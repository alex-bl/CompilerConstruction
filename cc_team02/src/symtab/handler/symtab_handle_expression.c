#include "handler/symtab_handle_expression.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "ast_expression.h"
#include "print_helper.h"
#include "validator.h"

static void append_error_to_expr(struct mCc_ast_expression *expression,
                                 struct mCc_validation_status_result *error)
{
	if (!expression->semantic_error) {
		expression->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(expression->semantic_error, error);
	}
}

static void
handle_inconsistent_type(struct mCc_ast_expression *expression,
                         enum mCc_ast_data_type type, const char *side,
                         struct mCc_symtab_and_validation_holder *info_holder)
{
	const char *type_msg;

	if (type == MCC_AST_DATA_TYPE_INCONSISTENT) {
		type_msg = "Inconsistent";
	} else {
		type_msg = "Unknown";
	}

	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE, "Operation '%s': %s type at %s",
	         mCc_ast_print_binary_op(expression->op), type_msg, side);
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        type, strndup(error_msg, strlen(error_msg)));

	append_error_to_expr(expression, error);
	expression->data_type = type;
	info_holder->error_count++;
}

static void handle_identifier(struct mCc_ast_expression *expression,
                              struct mCc_ast_identifier *identifier)
{
	if (!identifier->symtab_info) {
		expression->data_type = MCC_AST_DATA_TYPE_UNKNOWN;
	} else if (identifier->symtab_info->already_defined) {
		// which identifier is correct?
		expression->data_type = MCC_AST_DATA_TYPE_INCONSISTENT;
	} else {
		expression->data_type = identifier->symtab_info->data_type;
	}
}

static void
handle_expected_type(struct mCc_ast_expression *expression,
                     enum mCc_ast_data_type expected,
                     enum mCc_ast_data_type actual,
                     struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Incompatible types: Expected '%s' but have '%s'",
	         mCc_ast_print_data_type(expected), mCc_ast_print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_expr(expression, error);
	expression->data_type = MCC_AST_DATA_TYPE_INCOMPATIBLE;
	info_holder->error_count++;
}

static void handle_expected_numerical_type(
    struct mCc_ast_expression *expression, enum mCc_ast_data_type actual,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Incompatible types: Expected '%s' or '%s' but have '%s'",
	         mCc_ast_print_data_type(MCC_AST_DATA_TYPE_INT),
	         mCc_ast_print_data_type(MCC_AST_DATA_TYPE_FLOAT), mCc_ast_print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_expr(expression, error);
	expression->data_type = MCC_AST_DATA_TYPE_INCOMPATIBLE;
	info_holder->error_count++;
}

static void handle_expected_numerical_and_bool_type(
    struct mCc_ast_expression *expression, enum mCc_ast_data_type actual,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Incompatible types: Expected '%s' or '%s' or '%s' but have '%s'",
	         mCc_ast_print_data_type(MCC_AST_DATA_TYPE_INT),
	         mCc_ast_print_data_type(MCC_AST_DATA_TYPE_FLOAT),
	         mCc_ast_print_data_type(MCC_AST_DATA_TYPE_BOOL), mCc_ast_print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_expr(expression, error);
	expression->data_type = MCC_AST_DATA_TYPE_INCOMPATIBLE;
	info_holder->error_count++;
}

static void handle_invalid_operation(
    struct mCc_ast_expression *expression, enum mCc_ast_binary_op op,
    enum mCc_ast_data_type actual, enum mCc_ast_data_type expected,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Invalid operation '%s' on '%s'-types: Expected '%s'",
	         mCc_ast_print_binary_op(op), mCc_ast_print_data_type(actual),
	         mCc_ast_print_data_type(expected));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_expr(expression, error);
	expression->data_type = MCC_AST_DATA_TYPE_INCOMPATIBLE;
	info_holder->error_count++;
}

