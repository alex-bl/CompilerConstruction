#include "mCc/tac/basis/tac_expression.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

//const char *mCc_tac_binary_op(enum mCc_ast_binary_op op) {}

//const char *mCc_tac_unary_op(enum mCc_ast_unary_op op) {}

void mCc_tac_expression_literal(struct mCc_ast_expression *expression,
                                void *data)
{
	assert(expression);
	assert(data);

	struct mCc_tac_identifier *argument1;

	switch (expression->data_type) {
	case MCC_AST_DATA_TYPE_INT:
		argument1 = tac_new_identifier((char*) &expression->literal->i_value);
		break;
	case MCC_AST_DATA_TYPE_FLOAT:
		argument1 = tac_new_identifier((char*) &expression->literal->f_value);
		break;
	case MCC_AST_DATA_TYPE_BOOL:
		argument1 = tac_new_identifier((char*) &expression->literal->b_value);
		break;
	case MCC_AST_DATA_TYPE_STRING:
		argument1 = tac_new_identifier((char*) &expression->literal->s_value);
		break;
	default: argument1 = NULL; break;
	}

	tac_new_element(MCC_TAC_OPARATION_COPY, argument1, NULL, argument1);
}

void mCc_tac_expression_binary_op(struct mCc_ast_expression *expression,
                                  void *data)
{
	assert(expression);
	assert(data);
}

void mCc_tac_expression_parenth(struct mCc_ast_expression *expression,
                                void *data)
{
	assert(expression);
	assert(data);
}

void mCc_tac_expression_identifier(struct mCc_ast_expression *expression,
                                   void *data)
{
	assert(expression);
	assert(data);
}

void mCc_tac_expression_identifier_array(struct mCc_ast_expression *expression,
                                         void *data)
{
	assert(expression);
	assert(data);
}

void mCc_tac_expression_function_call(struct mCc_ast_expression *expression,
                                      void *data)
{
	assert(expression);
	assert(data);
}

void mCc_tac_expression_unary_op(struct mCc_ast_expression *expression,
                                 void *data)
{
	assert(expression);
	assert(data);
}
