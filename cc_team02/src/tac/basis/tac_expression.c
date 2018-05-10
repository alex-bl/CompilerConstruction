#include "mCc/tac/basis/tac_expression.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

// const char *mCc_tac_binary_op(enum mCc_ast_binary_op op) {}

// const char *mCc_tac_unary_op(enum mCc_ast_unary_op op) {}

void mCc_tac_expression_literal(struct mCc_ast_expression *expression,
                                void *data)
{
	assert(expression);
	assert(data);

	struct mCc_tac_identifier *argument1;

	switch (expression->data_type) {
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

	tac_new_element(MCC_TAC_OPERATION_EMPTY, argument1, NULL, NULL);
}

void mCc_tac_expression_binary_op(struct mCc_ast_expression *expression,
                                  void *data)
{
	assert(expression);
	assert(data);

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
	default: operation = MCC_TAC_OPERATION_EMPTY; break;
	}

	tac_new_element(operation, tac_new_identifier(expression->lhs),
	                tac_new_identifier(expression->rhs), NULL);
}

void mCc_tac_expression_parenth(struct mCc_ast_expression *expression,
                                void *data)
{
	assert(expression);
	assert(data);

	// TODO add tac element
}

void mCc_tac_expression_identifier(struct mCc_ast_expression *expression,
                                   void *data)
{
	assert(expression);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY,
	                tac_new_identifier(expression->identifier->identifier_name),
	                NULL, NULL);
}

void mCc_tac_expression_identifier_array(struct mCc_ast_expression *expression,
                                         void *data)
{
	assert(expression);
	assert(data);

	tac_new_element(
	    MCC_TAC_OPERATION_EMPTY,
	    tac_new_identifier(expression->array_identifier->identifier_name),
	    tac_new_identifier(expression->array_index_expression), NULL);
}

void mCc_tac_expression_function_call(struct mCc_ast_expression *expression,
                                      void *data)
{
	assert(expression);
	assert(data);

	tac_new_element(MCC_TAC_OPARATION_PROCEDURAL_CALL,
	                tac_new_identifier(
	                    expression->function_call->identifier->identifier_name),
	                NULL, NULL);
}

void mCc_tac_expression_unary_op(struct mCc_ast_expression *expression,
                                 void *data)
{
	assert(expression);
	assert(data);

	enum mCc_tac_operation operation;

	switch (expression->unary_op) {
	case MCC_AST_UNARY_OP_MINUS:
		operation = MCC_TAC_OPARATION_UNARY_OP_MINUS;
		break;
	case MCC_AST_UNARY_OP_NEGATION:
		operation = MCC_TAC_OPARATION_UNARY_OP_NEGATION;
		break;
	default: operation = MCC_TAC_OPERATION_EMPTY; break;
	}

	tac_new_element(operation, tac_new_identifier(expression->unary_rhs), NULL,
	                NULL);
}
