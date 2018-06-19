#include "tac_expression.h"

#include <assert.h>

#include "basic_tac.h"
#include "tac_function.h"
#include "tac_utils.h"

struct mCc_tac_element *
helper_get_tac_of_expression(struct mCc_ast_expression *expression,
                             struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	struct mCc_tac_element *tac_expression;

	switch (expression->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL:
		tac_expression = mCc_tac_expression_literal(expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		tac_expression = mCc_tac_expression_binary_op(expression, previous_tac);
		break;

		// returns the previous_tac -> can be removed?
	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		tac_expression = mCc_tac_expression_parenth(expression, previous_tac);
		break;
		// returns the previous_tac -> can be removed?
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		tac_expression =
		    mCc_tac_expression_identifier(expression, previous_tac);
		break;
		// returns the previous_tac -> can be removed?
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
		tac_expression =
		    mCc_tac_expression_identifier_array(expression, previous_tac);
		break;

	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
		tac_expression =
		    mCc_tac_expression_function_call(expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
		tac_expression = mCc_tac_expression_unary_op(expression, previous_tac);
		break;
	default: tac_expression = NULL; break;
	}

	// checking if the returned tac expression is the same as the
	// previous_tac!!!
	if (tac_expression == previous_tac) {
		tac_expression = NULL;
	}
	// mCc_tac_connect_tac_entry(previous_tac, tac_expression);
	return tac_expression;
}

struct mCc_tac_element *
mCc_tac_expression_literal(struct mCc_ast_expression *expression,
                           struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	/* MCC_AST_DATA_TYPE_VOID,
	MCC_AST_DATA_TYPE_INT,
	MCC_AST_DATA_TYPE_FLOAT,
	MCC_AST_DATA_TYPE_BOOL,
	MCC_AST_DATA_TYPE_STRING,*/

	enum mCc_tac_operation operation;
	struct mCc_tac_identifier *argument1;
	enum mCc_tac_type tac_type;

	switch (expression->literal->type) {
	case MCC_AST_DATA_TYPE_INT:
		operation = MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_INT;
		argument1 = tac_new_identifier_int(expression->literal->i_value);
		tac_type = MCC_TAC_TYPE_INTEGER;
		break;
	case MCC_AST_DATA_TYPE_FLOAT:
		operation = MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_FLOAT;
		argument1 = tac_new_identifier_float(expression->literal->f_value);
		tac_type = MCC_TAC_TYPE_FLOAT;
		break;
	case MCC_AST_DATA_TYPE_BOOL:
		operation = MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_BOOL;
		argument1 = tac_new_identifier_bool(expression->literal->b_value);
		tac_type = MCC_TAC_TYPE_INTEGER;
		break;
	case MCC_AST_DATA_TYPE_STRING:
		operation = MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_STRING;
		argument1 = tac_new_identifier(expression->literal->s_value);
		argument1->type = MCC_IDENTIFIER_TAC_TYPE_STRING;
		tac_type = MCC_TAC_TYPE_STRING;
		break;
	default:
		operation = MCC_TAC_OPARATION_EMPTY;
		argument1 = NULL;
		tac_type = MCC_TAC_TYPE_NO_TYPE;
		break;
	}

	struct mCc_tac_identifier *literal_label =
	    mCc_tac_create_new_lable_identifier();

	struct mCc_tac_element *tac =
	    tac_new_element(operation, argument1, NULL, literal_label, tac_type, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

static enum mCc_tac_operation
get_arithmetic_operation(struct mCc_ast_expression *expression,
                         enum mCc_tac_operation int_op,
                         enum mCc_tac_operation float_op)
{
	if (expression->data_type == MCC_AST_DATA_TYPE_INT) {
		return int_op;
	}
	return float_op;
}

static enum mCc_tac_operation
get_arithmetic_operation_logical(struct mCc_ast_expression *expression,
                                 enum mCc_tac_operation int_op,
                                 enum mCc_tac_operation float_op)
{
	if (expression->lhs->data_type == MCC_AST_DATA_TYPE_INT) {
		return int_op;
	}
	return float_op;
}

static enum mCc_tac_operation get_arithmetic_operation_with_bool(
    struct mCc_ast_expression *expression, enum mCc_tac_operation int_op,
    enum mCc_tac_operation float_op, enum mCc_tac_operation bool_op)
{
	if (expression->data_type == MCC_AST_DATA_TYPE_INT) {
		return int_op;
	} else if (expression->data_type == MCC_AST_DATA_TYPE_BOOL) {
		return bool_op;
	} else {
		return float_op;
	}
}

struct mCc_tac_element *
mCc_tac_expression_binary_op(struct mCc_ast_expression *expression,
                             struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(expression->lhs);
	assert(expression->rhs);
	assert(previous_tac);

	enum mCc_tac_operation operation;

	switch (expression->op) {
	case MCC_AST_BINARY_OP_ADD:
		operation = get_arithmetic_operation(
		    expression, MCC_TAC_OPARATION_BINARY_OP_ADD_INT,
		    MCC_TAC_OPARATION_BINARY_OP_ADD_FLOAT);
		break;
	case MCC_AST_BINARY_OP_SUB:
		operation = get_arithmetic_operation(
		    expression, MCC_TAC_OPARATION_BINARY_OP_SUB_INT,
		    MCC_TAC_OPARATION_BINARY_OP_SUB_FLOAT);
		break;
	case MCC_AST_BINARY_OP_MUL:
		operation = get_arithmetic_operation(
		    expression, MCC_TAC_OPARATION_BINARY_OP_MUL_INT,
		    MCC_TAC_OPARATION_BINARY_OP_MUL_FLOAT);
		break;
	case MCC_AST_BINARY_OP_DIV:
		operation = get_arithmetic_operation(
		    expression, MCC_TAC_OPARATION_BINARY_OP_DIV_INT,
		    MCC_TAC_OPARATION_BINARY_OP_DIV_FLOAT);
		break;
	case MCC_AST_BINARY_OP_GREATER_THAN:
		// operation = MCC_TAC_OPARATION_BINARY_OP_GREATER_THAN;
		operation = get_arithmetic_operation_logical(
		    expression, MCC_TAC_OPARATION_GREATER_INT,
		    MCC_TAC_OPARATION_GREATER_FLOAT);
		break;
	case MCC_AST_BINARY_OP_LESS_THAN:
		// operation = MCC_TAC_OPARATION_BINARY_OP_LESS_THAN;
		operation = get_arithmetic_operation_logical(
		    expression, MCC_TAC_OPARATION_LESS_INT,
		    MCC_TAC_OPARATION_LESS_FLOAT);
		break;
	case MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN:
		// operation = MCC_TAC_OPARATION_BINARY_OP_GREATER_OR_EQUALS_THAN;
		operation = get_arithmetic_operation_logical(
		    expression, MCC_TAC_OPARATION_GREATER_EQUALS_INT,
		    MCC_TAC_OPARATION_GREATER_EQUALS_FLOAT);
		break;
	case MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN:
		// operation = MCC_TAC_OPARATION_BINARY_OP_LESS_OR_EQUALS_THAN;
		operation = get_arithmetic_operation_logical(
		    expression, MCC_TAC_OPARATION_LESS_EQUALS_INT,
		    MCC_TAC_OPARATION_LESS_EQUALS_FLOAT);
		break;
	case MCC_AST_BINARY_OP_AND: operation = MCC_TAC_OPARATION_BINARY_AND; break;
	case MCC_AST_BINARY_OP_OR: operation = MCC_TAC_OPARATION_BINARY_OR; break;
	case MCC_AST_BINARY_OP_EQUALS:
		// operation = MCC_TAC_OPARATION_BINARY_OP_EQUALS;
		operation = get_arithmetic_operation_with_bool(
		    expression, MCC_TAC_OPARATION_EQUALS_INT,
		    MCC_TAC_OPARATION_EQUALS_FLOAT, MCC_TAC_OPARATION_EQUALS_BOOL);
		break;
	case MCC_AST_BINARY_OP_NOT_EQUALS:
		// operation = MCC_TAC_OPARATION_BINARY_OP_NOT_EQUALS;
		operation = get_arithmetic_operation_with_bool(
		    expression, MCC_TAC_OPARATION_NOT_EQUALS_INT,
		    MCC_TAC_OPARATION_NOT_EQUALS_FLOAT,
		    MCC_TAC_OPARATION_NOT_EQUALS_BOOL);
		break;
	default: operation = MCC_TAC_OPARATION_EMPTY; break;
	}

	struct mCc_tac_element *tac_lhs =
	    helper_get_tac_of_expression(expression->lhs, previous_tac);

	struct mCc_tac_element *tac_rhs =
	    helper_get_tac_of_expression(expression->rhs, tac_lhs);

	struct mCc_tac_identifier *operationlabel =
	    mCc_tac_create_new_lable_identifier();

	enum mCc_ast_data_type ast_data_type = expression->data_type;

	struct mCc_tac_element *tac = tac_new_element(
	    operation, mCc_tac_create_from_tac_identifier(tac_lhs->tac_result),
	    mCc_tac_create_from_tac_identifier(tac_rhs->tac_result), operationlabel,
	    mCc_tac_map_from_ast_data_type(ast_data_type), 0);
	mCc_tac_connect_tac_entry(tac_rhs, tac);
	return tac;

	// trying to fix bug, with wrong previous tac statement
	/*struct mCc_tac_identifier lhs;
	struct mCc_tac_identifier rhs;

	    struct mCc_tac_element *tac_lhs =
	        helper_get_tac_of_expression(expression->lhs, previous_tac);
	// if it is a complex statement - otherwise just take the bare expression
	if (tac_lhs != NULL) {
	    lhs = mCc_tac_create_from_tac_identifier(tac_lhs->tac_result);
	    previous_tac = tac_lhs;
	} else {
	    lhs = expression->lhs;
	}

	struct mCc_tac_element *tac_rhs =
	    helper_get_tac_of_expression(expression->rhs, previous_tac);

	struct mCc_tac_identifier *operationlabel =
	    mCc_tac_create_new_lable_identifier();

	struct mCc_tac_element *tac = tac_new_element(
	    operation, lhs, mCc_tac_create_from_tac_identifier(tac_rhs->tac_result),
	    operationlabel, MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(tac_rhs, tac);
	return tac;*/
}

struct mCc_tac_element *
mCc_tac_expression_parenth(struct mCc_ast_expression *expression,
                           struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	// TODO check if it is right
	struct mCc_tac_element *tac =
	    helper_get_tac_of_expression(expression->expression, previous_tac);

	return tac;
}

struct mCc_tac_element *
mCc_tac_expression_identifier(struct mCc_ast_expression *expression,
                              struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(expression->identifier->identifier_name);
	assert(previous_tac);

	// creates tac element just for and identifier concatenated with its scope
	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, NULL, NULL,
	                    mCc_helper_concat_name_and_scope(
	                        expression->identifier->identifier_name,
	                        expression->identifier->symtab_info->scope_level),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
	// return previous_tac;
}

static enum mCc_tac_operation
map_arr_index_type(enum mCc_ast_data_type ast_data_type)
{
	switch (ast_data_type) {
	case MCC_AST_DATA_TYPE_INT:
		return MCC_TAC_OPERATION_INT_ARR_INDEX_ACCESS;
	case MCC_AST_DATA_TYPE_FLOAT:
		return MCC_TAC_OPERATION_FLOAT_ARR_INDEX_ACCESS;
	case MCC_AST_DATA_TYPE_BOOL:
		return MCC_TAC_OPERATION_BOOL_ARR_INDEX_ACCESS;
	case MCC_AST_DATA_TYPE_STRING:
		return MCC_TAC_OPERATION_STRING_ARR_INDEX_ACCESS;
	default: return MCC_TAC_OPERATION_INT_ARR_INDEX_ACCESS;
	}
	return MCC_TAC_OPERATION_INT_ARR_INDEX_ACCESS;
}

struct mCc_tac_element *
mCc_tac_expression_identifier_array(struct mCc_ast_expression *expression,
                                    struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(expression->array_identifier);
	assert(expression->array_index_expression);
	assert(previous_tac);

	struct mCc_tac_element *array_expression_tac = helper_get_tac_of_expression(
	    expression->array_index_expression, previous_tac);

	enum mCc_ast_data_type ast_data_type = expression->data_type;

	// creates a new labels for the array with its index expression
	struct mCc_tac_element *tac = tac_new_element(
	    map_arr_index_type(ast_data_type),
	    mCc_helper_concat_name_and_scope(
	        expression->array_identifier->identifier_name,
	        expression->array_identifier->symtab_info->scope_level),
	    mCc_tac_create_from_tac_identifier(array_expression_tac->tac_result),
	    mCc_tac_create_new_lable_identifier(),
	    mCc_tac_map_from_ast_data_type(ast_data_type), 0);
	mCc_tac_connect_tac_entry(array_expression_tac, tac);
	return tac;
	// return previous_tac;
}

struct mCc_tac_element *
mCc_tac_expression_function_call(struct mCc_ast_expression *expression,
                                 struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	struct mCc_tac_element *tac =
	    mCc_tac_function_call(expression->function_call, previous_tac);

	return tac;
}

struct mCc_tac_element *
mCc_tac_expression_unary_op(struct mCc_ast_expression *expression,
                            struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	enum mCc_tac_operation operation;

	switch (expression->unary_op) {
	case MCC_AST_UNARY_OP_MINUS:
		if (expression->data_type == MCC_AST_DATA_TYPE_INT) {
			operation = MCC_TAC_OPARATION_UNARY_MINUS_INT;
		} else if (expression->data_type == MCC_AST_DATA_TYPE_FLOAT) {
			operation = MCC_TAC_OPARATION_UNARY_MINUS_FLOAT;
		}
		break;
	case MCC_AST_UNARY_OP_NEGATION:
		operation = MCC_TAC_OPARATION_UNARY_NEGATION;
		break;
	}

	struct mCc_tac_element *tac_unary_rhs_expression;
	tac_unary_rhs_expression =
	    helper_get_tac_of_expression(expression->unary_rhs, previous_tac);

	struct mCc_tac_identifier *operation_label =
	    mCc_tac_create_new_lable_identifier();

	enum mCc_ast_data_type ast_data_type = expression->data_type;

	struct mCc_tac_element *tac =
	    tac_new_element(operation,
	                    mCc_tac_create_from_tac_identifier(
	                        tac_unary_rhs_expression->tac_result),
	                    NULL, operation_label,
	                    mCc_tac_map_from_ast_data_type(ast_data_type), 0);
	mCc_tac_connect_tac_entry(tac_unary_rhs_expression, tac);
	return tac;
}
