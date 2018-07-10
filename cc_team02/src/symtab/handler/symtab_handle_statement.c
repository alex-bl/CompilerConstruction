#include "symtab_handle_statement.h"

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
	// just this two cases
	const char *type =
	    statement->statement_type == MCC_AST_STATEMENT_IF ? "If" : "While";

	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "%s-condition has incompatible types: Expected '%s' but have '%s'",
	         type, mCc_ast_print_data_type(expected),
	         mCc_ast_print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)+1));
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

void mCc_symtab_handle_if_statement_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_expression *condition_expr = statement->condition_expression;
	handle_statement(statement, condition_expr, info_holder);
}

void mCc_symtab_handle_while_statement_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_expression *loop_condition =
	    statement->loop_condition_expression;
	handle_statement(statement, loop_condition, info_holder);
}
