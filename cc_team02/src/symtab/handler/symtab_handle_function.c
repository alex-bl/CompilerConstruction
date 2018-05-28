#include "symtab_handle_function.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "config.h"
#include "log.h"
#include "print_helper.h"
#include "symbol_table.h"
#include "validation_status.h"
#include "validator.h"
#include "validator_helper.h"

/*
 * TODO:
 * - check for main
 * - check if has a return
 */
// is done preorder => needs symtab_info
static int get_expected_arg_count(struct mCc_symbol_table_node *symtab_info)
{
	assert(symtab_info);

	// is a function-identifier
	struct mCc_symtab_parameter_ref *next_param = symtab_info->next_parameter;
	int counter = 0;

	while (next_param) {
		counter++;
		next_param = next_param->next_parameter;
	}
	return counter;
}

static int get_actual_arg_count(struct mCc_ast_function_call *function_call)
{
	assert(function_call);
	struct mCc_ast_expression *next_expr = function_call->first_argument;
	int counter = 0;

	while (next_expr) {
		counter++;
		next_expr = next_expr->next_expr;
	}
	return counter;
}

static void
append_error_to_function_def(struct mCc_ast_function_def *function_def,
                             struct mCc_validation_status_result *error)
{
	if (!function_def->semantic_error) {
		function_def->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(function_def->semantic_error,
		                                    error);
	}
}

static void
append_error_to_function_call(struct mCc_ast_function_call *function_call,
                              struct mCc_validation_status_result *error)
{
	if (!function_call->semantic_error) {
		function_call->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(function_call->semantic_error,
		                                    error);
	}
}

static void
handle_invalid_param_count(struct mCc_ast_function_call *call, int expected,
                           int actual,
                           struct mCc_symtab_and_validation_holder *info_holder)
{

	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Function '%s': Expected %d argument(s), but have %d",
	         call->identifier->identifier_name, expected, actual);
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_SIGNATURE,
	        strndup(error_msg, strlen(error_msg)));

	append_error_to_function_call(call, error);
	info_holder->error_count++;
}

static void
handle_function_def(struct mCc_ast_function_def *function_def,
                    struct mCc_symtab_and_validation_holder *info_holder)
{
	struct mCc_ast_identifier *identifier = function_def->identifier;
	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(info_holder->symbol_table->parent, identifier, true);

	// it shouldn't be null at this stage
	assert(symtab_info);

	if (!symtab_info->already_defined) {
		// append to holder for error-handling at statement-level
		info_holder->function_identifier = identifier;
	}
}

static void reset_returns_on_control_path(struct mCc_ast_statement *statement)
{
	if (statement) {
		statement->returns_on_control_path = true;

		switch (statement->statement_type) {

		case MCC_AST_STATEMENT_IF:
			reset_returns_on_control_path(statement->if_statement);
			reset_returns_on_control_path(statement->else_statement);
			break;
		case MCC_AST_STATEMENT_WHILE:
			reset_returns_on_control_path(statement->while_statement);
			break;
		case MCC_AST_STATEMENT_RETURN:
		case MCC_AST_STATEMENT_DECLARATION:
		case MCC_AST_STATEMENT_ASSIGNMENT:
		case MCC_AST_STATEMENT_EXPRESSION: break;
		}

		if (statement->next_statement) {
			reset_returns_on_control_path(statement->next_statement);
		}
	}
}

static bool
is_void_function_scope(struct mCc_symtab_and_validation_holder *info_holder)
{
	return info_holder->function_identifier->symtab_info->data_type ==
	       MCC_AST_DATA_TYPE_VOID;
}

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

static void handle_expected_return_type_statement(
    struct mCc_ast_statement *statement, enum mCc_ast_data_type expected,
    enum mCc_ast_data_type actual,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "In function '%s': Expected a return-type of '%s' but have '%s' "
	         "(incompatible return type)",
	         info_holder->function_identifier->identifier_name,
	         mCc_ast_print_data_type(expected),
	         mCc_ast_print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_RETURN,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_statement(statement, error);
	info_holder->error_count++;
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
	    mCc_ast_print_data_type(identifier->symtab_info->data_type));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_MISSING_RETURN_PATH,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_statement(statement, error);
	statement->return_error_already_reported = true;
	info_holder->error_count++;
}

