#include "mCc/tac/basis/tac_expression.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

const char *mCc_tac_binary_op(enum mCc_ast_binary_op op)
{

}

const char *mCc_tac_unary_op(enum mCc_ast_unary_op op) {}

void mCc_tac_expression_literal(struct mCc_ast_expression *expression,
                                void *data)
{
	assert(expression);
	assert(data);
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
