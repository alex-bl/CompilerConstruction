#include "handler/symtab_handle_statement.h"

#include <assert.h>
#include <string.h>

#include "ast_data_type.h"
#include "ast_statement.h"
#include "config.h"
#include "log.h"
#include "print_helper.h"
#include "validator.h"

static void
append_error_to_statement(struct mCc_ast_statement *statement,
                          struct mCc_validation_status_result *error)
{
	if (!statement->semantic_error) {
		statement->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(statement->semantic_error, error);
	}
}

static void
handle_expected_type(struct mCc_ast_statement *statement,
                     enum mCc_ast_data_type expected,
                     enum mCc_ast_data_type actual,
                     struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Incompatible types: Expected '%s' but have '%s'",
	         print_data_type(expected), print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_statement(statement, error);
	info_holder->error_count++;
}

static void handle_expected_return_type(
    struct mCc_ast_statement *statement, enum mCc_ast_data_type expected,
    enum mCc_ast_data_type actual,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "In function '%s': Expected a return-type of '%s' but have '%s' "
	         "(incompatible return type)",
	         info_holder->function_identifier->identifier_name,
	         print_data_type(expected), print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_RETURN,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_statement(statement, error);
	info_holder->error_count++;
}

static void
handle_statement(struct mCc_ast_statement *statement,
                 struct mCc_ast_expression *condition_expr,
                 struct mCc_symtab_and_validation_holder *info_holder)
{
	enum mCc_ast_data_type condition_expr_type = condition_expr->data_type;
	if (condition_expr_type == MCC_AST_DATA_TYPE_INCONSISTENT ||
	    condition_expr_type == MCC_AST_DATA_TYPE_UNKNOWN ||
	    condition_expr_type == MCC_AST_DATA_TYPE_INCOMPATIBLE) {
		// no futher things to do => handled elsewhere
		log_debug("Inconsistent or unknown condition-expression detected.");
	} else if (condition_expr_type != MCC_AST_DATA_TYPE_BOOL) {
		handle_expected_type(statement, MCC_AST_DATA_TYPE_BOOL,
		                     condition_expr_type, info_holder);
	}
}

static void handle_returns_on_control_path(
    struct mCc_ast_statement *statement,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	struct mCc_ast_identifier *identifier = info_holder->function_identifier;
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(
	    error_msg, ERROR_MSG_BUF_SIZE,
	    "In function '%s': Missing return of type '%s' on this execution path",
	    identifier->identifier_name,
	    print_data_type(identifier->symtab_info->data_type));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_MISSING_RETURN_PATH,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_statement(statement, error);
	info_holder->error_count++;
}

static bool
if_statement_returns_on_all_paths(struct mCc_ast_statement *statement)
{
	struct mCc_ast_statement *if_statement = statement->if_statement;
	struct mCc_ast_statement *else_statement = statement->else_statement;
	bool else_is_valid = true;

	if (!else_statement) {
		if (!statement->next_statement ||
		    !statement->next_statement->returns_on_control_path) {
			else_is_valid = false;
		}
	} else {
		else_is_valid = else_statement->returns_on_control_path;
	}

	return if_statement->returns_on_control_path && else_is_valid;
}

static void
remove_invalid_path_errors(struct mCc_ast_statement *statement,
                           struct mCc_symtab_and_validation_holder *info_holder)
{
	if (statement->statement_type == MCC_AST_STATEMENT_IF) {
		remove_invalid_path_errors(statement->if_statement,info_holder);
		remove_invalid_path_errors(statement->else_statement,info_holder);
	} else if (statement->statement_type == MCC_AST_STATEMENT_WHILE) {
		remove_invalid_path_errors(statement->while_statement,info_holder);
	} else if (statement->next_statement) {
		remove_invalid_path_errors(statement->next_statement,info_holder);
	}

	if (!statement->returns_on_control_path) {
		statement->returns_on_control_path = true;
		info_holder->error_count--;
	}
}


/*
 * TODO: https://stackoverflow.com/questions/21945891/how-do-i-check-whether-all-code-paths-return-a-value
 *
You can do this with a recursive walk over the AST. For example:

- A sequence of statements returns on all control paths if either the first statement returns on all control paths or the second statement returns on all control paths.
- An if statement returns on all control paths if both the "if" and "else" branches return on all control paths or the "if" statement is always true.
- A while loop returns on all control paths only if the "while" condition is always true.
- A return statement returns on all control paths.
 *
 *
 */
static void set_returns_on_control_path(struct mCc_ast_statement *statement,
		 struct mCc_symtab_and_validation_holder *info_holder)
{
	assert(statement);

