#include "mCc/ast_visit.h"

#include <assert.h>

#define visit_unless_null(_f, _x, _y) \
	if (_f) { \
		(_f)((_x), (_y)); \
	}

void mC_ast_visit_expression_df_post(struct mC_ast_expression *expression,
                                     struct mC_ast_visitor *visitor)
{
	assert(expression);
	assert(visitor);

	switch (expression->type) {
		case MC_AST_EXPRESSION_TYPE_LITERAL:
			mC_ast_visit_literal_post(expression->literal, visitor);
			visit_unless_null(visitor->expression_literal, expression,
			                  visitor->data);
			break;

		case MC_AST_EXPRESSION_TYPE_BINARY_OP:
			mC_ast_visit_expression_df_post(expression->lhs, visitor);
			mC_ast_visit_expression_df_post(expression->rhs, visitor);
			visit_unless_null(visitor->expression_binary_op, expression,
			                  visitor->data);
			break;

		case MC_AST_EXPRESSION_TYPE_PARENTH:
			mC_ast_visit_expression_df_post(expression->expression, visitor);
			visit_unless_null(visitor->expression_parenth, expression,
			                  visitor->data);
			break;
	}

	visit_unless_null(visitor->expression, expression, visitor->data);
}

void mC_ast_visit_literal_post(struct mC_ast_literal *literal,
                               struct mC_ast_visitor *visitor)
{
	assert(literal);

	switch (literal->type) {
		case MC_AST_LITERAL_TYPE_INT:
			visit_unless_null(visitor->literal_int, literal, visitor->data);
			break;

		case MC_AST_LITERAL_TYPE_FLOAT:
			visit_unless_null(visitor->literal_float, literal, visitor->data);
			break;
	}

	visit_unless_null(visitor->literal, literal, visitor->data);
}
