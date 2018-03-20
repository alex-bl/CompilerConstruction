#include <assert.h>

#include "mCc/ast/visit/ast_visit_expression.h"
#include "mCc/ast/visit/ast_visit_literal.h"

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
		visit_if_post_order(expression, visitor->expression_literal, visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		visit_if_pre_order(expression, visitor->expression_binary_op, visitor);
		mCc_ast_visit_expression(expression->lhs, visitor);
		mCc_ast_visit_expression(expression->rhs, visitor);
		visit_if_post_order(expression, visitor->expression_binary_op, visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		visit_if_pre_order(expression, visitor->expression_parenth, visitor);
		mCc_ast_visit_expression(expression->expression, visitor);
		visit_if_post_order(expression, visitor->expression_parenth, visitor);
		break;

	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
		/*TODO*/
		break;

	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		/*TODO*/
		break;

	case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
		/*TODO*/
		break;
	}

	visit_if_post_order(expression, visitor->expression, visitor);
}
