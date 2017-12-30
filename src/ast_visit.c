#include "mCc/ast_visit.h"

#include <assert.h>

#define visit(_f, _x, _y) \
	if (_f) { \
		(_f)(_x, _y); \
	}

#define visit_if(_c, _f, _x, _y) \
	if (_c) { \
		visit(_f, _x, _y); \
	}

#define visit_if_pre(_order, _f, _x, _y) \
	visit_if((_order) == MC_AST_VISIT_PRE_ORDER, _f, _x, _y)

#define visit_if_post(_order, _f, _x, _y) \
	visit_if((_order) == MC_AST_VISIT_POST_ORDER, _f, _x, _y)

void mC_ast_visit_expression_df(enum mC_ast_visit_order order,
                                struct mC_ast_expression *expression,
                                struct mC_ast_visitor *visitor)
{
	assert(expression);
	assert(visitor);

	visit_if_pre(order, visitor->expression, expression, visitor->data);

	switch (expression->type) {
		case MC_AST_EXPRESSION_TYPE_LITERAL:
			visit_if_pre(order, visitor->expression_literal, expression,
			             visitor->data);
			mC_ast_visit_literal(order, expression->literal, visitor);
			visit_if_post(order, visitor->expression_literal, expression,
			              visitor->data);
			break;

		case MC_AST_EXPRESSION_TYPE_BINARY_OP:
			visit_if_pre(order, visitor->expression_binary_op, expression,
			             visitor->data);
			mC_ast_visit_expression_df(order, expression->lhs, visitor);
			mC_ast_visit_expression_df(order, expression->rhs, visitor);
			visit_if_post(order, visitor->expression_binary_op, expression,
			              visitor->data);
			break;

		case MC_AST_EXPRESSION_TYPE_PARENTH:
			visit_if_pre(order, visitor->expression_parenth, expression,
			             visitor->data);
			mC_ast_visit_expression_df(order, expression->expression, visitor);
			visit_if_post(order, visitor->expression_parenth, expression,
			              visitor->data);
			break;
	}

	visit_if_post(order, visitor->expression, expression, visitor->data);
}

void mC_ast_visit_literal(enum mC_ast_visit_order order,
                          struct mC_ast_literal *literal,
                          struct mC_ast_visitor *visitor)
{
	assert(literal);
	assert(visitor);

	visit_if_pre(order, visitor->literal, literal, visitor->data);

	switch (literal->type) {
		case MC_AST_LITERAL_TYPE_INT:
			visit(visitor->literal_int, literal, visitor->data);
			break;

		case MC_AST_LITERAL_TYPE_FLOAT:
			visit(visitor->literal_float, literal, visitor->data);
			break;
	}

	visit_if_post(order, visitor->literal, literal, visitor->data);
}