static void handle_invalid_operation_numerical(
    struct mCc_ast_expression *expression, enum mCc_ast_binary_op op,
    enum mCc_ast_data_type actual,
    struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Invalid operation '%s' on '%s'-types: Expected '%s' or '%s'",
	         mCc_ast_print_binary_op(op), mCc_ast_print_data_type(actual),
	         mCc_ast_print_data_type(MCC_AST_DATA_TYPE_INT),
	         mCc_ast_print_data_type(MCC_AST_DATA_TYPE_FLOAT));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_expr(expression, error);
	expression->data_type = MCC_AST_DATA_TYPE_INCOMPATIBLE;
	info_holder->error_count++;
}

static void
handle_inconsistent_sides(struct mCc_ast_expression *expression,
                          enum mCc_ast_data_type lhs_type,
                          enum mCc_ast_data_type rhs_type,
                          struct mCc_symtab_and_validation_holder *info_holder)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Operation '%s' has incompatible types: '%s' at left "
	         "hand side, but '%s' at right hand side",
	         mCc_ast_print_binary_op(expression->op), mCc_ast_print_data_type(lhs_type),
	         mCc_ast_print_data_type(rhs_type));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_TYPE,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_expr(expression, error);
	expression->data_type = MCC_AST_DATA_TYPE_INCONSISTENT;
	info_holder->error_count++;
}

static bool binary_op_is_numerical(enum mCc_ast_binary_op op)
{
	return op != MCC_AST_BINARY_OP_AND && op != MCC_AST_BINARY_OP_OR;
}

static bool binary_op_is_numerical_only(enum mCc_ast_binary_op op)
{
	return op == MCC_AST_BINARY_OP_ADD || op == MCC_AST_BINARY_OP_SUB ||
	       op == MCC_AST_BINARY_OP_MUL || op == MCC_AST_BINARY_OP_DIV ||
	       op == MCC_AST_BINARY_OP_LESS_THAN ||
	       op == MCC_AST_BINARY_OP_GREATER_THAN ||
	       op == MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN ||
	       op == MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN;
}

static bool binary_op_returns_non_bool(enum mCc_ast_binary_op op)
{
	return op == MCC_AST_BINARY_OP_ADD || op == MCC_AST_BINARY_OP_SUB ||
	       op == MCC_AST_BINARY_OP_MUL || op == MCC_AST_BINARY_OP_DIV;
}

static bool type_is_numerical(enum mCc_ast_data_type type)
{
	return type == MCC_AST_DATA_TYPE_INT || type == MCC_AST_DATA_TYPE_FLOAT;
}

static void assign_type(struct mCc_ast_expression *expression,
                        enum mCc_ast_binary_op binary_op,
                        enum mCc_ast_data_type type)
{
	/*
	 * just set the type: numerical ops keeps it, boolean ops change
	 * it to bool
	 */
	if (binary_op_returns_non_bool(binary_op)) {
		expression->data_type = type;
	} else {
		expression->data_type = MCC_AST_DATA_TYPE_BOOL;
	}
}

void mCc_handle_expression_literal_post_order(
    struct mCc_ast_expression *expression, void *data)
{
	// save type
	expression->data_type = expression->literal->type;
}

void mCc_handle_expression_binary_op_post_order(
    struct mCc_ast_expression *expression, void *data)
{
	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	enum mCc_ast_data_type lhs_type = expression->lhs->data_type;
	enum mCc_ast_data_type rhs_type = expression->rhs->data_type;
	enum mCc_ast_binary_op binary_op = expression->op;

	bool erroneous_lhs = false;
	bool erroneous_rhs = false;

