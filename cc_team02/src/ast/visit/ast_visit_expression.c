#include "ast_visit_expression.h"

#include <assert.h>

#include "ast_visit_function.h"
#include "ast_visit_identifier.h"
#include "ast_visit_literal.h"

void mCc_ast_visit_optional_expression(struct mCc_ast_expression *expr,
                                       struct mCc_ast_visitor *visitor)
{
	if (expr) {
		mCc_ast_visit_expression(expr, visitor);
	}
}

void mCc_ast_visit_expression(struct mCc_ast_expression *expression,
                              struct mCc_ast_visitor *visitor)
{
	assert(expression);
	assert(visitor);

	visit_if_pre_order(expression, visitor->expression, visitor);
	visit_if_both_order(expression, visitor->expression, visitor);

	switch (expression->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL:
		visit_if_pre_order(expression, visitor->expression_literal, visitor);
		visit_if_both_order(expression, visitor->expression_literal, visitor);

		mCc_ast_visit_literal(expression->literal, visitor);

		visit_if_post_order(expression, visitor->expression_literal, visitor);
		visit_if_both_order(expression, visitor->expression_literal_post_order, visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		visit_if_pre_order(expression, visitor->expression_binary_op, visitor);
		visit_if_both_order(expression, visitor->expression_binary_op, visitor);

		mCc_ast_visit_expression(expression->lhs, visitor);
		mCc_ast_visit_expression(expression->rhs, visitor);

		visit_if_post_order(expression, visitor->expression_binary_op, visitor);
		visit_if_both_order(expression, visitor->expression_binary_op_post_order, visitor);

		break;

	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		visit_if_pre_order(expression, visitor->expression_parenth, visitor);
		visit_if_both_order(expression, visitor->expression_parenth, visitor);

		mCc_ast_visit_expression(expression->expression, visitor);

		visit_if_post_order(expression, visitor->expression_parenth, visitor);
		visit_if_both_order(expression, visitor->expression_parenth_post_order, visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
		visit_if_pre_order(expression, visitor->expression_function_call,
		                   visitor);
		visit_if_both_order(expression, visitor->expression_function_call,
		                   visitor);

		mCc_ast_visit_function_call(expression->function_call, visitor);

		visit_if_post_order(expression, visitor->expression_function_call,
		                    visitor);
		visit_if_both_order(expression, visitor->expression_function_call_post_order,
		                   visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		visit_if_pre_order(expression, visitor->expression_identifier, visitor);
		visit_if_both_order(expression, visitor->expression_identifier, visitor);

		mCc_ast_visit_identifier(expression->identifier, visitor);

		visit_if_post_order(expression, visitor->expression_identifier,
		                    visitor);
		visit_if_both_order(expression, visitor->expression_identifier_post_order, visitor);

		break;

	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
		visit_if_pre_order(expression, visitor->expression_array_identifier,
		                   visitor);
		visit_if_both_order(expression, visitor->expression_array_identifier,
		                   visitor);

		mCc_ast_visit_identifier(expression->array_identifier, visitor);
		mCc_ast_visit_expression(expression->array_index_expression, visitor);

		visit_if_post_order(expression, visitor->expression_array_identifier,
		                    visitor);
		visit_if_both_order(expression, visitor->expression_array_identifier_post_order,
		                   visitor);

		break;

	case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
		visit_if_pre_order(expression, visitor->expression_unary_op, visitor);
		visit_if_both_order(expression, visitor->expression_unary_op, visitor);

		mCc_ast_visit_expression(expression->unary_rhs, visitor);

		visit_if_post_order(expression, visitor->expression_unary_op, visitor);
		visit_if_both_order(expression, visitor->expression_unary_op_post_order, visitor);

		break;
	}

	visit_if_post_order(expression, visitor->expression, visitor);
	visit_if_both_order(expression, visitor->expression_post_order, visitor);

	mCc_ast_visit_optional_expression(expression->next_expr, visitor);
}
