#include <assert.h>

#include "mCc/ast/visit/ast_visit_expression.h"
#include "mCc/ast/visit/ast_visit_function.h"
#include "mCc/ast/visit/ast_visit_identifier.h"
#include "mCc/ast/visit/ast_visit_literal.h"

void mCc_visit_next_expression(struct mCc_ast_expression *expr,
                               struct mCc_ast_visitor *visitor)
{
	if (expr->next_expr) {
		mCc_ast_visit_expression(expr->next_expr, visitor);
	}
}

void mCc_ast_visit_expression(struct mCc_ast_expression *expression,
                              struct mCc_ast_visitor *visitor)
{
	assert(expression);
	assert(visitor);

	visit_if_pre_order(expression, visitor->expression, visitor);

	switch (expression->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL:
		visit_if_pre_order(expression, visitor->expression_literal, visitor);
		mCc_ast_visit_literal(expression->literal, visitor);

		mCc_visit_next_expression(expression, visitor);

		visit_if_post_order(expression, visitor->expression_literal, visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		visit_if_pre_order(expression, visitor->expression_binary_op, visitor);
		mCc_ast_visit_expression(expression->lhs, visitor);
		mCc_ast_visit_expression(expression->rhs, visitor);

		mCc_visit_next_expression(expression, visitor);

		visit_if_post_order(expression, visitor->expression_binary_op, visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		visit_if_pre_order(expression, visitor->expression_parenth, visitor);
		mCc_ast_visit_expression(expression->expression, visitor);

		mCc_visit_next_expression(expression, visitor);

		visit_if_post_order(expression, visitor->expression_parenth, visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
		visit_if_pre_order(expression, visitor->expression_function_call,
		                   visitor);
		mCc_ast_visit_function_call(expression->function_call, visitor);

		mCc_visit_next_expression(expression, visitor);

		visit_if_post_order(expression, visitor->expression_function_call,
		                    visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		visit_if_pre_order(expression, visitor->expression_identifier, visitor);
		mCc_ast_visit_identifier(expression->identifier, visitor);

		mCc_visit_next_expression(expression, visitor);

		visit_if_post_order(expression, visitor->expression_identifier,
		                    visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
		visit_if_pre_order(expression, visitor->expression_array_identifier,
		                   visitor);
		mCc_ast_visit_identifier(expression->array_identifier, visitor);
		mCc_ast_visit_expression(expression->array_index_expression, visitor);

		mCc_visit_next_expression(expression, visitor);

		visit_if_post_order(expression, visitor->expression_array_identifier,
		                    visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
		visit_if_pre_order(expression, visitor->expression_unary_op, visitor);
		mCc_ast_visit_expression(expression->unary_rhs, visitor);

		mCc_visit_next_expression(expression, visitor);

		visit_if_post_order(expression, visitor->expression_unary_op, visitor);

		break;
	}

	visit_if_post_order(expression, visitor->expression, visitor);
}
