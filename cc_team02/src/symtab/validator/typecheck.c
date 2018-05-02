#include "mCc/symtab/validator/typecheck.h"

#include <stdbool.h>
#include <string.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validation_status.h"
#include "mCc/symtab/validator/validator_helper.h"

static enum mCc_ast_data_type get_type(struct mCc_symbol_table *symbol_table,
                                       struct mCc_ast_identifier *identifier)
{
	struct mCc_symbol_table_node *node_info =
	    mCc_symtab_lookup(symbol_table, identifier, false);
	if (!node_info) {
		return MCC_AST_DATA_TYPE_UNKNOWN;
	}
	return node_info->data_type;
}

static bool is_valid_type_on_binary(enum mCc_ast_data_type type_left,
                                    enum mCc_ast_data_type type_right)
{
	return type_left != MCC_AST_DATA_TYPE_INCONSISTENT &&
	       type_left != MCC_AST_DATA_TYPE_UNKNOWN &&
	       type_right != MCC_AST_DATA_TYPE_INCONSISTENT &&
	       type_right != MCC_AST_DATA_TYPE_UNKNOWN && type_left == type_right;
}

/*
 * Symboltable needed at this stage because symtab-info is linked to the
 * identifier after identifier is visited
 */
enum mCc_ast_data_type
mCc_typecheck_get_type(struct mCc_symbol_table *symbol_table,
                       struct mCc_ast_expression *expr)
{

	// TODO: what happens if identifier inside expression is not known?
	switch (expr->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL: return expr->literal->type; break;
	case MCC_AST_EXPRESSION_TYPE_BINARY_OP: {
		enum mCc_ast_data_type lhs_type =
		    mCc_typecheck_get_type(symbol_table, expr->lhs);
		enum mCc_ast_data_type rhs_type =
		    mCc_typecheck_get_type(symbol_table, expr->rhs);
		if (is_valid_type_on_binary(lhs_type, rhs_type)) {
			return lhs_type;
		}
		return MCC_AST_DATA_TYPE_INCONSISTENT;
		break;
	}
	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		return mCc_typecheck_get_type(symbol_table, expr->expression);
		break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		return get_type(symbol_table, expr->identifier);
		break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
		return get_type(symbol_table, expr->array_identifier);
		break;
	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
		return get_type(symbol_table, expr->function_call->identifier);
		break;
	case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
		return mCc_typecheck_get_type(symbol_table, expr->unary_rhs);
		break;
	}
	log_error("No ast-type-match: Should this ever happen?");
	return MCC_AST_DATA_TYPE_INCONSISTENT;
}

enum mCc_validation_status_type
mCc_typecheck_validate_type(struct mCc_symbol_table *symbol_table,
                            enum mCc_ast_data_type expected_type,
                            struct mCc_ast_expression *to_check)
{
	enum mCc_ast_data_type expr_type =
	    mCc_typecheck_get_type(symbol_table, to_check);
	// is valid
	if (expr_type == expected_type) {
		return MCC_VALIDATION_STATUS_VALID;
	} else if (expr_type == MCC_AST_DATA_TYPE_UNKNOWN) {
		return MCC_VALIDATION_STATUS_ERROR_REPORTED_LATER;
	}
	// invalid type
	return MCC_VALIDATION_STATUS_INVALID_TYPE;
}

enum mCc_validation_status_type
mCc_typecheck_validate_type_assignment(struct mCc_symbol_table *symbol_table,
                                       void *validator_input)
{
	struct mCc_ast_assignment *assignment =
	    (struct mCc_ast_assignment *)validator_input;

	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(symbol_table, assignment->identifier, false);

	if (!symtab_info) {
		log_error("No symtab entry found for '%s'. Error is reported later.",
		          assignment->identifier->identifier_name);
		/*
		 * happens if trying to validate an invalid identifier => is reported
		 * later
		 */
		return MCC_VALIDATION_STATUS_ERROR_REPORTED_LATER;
	}
	struct mCc_ast_expression *to_check = mCc_ast_get_expression(assignment);
	return mCc_typecheck_validate_type(symbol_table, symtab_info->data_type,
	                                   to_check);
}

enum mCc_validation_status_type mCc_typecheck_validate_type_assignment_arr_expr(
    struct mCc_symbol_table *symbol_table, void *validator_input)
{
	struct mCc_ast_assignment *assignment =
	    (struct mCc_ast_assignment *)validator_input;

	struct mCc_ast_expression *to_check = assignment->array_index_expression;
	return mCc_typecheck_validate_type(symbol_table, MCC_AST_DATA_TYPE_INT,
	                                   to_check);
}

// is only called if there isn't any other error with the function
enum mCc_validation_status_type
mCc_typecheck_validate_type_return(struct mCc_symbol_table *symbol_table,
                                   void *validator_input)
{
	struct mCc_ast_function_def *function_def =
	    (struct mCc_ast_function_def *)validator_input;

	struct mCc_ast_statement *to_check =
	    mCc_validator_find_return_statement(function_def);

	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(symbol_table, function_def->identifier, false);

	/*
	 * If it has no return-statement => valid
	 *
	 * Check for the signature is done elsewhere
	 */
	if (!to_check) {
		return MCC_VALIDATION_STATUS_VALID;
	}

	return mCc_typecheck_validate_type(symbol_table, symtab_info->data_type,
	                                   to_check->return_expression);
}

static enum mCc_validation_status_type
check_statement(struct mCc_ast_expression *to_check,
                struct mCc_symbol_table *symbol_table)
{
	return mCc_typecheck_validate_type(symbol_table, MCC_AST_DATA_TYPE_BOOL,
	                                   to_check);
}

enum mCc_validation_status_type
mCc_typecheck_validate_if(struct mCc_symbol_table *symbol_table,
                          void *validator_input)
{
	struct mCc_ast_statement *to_check =
	    (struct mCc_ast_statement *)validator_input;
	return check_statement(to_check->condition_expression, symbol_table);
}

enum mCc_validation_status_type
mCc_typecheck_validate_while(struct mCc_symbol_table *symbol_table,
                             void *validator_input)
{
	struct mCc_ast_statement *to_check =
	    (struct mCc_ast_statement *)validator_input;
	return check_statement(to_check->loop_condition_expression, symbol_table);
}

/*
 * Assertions:
 * - identifier is valid
 * - signature is ok
 * - parameter have identifier with associated symtab_info
 */
enum mCc_validation_status_type
mCc_typecheck_validate_function_call(struct mCc_symbol_table *symbol_table,
                                     void *validator_input)
{
	struct mCc_ast_function_call *function_call =
	    (struct mCc_ast_function_call *)validator_input;

	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(symbol_table, function_call->identifier, false);

	struct mCc_symtab_parameter_ref *next_param = symtab_info->next_parameter;
	struct mCc_ast_expression *next_argument = function_call->first_argument;

	while (next_param) {
		enum mCc_ast_data_type param_type =
		    next_param->identifier->symtab_info->data_type;
		enum mCc_validation_status_type param_validation_status =
		    mCc_typecheck_validate_type(symbol_table, param_type,
		                                next_argument);

		if (param_validation_status == MCC_VALIDATION_STATUS_INVALID_TYPE) {
			return MCC_VALIDATION_STATUS_INVALID_TYPE;
		}
		// ignore undefined identifiers (are catched later)

		next_param = next_param->next_parameter;
		next_argument = next_argument->next_expr;
	}
	return MCC_VALIDATION_STATUS_VALID;
}
