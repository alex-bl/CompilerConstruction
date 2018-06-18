#include <assert.h>

#include "basic_tac.h"
#include "tac_expression.h"
#include "tac_utils.h"

enum mCc_tac_operation tac_helper_get_primitive_assignment_tac_operation(
    enum mCc_ast_data_type return_expression_operation)
{
	switch (return_expression_operation) {
	case MCC_AST_DATA_TYPE_INT:
		return MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_INT;
		break;
	case MCC_AST_DATA_TYPE_FLOAT:
		return MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_FLOAT;
		break;
	case MCC_AST_DATA_TYPE_BOOL:
		return MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_BOOL;
		break;
	case MCC_AST_DATA_TYPE_STRING:
		return MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_STRING;
		break;
	default: return MCC_TAC_OPARATION_EMPTY; break;
	}
}

static enum mCc_tac_operation tac_helper_get_function_assignment_tac_operation(
    enum mCc_ast_data_type return_expression_operation)
{
	switch (return_expression_operation) {
	case MCC_AST_DATA_TYPE_INT:
		return MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_INT;
		break;
	case MCC_AST_DATA_TYPE_FLOAT:
		return MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_FLOAT;
		break;
	case MCC_AST_DATA_TYPE_BOOL:
		return MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_BOOL;
		break;
	case MCC_AST_DATA_TYPE_STRING:
		return MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_STRING;
		break;
	default: return MCC_TAC_OPARATION_EMPTY; break;
	}
}

static bool is_function_call_assignment(struct mCc_ast_assignment *assignment)
{
	return assignment->assignment_type == MCC_AST_ASSIGNMENT_PRIMITIVE &&
	       assignment->assigned_expression->type ==
	           MCC_AST_EXPRESSION_TYPE_CALL_EXPR;
}

// x:= y
struct mCc_tac_element *
mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                             struct mCc_tac_element *previous_tac)
{
	assert(assignment);
	assert(assignment->assigned_expression);
	assert(previous_tac);

	struct mCc_tac_element *tac_assigned_expression =
	    helper_get_tac_of_expression(assignment->assigned_expression,
	                                 previous_tac);

	// puts scope level behind the variable name and return tac_identifier
	struct mCc_tac_identifier *name_identifier =
	    mCc_helper_concat_name_and_scope(
	        assignment->identifier->identifier_name,
	        assignment->identifier->symtab_info->scope_level);

	enum mCc_ast_data_type ast_data_type =
	    assignment->identifier->symtab_info->data_type;

	enum mCc_tac_operation assignment_operation =
	    tac_helper_get_primitive_assignment_tac_operation(
	        assignment->assigned_expression->data_type);

	struct mCc_tac_identifier *tac_arg_1 =
	    mCc_tac_create_from_tac_identifier(tac_assigned_expression->tac_result);

	struct mCc_tac_element *tac =
	    tac_new_element(assignment_operation, tac_arg_1, NULL, name_identifier,
	                    mCc_tac_map_from_ast_data_type(ast_data_type), 0);

	// treat function-call
	if (is_function_call_assignment(assignment)) {
		tac_arg_1->type = MCC_IDENTIFIER_TAC_TYPE_FUNCTION_CALL;
		tac->tac_operation =
		    tac_helper_get_function_assignment_tac_operation(ast_data_type);
	}

	mCc_tac_connect_tac_entry(tac_assigned_expression, tac);

	return tac;
}

enum mCc_tac_operation tac_helper_get_array_assignment_tac_operation(
    enum mCc_ast_data_type return_expression_operation)
{
	switch (return_expression_operation) {
	case MCC_AST_DATA_TYPE_INT:
		return MCC_TAC_OPARATION_ASSIGN_ARRAY_INT;
		break;
	case MCC_AST_DATA_TYPE_FLOAT:
		return MCC_TAC_OPARATION_ASSIGN_ARRAY_FLOAT;
		break;
	case MCC_AST_DATA_TYPE_BOOL:
		return MCC_TAC_OPARATION_ASSIGN_ARRAY_BOOL;
		break;
	case MCC_AST_DATA_TYPE_STRING:
		return MCC_TAC_OPARATION_ASSIGN_ARRAY_STRING;
		break;
	default: return MCC_TAC_OPARATION_EMPTY; break;
	}
}

// y[i]:=x
struct mCc_tac_element *
mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                         struct mCc_tac_element *previous_tac)
{
	assert(assignment);
	assert(assignment->array_index_expression);
	assert(assignment->array_assigned_expression);
	assert(previous_tac);

	struct mCc_tac_element *tac_assigned_expression =
	    helper_get_tac_of_expression(assignment->array_assigned_expression,
	                                 previous_tac);

	struct mCc_tac_element *tac_index_expression = helper_get_tac_of_expression(
	    assignment->array_index_expression, tac_assigned_expression);

	// puts scope level behind the variable name and return
	// tac_identifier
	struct mCc_tac_identifier *name_identifier =
	    mCc_helper_concat_name_and_scope(
	        assignment->identifier->identifier_name,
	        assignment->identifier->symtab_info->scope_level);

	enum mCc_ast_data_type ast_data_type =
	    assignment->identifier->symtab_info->data_type;

	enum mCc_tac_operation assignment_operation =
	    tac_helper_get_array_assignment_tac_operation(
	        assignment->array_assigned_expression->data_type);

	struct mCc_tac_element *tac = tac_new_element(
	    assignment_operation,
	    mCc_tac_create_from_tac_identifier(tac_assigned_expression->tac_result),
	    mCc_tac_create_from_tac_identifier(tac_index_expression->tac_result),
	    name_identifier, mCc_tac_map_from_ast_data_type(ast_data_type), 0);

	mCc_tac_connect_tac_entry(tac_index_expression, tac);

	return tac;
}