static bool error_already_reported(struct mCc_ast_statement *statement)
{
	if (statement->statement_type == MCC_AST_STATEMENT_IF) {
		bool if_stmt_reported =
		    (statement->if_statement
		         ? statement->if_statement->return_error_already_reported
		         : false);
		bool else_stmt_reported =
		    (statement->else_statement
		         ? statement->else_statement->return_error_already_reported
		         : false);
		return statement->return_error_already_reported || if_stmt_reported ||
		       else_stmt_reported;
	} else if (statement->statement_type == MCC_AST_STATEMENT_WHILE) {
		bool while_stmt_reported =
		    (statement->while_statement
		         ? statement->while_statement->return_error_already_reported
		         : false);
		return statement->return_error_already_reported || while_stmt_reported;
	}
	return statement->return_error_already_reported;
}

static bool
return_path_error_already_reported(struct mCc_ast_statement *statement)
{
	assert(statement);
	struct mCc_ast_statement *next_statement = statement->next_statement;
	bool already_reported = error_already_reported(statement);

	if (next_statement) {
		already_reported = error_already_reported(next_statement);
	}
	statement->return_error_already_reported = already_reported;

	return already_reported;
}

static bool void_function_checked_statement(
    struct mCc_ast_statement *return_statement,
    enum mCc_ast_data_type function_type,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	if (!return_statement || !return_statement->return_expression) {
		if (function_type != MCC_AST_DATA_TYPE_VOID) {
			handle_expected_return_type_statement(
			    return_statement, function_type, MCC_AST_DATA_TYPE_VOID,
			    info_holder);
		}
		// everything is fine if function is void
		return true;
	}
	return false;
}

static void
handle_wrong_return_type(struct mCc_ast_statement *statement,
                         struct mCc_symtab_and_validation_holder *info_holder)
{

	assert(statement);

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
		if (void_function_checked_statement(statement, function_type,
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
			handle_expected_return_type_statement(statement, function_type,
			                                      return_type, info_holder);
		}
	}
	log_debug("Function-def return-type-checking completed");
}

static bool get_returns_on_control_path(
    struct mCc_ast_statement *statement,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	if (!statement->next_statement) {
		return info_holder->function_identifier->symtab_info->data_type ==
		       MCC_AST_DATA_TYPE_VOID;
	}
	return statement->next_statement->returns_on_control_path;
}

static bool
check_return_path(struct mCc_ast_statement *statement,
                  struct mCc_symtab_and_validation_holder *info_holder)
{
	assert(info_holder);

	// if empty
	if (!statement) {
		return is_void_function_scope(info_holder);
	}

	bool return_path_exists = false;
	// check next statement first
	if (statement->next_statement) {
		return_path_exists =
		    check_return_path(statement->next_statement, info_holder);
	} else {
		// if there isn't any other statement left
		return_path_exists = is_void_function_scope(info_holder);
	}

	switch (statement->statement_type) {

	case MCC_AST_STATEMENT_IF:
		// a return path exists => set it
		if (return_path_exists) {
			// handles null-values
			reset_returns_on_control_path(statement->if_statement);
			reset_returns_on_control_path(statement->else_statement);
		}
		/*
		 * If the function is a void function, it isn't enough to reset the
		 * control-path-flag, checks for invalid return-types are also required!
		 */
		if (!return_path_exists || is_void_function_scope(info_holder)) {
			bool returns_if_branch =
			    check_return_path(statement->if_statement, info_holder);
			bool returns_else_branch =
			    check_return_path(statement->else_statement, info_holder);
			return_path_exists = (returns_if_branch && returns_else_branch) ||
			                     is_void_function_scope(info_holder);
		}
		break;
	case MCC_AST_STATEMENT_WHILE:
		if (return_path_exists) {
			reset_returns_on_control_path(statement->while_statement);
		}
		break;
	case MCC_AST_STATEMENT_RETURN:
		statement->returns_on_control_path = true;
		return_path_exists = true;
		handle_wrong_return_type(statement, info_holder);
		break;
	case MCC_AST_STATEMENT_DECLARATION:
	case MCC_AST_STATEMENT_ASSIGNMENT:
	case MCC_AST_STATEMENT_EXPRESSION:
		return_path_exists =
		    get_returns_on_control_path(statement, info_holder);
		break;
	}
	statement->returns_on_control_path = return_path_exists;
	if (!return_path_exists && !return_path_error_already_reported(statement)) {
		handle_returns_on_control_path(statement, info_holder);
	}
	// needed?
	return statement->returns_on_control_path;
}

