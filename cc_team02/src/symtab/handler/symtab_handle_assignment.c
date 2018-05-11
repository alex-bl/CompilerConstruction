#include "handler/symtab_handle_assignment.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "ast_assignment.h"
#include "ast_data_type.h"
#include "ast_expression.h"
#include "ast_identifier.h"
#include "print_helper.h"
#include "symbol_table.h"
#include "validator.h"

static void
append_error_to_assignment(struct mCc_ast_assignment *assignment,
                           struct mCc_validation_status_result *error)
{
	if (!assignment->semantic_error) {
		assignment->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(assignment->semantic_error, error);
	}
}

static void handle_expected_type(struct mCc_ast_assignment *assignment,
                                 enum mCc_ast_data_type expected,
                                 enum mCc_ast_data_type actual)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Invalid assignment: Expected '%s' but have '%s'",
	         print_data_type(expected), print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_assignment(assignment, error);
}

static void
handle_expected_type_array_expr(struct mCc_ast_assignment *assignment,
                                enum mCc_ast_data_type expected,
                                enum mCc_ast_data_type actual)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(
	    error_msg, ERROR_MSG_BUF_SIZE,
	    "Invalid index exppression on assignment: Expected '%s' but have '%s'",
	    print_data_type(expected), print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_assignment(assignment, error);
}

static void
handle_assignment(struct mCc_ast_assignment *assignment,
                  struct mCc_ast_expression *expression,
                  struct mCc_symtab_and_validation_holder *info_holder)
{
	struct mCc_ast_identifier *identifier = assignment->identifier;
	// identifier not defined/duplicate => handled at identifier
	if (!identifier->symtab_info || identifier->symtab_info->already_defined) {
		// TODO: do nothing? log?
		return;
	}
	enum mCc_ast_data_type identifier_type = identifier->symtab_info->data_type;
	enum mCc_ast_data_type expression_type = expression->data_type;
	/*
	 * incompatible types, but not unknown nor inconsistent (if the latter is
	 * the case, they are catched elsewhere)
	 */
	if (identifier_type != expression_type &&
	    expression_type != MCC_AST_DATA_TYPE_UNKNOWN &&
	    expression_type != MCC_AST_DATA_TYPE_INCONSISTENT) {
		handle_expected_type(assignment, identifier_type, expression_type);
		info_holder->error_count++;
	}
}

static void
handle_assignment_array(struct mCc_ast_assignment *assignment,
                        struct mCc_symtab_and_validation_holder *info_holder)
{

	enum mCc_ast_data_type arr_index_expr_type =
	    assignment->array_index_expression->data_type;

	if (arr_index_expr_type != MCC_AST_DATA_TYPE_UNKNOWN &&
	    arr_index_expr_type != MCC_AST_DATA_TYPE_INCONSISTENT &&
	    arr_index_expr_type != MCC_AST_DATA_TYPE_INT) {
		handle_expected_type_array_expr(assignment, MCC_AST_DATA_TYPE_INT,
		                                arr_index_expr_type);
		info_holder->error_count++;
	}
}

// called post orderly
void mCc_symtab_handle_primitive_assignment_post_order(
    struct mCc_ast_assignment *assignment, void *data)
{
	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	assert(assignment);
	assert(data);
	handle_assignment(assignment, assignment->assigned_expression, info_holder);
}

void mCc_symtab_handle_array_assignment_post_order(
    struct mCc_ast_assignment *assignment, void *data)
{
	assert(assignment);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	// checks for array-expression
	handle_assignment(assignment, assignment->array_assigned_expression,
	                  info_holder);
	// and its index
	handle_assignment_array(assignment, info_holder);
}