	if (!statement->returns_on_control_path) {
		struct mCc_ast_statement *next_statement = statement->next_statement;
		// e.g. on ifs
		bool special_return_path = false;
		bool next_stmt_returns = false;

		// handle if
		if (statement->statement_type == MCC_AST_STATEMENT_IF) {
			special_return_path = if_statement_returns_on_all_paths(statement);
		}

		if (next_statement) {
			next_stmt_returns = next_statement->returns_on_control_path;
		}

		statement->returns_on_control_path =
		    special_return_path || next_stmt_returns;

		//if statement has a path
		if(!special_return_path && next_stmt_returns){
			remove_invalid_path_errors(statement,info_holder);
		}
	}
}

static enum mCc_ast_data_type get_expected_type(void *data)
{
	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_symbol_table_node *symtab_info =
	    info_holder->function_identifier->symtab_info;

	if (symtab_info->already_defined) {
		// no unique identifier => return type not known
		return MCC_AST_DATA_TYPE_UNKNOWN;
	}
	return symtab_info->data_type;
}

static bool statement_is_erroneous(struct mCc_ast_statement *statement,
                                   void *data)
{

	enum mCc_ast_data_type expected_type = get_expected_type(data);
	return !statement->returns_on_control_path &&
	       expected_type != MCC_AST_DATA_TYPE_VOID &&
	       expected_type != MCC_AST_DATA_TYPE_UNKNOWN;
}

static bool
void_function_checked(struct mCc_ast_statement *return_statement,
                      enum mCc_ast_data_type function_type,
                      struct mCc_symtab_and_validation_holder *info_holder)
{
	if (!return_statement || !return_statement->return_expression) {
		if (function_type != MCC_AST_DATA_TYPE_VOID) {
			handle_expected_return_type(return_statement, function_type,
			                     MCC_AST_DATA_TYPE_VOID, info_holder);
		}
		// everything is fine if function is void
		return true;
	}
	return false;
}

void mCc_symtab_handle_if_statement_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	set_returns_on_control_path(statement,info_holder);

	struct mCc_ast_expression *condition_expr = statement->condition_expression;
	handle_statement(statement, condition_expr, info_holder);

	// wrong return-path and non-void
	if (statement_is_erroneous(statement, data)) {
		handle_returns_on_control_path(statement, info_holder);
	}
}

void mCc_symtab_handle_while_statement_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	set_returns_on_control_path(statement,info_holder);

	struct mCc_ast_expression *loop_condition =
	    statement->loop_condition_expression;
	handle_statement(statement, loop_condition, info_holder);

	// wrong return-path and non-void
	if (statement_is_erroneous(statement, data)) {
		handle_returns_on_control_path(statement, info_holder);
	}
}

//do typechecking on every return inside a function!
void mCc_symtab_handle_statement_return_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);
	// TODO: really necessary here?
	statement->returns_on_control_path = true;

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_identifier *identifier = info_holder->function_identifier;

	log_debug("Processing type-checking on function return '%s'...",
	          identifier->identifier_name);

	// error detected previously
	if (statement->semantic_error || identifier->semantic_error) {
		log_debug("Error already detected. Do not check return type");
	} else {

		enum mCc_ast_data_type function_type =
		    identifier->symtab_info->data_type;

		// no more checks needed
		if (void_function_checked(statement, function_type,
		                          info_holder)) {
			return;
		}

		enum mCc_ast_data_type return_type =
		    statement->return_expression->data_type;
		// if return is void and no return-expression is set => valid
		if (!statement->return_expression &&
		    return_type == MCC_AST_DATA_TYPE_VOID) {
			return;
		}
		// incompatible types
		if (return_type != MCC_AST_DATA_TYPE_INCONSISTENT &&
		    return_type != MCC_AST_DATA_TYPE_UNKNOWN &&
		    return_type != function_type) {
			handle_expected_return_type(statement, function_type, return_type,
			                     info_holder);
		}
	}
	log_debug("Function-def return-type-checking completed");
}

void mCc_symtab_handle_statement_declaration_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	set_returns_on_control_path(statement,info_holder);


	// wrong return-path and non-void
	if (statement_is_erroneous(statement, data)) {
		handle_returns_on_control_path(statement, info_holder);
	}
}

void mCc_symtab_handle_statement_assignment_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	set_returns_on_control_path(statement,info_holder);

	// wrong return-path and non-void
	if (statement_is_erroneous(statement, data)) {
		handle_returns_on_control_path(statement, info_holder);
	}
}

void mCc_symtab_handle_statement_expression_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	set_returns_on_control_path(statement,info_holder);

	// wrong return-path and non-void
	if (statement_is_erroneous(statement, data)) {
		handle_returns_on_control_path(statement, info_holder);
	}
}
