#include "mCc/ast_visit.h"

#include <assert.h>

#define visit(callback, ...) \
	do { \
		if (callback) { \
			(callback)(__VA_ARGS__); \
		} \
	} while (0)

#define visit_if(cond, callback, ...) \
	do { \
		if (cond) { \
			visit(callback, ##__VA_ARGS__); \
		} \
	} while (0)

#define visit_if_pre(order_, callback, ...) \
	visit_if((order_) == MCC_AST_VISIT_PRE_ORDER, callback, ##__VA_ARGS__)

#define visit_if_post(order_, callback, ...) \
	visit_if((order_) == MCC_AST_VISIT_POST_ORDER, callback, ##__VA_ARGS__)

void mCc_ast_visit_expression_df(enum mCc_ast_visit_order order,
                                 struct mCc_ast_expression *expression,
                                 struct mCc_ast_visitor *visitor)
{
	assert(expression);
	assert(visitor);

	visit_if_pre(order, visitor->expression, expression, visitor->userdata);

	switch (expression->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL:
		visit_if_pre(order, visitor->expression_literal, expression,
		             visitor->userdata);
		mCc_ast_visit_literal(order, expression->literal, visitor);
		visit_if_post(order, visitor->expression_literal, expression,
		              visitor->userdata);
		break;

	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		visit_if_pre(order, visitor->expression_binary_op, expression,
		             visitor->userdata);
		mCc_ast_visit_expression_df(order, expression->lhs, visitor);
		mCc_ast_visit_expression_df(order, expression->rhs, visitor);
		visit_if_post(order, visitor->expression_binary_op, expression,
		              visitor->userdata);
		break;

	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		visit_if_pre(order, visitor->expression_parenth, expression,
		             visitor->userdata);
		mCc_ast_visit_expression_df(order, expression->expression, visitor);
		visit_if_post(order, visitor->expression_parenth, expression,
		              visitor->userdata);
		break;
	}

	visit_if_post(order, visitor->expression, expression, visitor->userdata);
}

void mCc_ast_visit_literal(enum mCc_ast_visit_order order,
                           struct mCc_ast_literal *literal,
                           struct mCc_ast_visitor *visitor)
{
	assert(literal);
	assert(visitor);

	visit_if_pre(order, visitor->literal, literal, visitor->userdata);

	switch (literal->type) {
	case MCC_AST_LITERAL_TYPE_INT:
		visit(visitor->literal_int, literal, visitor->userdata);
		break;

	case MCC_AST_LITERAL_TYPE_FLOAT:
		visit(visitor->literal_float, literal, visitor->userdata);
		break;
	}

	visit_if_post(order, visitor->literal, literal, visitor->userdata);
}
