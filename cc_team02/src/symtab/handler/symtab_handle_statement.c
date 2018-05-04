
#include "config.h"
#include "log.h"
#include "mCc/ast/basis/ast_data_type.h"
#include "mCc/ast/basis/ast_statement.h"
#include <assert.h>

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

static void handle_expected_type(struct mCc_ast_statement *statement,
                                 enum mCc_ast_data_type expected,
                                 enum mCc_ast_data_type actual)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, "Incompatible types: Expected '%s' but have %s",
	         ERROR_MSG_BUF_SIZE, print_data_type(expected),
	         print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        error_msg);
	append_error_to_statement(statement, error);
}

static void handle_statement(struct mCc_ast_statement *statement,
                             struct mCc_ast_expression *condition_expr)
{
	enum mCc_ast_data_type condition_expr_type = condition_expr->data_type;
	if (condition_expr_type == MCC_AST_DATA_TYPE_INCONSISTENT ||
	    condition_expr_type == MCC_AST_DATA_TYPE_UNKNOWN) {
		// no futher things to do => handled elsewhere
		log_debug("Inconsistent or unknown condition-expression detected.");
	} else if (condition_expr_type != MCC_AST_DATA_TYPE_BOOL) {
		handle_expected_type(statement, MCC_AST_DATA_TYPE_BOOL,
		                     condition_expr_type);
	}
}

void mCc_symtab_handle_if_statement_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_ast_expression *condition_expr = statement->condition_expression;
	handle_statement(statement, condition_expr);
}

void mCc_symtab_handle_while_statement_post_order(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_ast_expression *loop_condition =
	    statement->loop_condition_expression;
	handle_statement(statement, loop_condition);
}
