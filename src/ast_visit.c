#include "mCc/ast_visit.h"

#include <assert.h>

#define visit_unless_null(_f, _x, _y) \
	if (_f) { \
		(_f)((_x), (_y)); \
	}

void mC_ast_visit_expression(struct mC_ast_expression *expression,
                             struct mC_ast_visitor *visitor)
{
	assert(expression);
	assert(visitor);

	visit_unless_null(visitor->expression, expression, visitor->data);

	switch (expression->type) {
		case MC_AST_EXPRESSION_TYPE_LITERAL:
			visit_unless_null(visitor->expression_literal, expression,
			                  visitor->data);
			mC_ast_visit_literal(expression->literal, visitor);
			break;

		case MC_AST_EXPRESSION_TYPE_BINARY_OP:
			visit_unless_null(visitor->expression_binary_op, expression,
			                  visitor->data);
			mC_ast_visit_expression(expression->lhs, visitor);
			mC_ast_visit_expression(expression->rhs, visitor);
			break;

		case MC_AST_EXPRESSION_TYPE_PARENTH:
			visit_unless_null(visitor->expression_parenth, expression,
			                  visitor->data);
			mC_ast_visit_expression(expression->expression, visitor);
			break;
	}
}

void mC_ast_visit_literal(struct mC_ast_literal *literal,
                          struct mC_ast_visitor *visitor)
{
	assert(literal);

	visit_unless_null(visitor->literal, literal, visitor->data);

	switch (literal->type) {
		case MC_AST_LITERAL_TYPE_INT:
			visit_unless_null(visitor->literal_int, literal, visitor->data);
			break;

		case MC_AST_LITERAL_TYPE_FLOAT:
			visit_unless_null(visitor->literal_float, literal, visitor->data);
			break;
	}
}