// do this preorder
void mCc_symtab_handle_function_def_pre_order(struct mCc_ast_function_def *def,
                                              void *data)
{
	assert(def);
	assert(data);

	log_debug("Processing function-def '%s'...",
	          def->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	// just for linking symtab-info into info_holder
	handle_function_def(def, info_holder);

	log_debug("Function-def checking completed");
}

// TODO: refactor => duplicate to symtab_handle_statement except return
static void handle_expected_return_type(
    struct mCc_ast_function_def *def, enum mCc_ast_data_type expected,
    enum mCc_ast_data_type actual,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "In function '%s': Expected a return-type of '%s' but have '%s' "
	         "(incompatible return type)",
	         def->identifier->identifier_name,
	         mCc_ast_print_data_type(expected),
	         mCc_ast_print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_RETURN,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_function_def(def, error);
	info_holder->error_count++;
}

static void handle_expected_type_function_call(
    struct mCc_ast_function_call *call, enum mCc_ast_data_type expected,
    enum mCc_ast_data_type actual, int arg_nr,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Incompatible types at argument %d: Expected '%s' but have '%s'",
	         arg_nr, mCc_ast_print_data_type(expected),
	         mCc_ast_print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_PARAMETER,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_function_call(call, error);
	info_holder->error_count++;
}

const char *print_identifier_type(enum mCc_symtab_identifier_type type)
{
	if (type == MCC_SYM_TAB_IDENTIFIER_VARIABLE_PRIMITIVE) {
		return "";
	}
	return "[]";
}

static void handle_array_primitive_missmatch(
    struct mCc_ast_function_call *call,
    enum mCc_symtab_identifier_type expected,
    enum mCc_symtab_identifier_type actual, enum mCc_ast_data_type data_type,
    int arg_nr, struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(
	    error_msg, ERROR_MSG_BUF_SIZE,
	    "Incompatible types at argument %d: Expected '%s%s' but have '%s%s'",
	    arg_nr, mCc_ast_print_data_type(data_type),
	    print_identifier_type(expected), mCc_ast_print_data_type(data_type),
	    print_identifier_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_PARAMETER,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_function_call(call, error);
	info_holder->error_count++;
}

static void handle_array_size_missmatch(
    struct mCc_ast_function_call *call, size_t expected, size_t actual,
    enum mCc_ast_data_type data_type, int arg_nr,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Incompatible types at argument %d: Expected '%s[%ld]' but have "
	         "'%s[%ld]'",
	         arg_nr, mCc_ast_print_data_type(data_type), expected,
	         mCc_ast_print_data_type(data_type), actual);
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_PARAMETER,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_function_call(call, error);
	info_holder->error_count++;
}

static void handle_unknown_inconsistent_type(
    struct mCc_ast_function_call *call, int arg_nr,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE, "Inconsistent type at argument %d",
	         arg_nr);
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_PARAMETER,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_function_call(call, error);
	info_holder->error_count++;
}

static void
empty_function_checked(struct mCc_ast_function_def *def,
                       struct mCc_symtab_and_validation_holder *info_holder)
{
	enum mCc_ast_data_type function_type =
	    def->identifier->symtab_info->data_type;
	if (function_type != MCC_AST_DATA_TYPE_VOID) {
		handle_expected_return_type(def, function_type, MCC_AST_DATA_TYPE_VOID,
		                            info_holder);
	}
	// everything is fine if function is void
}

static void mark_parameters(struct mCc_ast_function_call *call)
{
	struct mCc_ast_expression *next_param = call->first_argument;
	while (next_param) {
		next_param->is_function_parameter = true;
		next_param = next_param->next_expr;
	}
}

static bool
array_primitive_missmatch(struct mCc_symtab_parameter_ref *next_param,
                          struct mCc_ast_expression *next_argument)
{
	enum mCc_symtab_identifier_type param_type =
	    next_param->identifier->symtab_info->entry_type;
	enum mCc_ast_expression_type expr_type = next_argument->type;

	if (expr_type == MCC_AST_EXPRESSION_TYPE_IDENTIFIER) {
		enum mCc_symtab_identifier_type expr_identifier_type =
		    next_argument->identifier->symtab_info->entry_type;
		return param_type != expr_identifier_type;
	} else if (expr_type == MCC_AST_EXPRESSION_TYPE_LITERAL) {
		return param_type == MCC_SYM_TAB_IDENTIFIER_VARIABLE_ARRAY;
	}

	return false;
}

static bool array_size_missmatch(struct mCc_symtab_parameter_ref *next_param,
                                 struct mCc_ast_expression *next_argument)
{
	struct mCc_symbol_table_node *symtab_info =
	    next_param->identifier->symtab_info;
	enum mCc_ast_expression_type expr_type = next_argument->type;

