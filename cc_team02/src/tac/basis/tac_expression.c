#include "tac_expression.h"

#include <assert.h>

#include "basic_tac.h"
#include "tac_function.h"

struct mCc_tac_element *
helper_get_tac_of_expression(struct mCc_ast_expression *expression,
                             struct mCc_tac_element *previous_tac)
{
	struct mCc_tac_element *tac_expression;

	switch (expression->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL:
		tac_expression = mCc_tac_expression_literal(expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		tac_expression = mCc_tac_expression_binary_op(expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		tac_expression = mCc_tac_expression_parenth(expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		tac_expression =
		    mCc_tac_expression_identifier(expression, previous_tac);
		break;
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
	}
	mCc_tac_connect_tac_entry(previous_tac, tac_expression);
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

	struct mCc_tac_identifier *argument1;

	switch (expression->literal->type) {
	case MCC_AST_DATA_TYPE_INT:
		argument1 = tac_new_identifier((char *)&expression->literal->i_value);
		break;
	case MCC_AST_DATA_TYPE_FLOAT:
		argument1 = tac_new_identifier((char *)&expression->literal->f_value);
		break;
	case MCC_AST_DATA_TYPE_BOOL:
		argument1 = tac_new_identifier((char *)&expression->literal->b_value);
		break;
	case MCC_AST_DATA_TYPE_STRING:
		argument1 = tac_new_identifier((char *)&expression->literal->s_value);
		break;
	default: argument1 = NULL; break;
	}

	// has no identifier -
	// tac_new_identifier(expression->identifier->identifier_name)
	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, NULL, NULL, argument1,
	                    MCC_TAC_TYPE_NO_TYPE, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

struct mCc_tac_element *
mCc_tac_expression_binary_op(struct mCc_ast_expression *expression,
                             struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	enum mCc_tac_operation operation;

	switch (expression->op) {
	case MCC_AST_BINARY_OP_ADD:
		operation = MCC_TAC_OPARATION_BINARY_OP_ADD;
		break;
	case MCC_AST_BINARY_OP_SUB:
		operation = MCC_TAC_OPARATION_BINARY_OP_SUB;
		break;
	case MCC_AST_BINARY_OP_MUL:
		operation = MCC_TAC_OPARATION_BINARY_OP_MUL;
		break;
	case MCC_AST_BINARY_OP_DIV:
		operation = MCC_TAC_OPARATION_BINARY_OP_DIV;
		break;
	case MCC_AST_BINARY_OP_LESS_THAN:
		operation = MCC_TAC_OPARATION_BINARY_OP_LESS_THAN;
		break;
	case MCC_AST_BINARY_OP_GREATER_THAN:
		operation = MCC_TAC_OPARATION_BINARY_OP_GREATER_THAN;
		break;
	case MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN:
		operation = MCC_TAC_OPARATION_BINARY_OP_LESS_OR_EQUALS_THAN;
		break;
	case MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN:
		operation = MCC_TAC_OPARATION_BINARY_OP_GREATER_OR_EQUALS_THAN;
		break;
	case MCC_AST_BINARY_OP_AND:
		operation = MCC_TAC_OPARATION_BINARY_OP_AND;
		break;
	case MCC_AST_BINARY_OP_OR:
		operation = MCC_TAC_OPARATION_BINARY_OP_OR;
		break;
	case MCC_AST_BINARY_OP_EQUALS:
		operation = MCC_TAC_OPARATION_BINARY_OP_EQUALS;
		break;
	case MCC_AST_BINARY_OP_NOT_EQUALS:
		operation = MCC_TAC_OPARATION_BINARY_OP_NOT_EQUALS;
		break;
	default: operation = MCC_TAC_OPARATION_EMPTY; break;
	}

	struct mCc_tac_element *tac_lhs =
	    helper_get_tac_of_expression(expression->lhs, previous_tac);

	struct mCc_tac_element *tac_rhs =
	    helper_get_tac_of_expression(expression->rhs, tac_lhs);

	struct mCc_tac_element *tac =
	    tac_new_element(operation, tac_lhs->tac_result, tac_lhs->tac_result,
	                    NULL, MCC_TAC_TYPE_NO_TYPE, NULL);
	mCc_tac_connect_tac_entry(tac_rhs, tac);
	return tac;
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
	assert(previous_tac);

	// expression->identifier

	// TODO check if that is correct and needed
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, NULL, NULL,
	    tac_new_identifier(expression->identifier->identifier_name),
	    MCC_TAC_TYPE_NO_TYPE, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

struct mCc_tac_element *
mCc_tac_expression_identifier_array(struct mCc_ast_expression *expression,
                                    struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	// TODO check if that is correct and needed
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, NULL, NULL,
	    tac_new_identifier(expression->array_identifier->identifier_name),
	    MCC_TAC_TYPE_NO_TYPE, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

struct mCc_tac_element *
mCc_tac_expression_function_call(struct mCc_ast_expression *expression,
                                 struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	struct mCc_tac_element *tac =
	    mCc_tac_function_call(expression->function_call, previous_tac);

	/*struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_PROCEDURAL_CALL,
	    tac_new_identifier(
	        expression->function_call->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);*/
	return tac;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_expression_unary_op(struct mCc_ast_expression *expression,
                            struct mCc_tac_element *previous_tac)
{
	assert(expression);
	assert(previous_tac);

	enum mCc_tac_operation operation;

	switch (expression->unary_op) {
	case MCC_AST_UNARY_OP_MINUS:
		operation = MCC_TAC_OPARATION_UNARY_OP_MINUS;
		break;
	case MCC_AST_UNARY_OP_NEGATION:
		operation = MCC_TAC_OPARATION_UNARY_OP_NEGATION;
		break;
	}

	struct mCc_tac_element *tac_unary_rhs_expression =
	    helper_get_tac_of_expression(expression->unary_rhs, previous_tac);

	struct mCc_tac_element *tac =
	    tac_new_element(operation, tac_unary_rhs_expression->tac_result, NULL,
	                    NULL, MCC_TAC_TYPE_NO_TYPE, NULL);
	mCc_tac_connect_tac_entry(tac_unary_rhs_expression, tac);
	return tac;
}