	if (lhs_type == MCC_AST_DATA_TYPE_INCONSISTENT ||
	    lhs_type == MCC_AST_DATA_TYPE_UNKNOWN) {
		handle_inconsistent_type(expression, lhs_type, "left hand side",
		                         info_holder);
		erroneous_lhs = true;
	}
	if (rhs_type == MCC_AST_DATA_TYPE_INCONSISTENT ||
	    rhs_type == MCC_AST_DATA_TYPE_UNKNOWN) {
		handle_inconsistent_type(expression, rhs_type, "right hand side",
		                         info_holder);
		erroneous_rhs = true;
	}
	// if both sides have known types
	if (!erroneous_lhs && !erroneous_rhs) {
		// not the same types
		if (lhs_type != rhs_type) {
			handle_inconsistent_sides(expression, lhs_type, rhs_type,
			                          info_holder);
		} else {
			// TODO: maybe refactor this one?
			if (type_is_numerical(lhs_type)) {
				if (!binary_op_is_numerical(binary_op)) {
					handle_invalid_operation(expression, binary_op, lhs_type,
					                         MCC_AST_DATA_TYPE_BOOL,
					                         info_holder);
				} else {
					assign_type(expression, binary_op, lhs_type);
				}
			} else if (lhs_type == MCC_AST_DATA_TYPE_BOOL) {
				if (binary_op_is_numerical_only(binary_op)) {
					handle_invalid_operation_numerical(expression, binary_op,
					                                   lhs_type, info_holder);
				} else {
					assign_type(expression, binary_op, lhs_type);
				}
			} else {
				// string permits on binary operation
				handle_expected_numerical_and_bool_type(expression, lhs_type,
				                                        info_holder);
			}
		}
	}
}

void mCc_handle_expression_parenth_post_order(
    struct mCc_ast_expression *expression, void *data)
{
	/*
	 * just set the type, if it was inconsistent, it is already reported
	 */
	expression->data_type = expression->expression->data_type;
}

void mCc_handle_expression_identifier_post_order(
    struct mCc_ast_expression *expression, void *data)
{
	struct mCc_ast_identifier *identifier = expression->identifier;
	handle_identifier(expression, identifier);
}

void mCc_handle_expression_identifier_array_post_order(
    struct mCc_ast_expression *expression, void *data)
{
	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_identifier *identifier = expression->array_identifier;
	// identifier check => gives the type to the expression
	handle_identifier(expression, identifier);

	// if no invalid identifier was detected
	if (expression->data_type != MCC_AST_DATA_TYPE_UNKNOWN &&
	    expression->data_type != MCC_AST_DATA_TYPE_INCONSISTENT) {
		enum mCc_ast_data_type arr_expr_type =
		    expression->array_index_expression->data_type;

		if (arr_expr_type == MCC_AST_DATA_TYPE_INCONSISTENT ||
		    arr_expr_type == MCC_AST_DATA_TYPE_UNKNOWN) {
			expression->data_type = arr_expr_type;
		} else if (arr_expr_type != MCC_AST_DATA_TYPE_INT) {
			handle_expected_type(expression, MCC_AST_DATA_TYPE_INT,
			                     arr_expr_type, info_holder);
		} else {
			// type is int as expected
			expression->data_type = arr_expr_type;
		}
	}
}

void mCc_handle_expression_function_call_post_order(
    struct mCc_ast_expression *expression, void *data)
{
	// validation is done at function-call-handler, just set type
	struct mCc_ast_identifier *identifier =
	    expression->function_call->identifier;
	handle_identifier(expression, identifier);
}

void mCc_handle_expression_unary_op_post_order(
    struct mCc_ast_expression *expression, void *data)
{
	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	enum mCc_ast_data_type unary_op_data_type =
	    expression->unary_rhs->data_type;
	enum mCc_ast_unary_op unary_op = expression->unary_op;
	// unknown or inconsistent
	if (unary_op_data_type == MCC_AST_DATA_TYPE_INCONSISTENT ||
	    unary_op_data_type == MCC_AST_DATA_TYPE_UNKNOWN) {
		expression->data_type = unary_op_data_type;
	}
	// minus on non-numerical-type
	else if (unary_op == MCC_AST_UNARY_OP_MINUS &&
	         (unary_op_data_type != MCC_AST_DATA_TYPE_INT ||
	          unary_op_data_type != MCC_AST_DATA_TYPE_FLOAT)) {

		handle_expected_numerical_type(expression, unary_op_data_type,
		                               info_holder);

	}
	// negation on non-boolean-type
	else if (unary_op == MCC_AST_UNARY_OP_NEGATION &&
	         unary_op_data_type != MCC_AST_DATA_TYPE_BOOL) {
		handle_expected_type(expression, MCC_AST_DATA_TYPE_BOOL,
		                     unary_op_data_type, info_holder);
	} // everything is fine
	else {
		expression->data_type = unary_op_data_type;
	}
}