	if (symtab_info->entry_type == MCC_SYM_TAB_IDENTIFIER_VARIABLE_ARRAY &&
	    expr_type == MCC_AST_EXPRESSION_TYPE_IDENTIFIER) {

		struct mCc_symbol_table_node *symtab_info_arg =
		    next_argument->identifier->symtab_info;

		return symtab_info->size != symtab_info_arg->size;
	}
	return false;
}

// check for return-type
void mCc_symtab_handle_function_def_post_order(struct mCc_ast_function_def *def,
                                               void *data)
{
	assert(def);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_identifier *identifier = def->identifier;

	log_debug("Processing type-checking on function return '%s'...",
	          identifier->identifier_name);

	// error detected previously
	if (def->semantic_error || identifier->semantic_error) {
		log_debug("Error already detected. Do not check return type");
	} else if (def->first_statement) {
		check_return_path(def->first_statement, info_holder);
	} else {
		empty_function_checked(def, info_holder);
	}
	log_debug("Function-def return-type-checking completed");
}

void mCc_symtab_handle_function_call_pre_order(
    struct mCc_ast_function_call *call, void *data)
{
	assert(call);
	assert(data);

	log_debug("Checking function-call-signature '%s'...",
	          call->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_symbol_table_node *identifier_info =
	    mCc_symtab_lookup(info_holder->symbol_table, call->identifier, false);

	mark_parameters(call);

	// Reported later
	if (identifier_info && !identifier_info->already_defined) {
		int expected_nr_args = get_expected_arg_count(identifier_info);
		int actual_nr_args = get_actual_arg_count(call);

		if (expected_nr_args != actual_nr_args) {
			handle_invalid_param_count(call, expected_nr_args, actual_nr_args,
			                           info_holder);
		}
	}

	log_debug("Signature checking completed");
}

static enum mCc_symtab_identifier_type
get_identifier_type(struct mCc_ast_expression *expr)
{
	if (expr->type == MCC_AST_EXPRESSION_TYPE_LITERAL) {
		return MCC_SYM_TAB_IDENTIFIER_VARIABLE_PRIMITIVE;
	}
	return expr->identifier->symtab_info->entry_type;
}

/*
 * TODO:
 * - check argument-types => post-order
 */
void mCc_symtab_handle_function_call_post_order(
    struct mCc_ast_function_call *call, void *data)
{
	assert(call);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_identifier *identifier = call->identifier;
	struct mCc_symbol_table_node *symtab_info = identifier->symtab_info;

	if (!symtab_info) {
		log_debug("No symtab info associated with '%s'. It does not exist. No "
		          "check required",
		          identifier->identifier_name);
	} else if (call->semantic_error) {
		log_debug("Function '%s' has already errors. Skipping parameter check",
		          identifier->identifier_name);
	} else {
		// have the same size dueto previous checks
		struct mCc_symtab_parameter_ref *next_param =
		    symtab_info->next_parameter;
		struct mCc_ast_expression *next_argument = call->first_argument;
		int arg_counter = 0;

		log_debug("Type checking on function-call-signature '%s'...",
		          identifier->identifier_name);

		while (next_param) {

			enum mCc_ast_data_type arg_type = next_argument->data_type;
			enum mCc_ast_data_type def_type =
			    next_param->identifier->symtab_info->data_type;

			// unknown or inconsistent
			if (arg_type == MCC_AST_DATA_TYPE_UNKNOWN ||
			    arg_type == MCC_AST_DATA_TYPE_INCONSISTENT) {
				handle_unknown_inconsistent_type(call, arg_counter,
				                                 info_holder);
			} // different than expected
			else if (arg_type != def_type) {
				handle_expected_type_function_call(call, def_type, arg_type,
				                                   arg_counter, info_holder);
			} else if (array_primitive_missmatch(next_param, next_argument)) {
				enum mCc_symtab_identifier_type expected =
				    next_param->identifier->symtab_info->entry_type;
				enum mCc_symtab_identifier_type actual =
				    get_identifier_type(next_argument);

				handle_array_primitive_missmatch(
				    call, expected, actual, def_type, arg_counter, info_holder);
			} else if (array_size_missmatch(next_param, next_argument)) {
				size_t expected_size =
				    next_param->identifier->symtab_info->size;
				size_t actual_size =
				    next_argument->identifier->symtab_info->size;
				handle_array_size_missmatch(call, expected_size, actual_size,
				                            def_type, arg_counter, info_holder);
			}
			arg_counter++;
			next_param = next_param->next_parameter;
			next_argument = next_argument->next_expr;
		}
		log_debug("Type checking completed");
	}
}
