#include "mCc/ast/basis/ast_expression.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct mCc_ast_expression *
mCc_ast_new_expression_literal(struct mCc_ast_literal *literal)
{
	assert(literal);

	struct mCc_ast_expression *expr = malloc(sizeof(*expr));
	if (!expr) {
		return NULL;
	}

	expr->type = MCC_AST_EXPRESSION_TYPE_LITERAL;
	expr->literal = literal;
	// set explicitly to null
	expr->next_expr = NULL;
	return expr;
}

struct mCc_ast_expression *
mCc_ast_new_expression_binary_op(enum mCc_ast_binary_op op,
                                 struct mCc_ast_expression *lhs,
                                 struct mCc_ast_expression *rhs)
{
	assert(lhs);
	assert(rhs);

	struct mCc_ast_expression *expr = malloc(sizeof(*expr));
	if (!expr) {
		return NULL;
	}

	expr->type = MCC_AST_EXPRESSION_TYPE_BINARY_OP;
	expr->op = op;
	expr->lhs = lhs;
	expr->rhs = rhs;
	// set explicitly to null
	expr->next_expr = NULL;
	return expr;
}

struct mCc_ast_expression *
mCc_ast_new_expression_parenth(struct mCc_ast_expression *expression)
{
	assert(expression);

	struct mCc_ast_expression *expr = malloc(sizeof(*expr));
	if (!expr) {
		return NULL;
	}

	expr->type = MCC_AST_EXPRESSION_TYPE_PARENTH;
	expr->expression = expression;
	// set explicitly to null
	expr->next_expr = NULL;
	return expr;
}

/*added*/
struct mCc_ast_expression *
mCc_ast_new_expression_unary_op(enum mCc_ast_unary_op op,
                                struct mCc_ast_expression *expression)
{
	assert(expression);

	struct mCc_ast_expression *expr = malloc(sizeof(*expr));
	if (!expr) {
		return NULL;
	}

	expr->type = MCC_AST_EXPRESSION_TYPE_UNARY_OP;
	expr->unary_op = op;
	expr->unary_rhs = expression;
	// set explicitly to null
	expr->next_expr = NULL;

	return expr;
}

struct mCc_ast_expression *
mCc_ast_new_expression_identifier(struct mCc_ast_identifier *identifier)
{
	assert(identifier);

	struct mCc_ast_expression *expr = malloc(sizeof(*expr));
	if (!expr) {
		return NULL;
	}

	expr->type = MCC_AST_EXPRESSION_TYPE_IDENTIFIER;
	expr->identifier = identifier;
	// set explicitly to null
	expr->next_expr = NULL;

	return expr;
}

struct mCc_ast_expression *mCc_ast_new_expression_array_identifier(
    struct mCc_ast_identifier *array_identifier,
    struct mCc_ast_expression *array_index_expression)
{
	assert(array_identifier);
	assert(array_index_expression);

	struct mCc_ast_expression *expr = malloc(sizeof(*expr));
	if (!expr) {
		return NULL;
	}

	expr->type = MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY;
	expr->array_identifier = array_identifier;
	expr->array_index_expression = array_index_expression;
	// set explicitly to null
	expr->next_expr = NULL;

	return expr;
}

struct mCc_ast_expression *mCc_ast_new_expression_function_call(
    struct mCc_ast_function_call *function_call)
{
	assert(function_call);

	struct mCc_ast_expression *expr = malloc(sizeof(*expr));
	if (!expr) {
		return NULL;
	}

	expr->type = MCC_AST_EXPRESSION_TYPE_CALL_EXPR;
	expr->function_call = function_call;
	// set explicitly to null
	expr->next_expr = NULL;

	return expr;
}

void mCc_ast_delete_expression(struct mCc_ast_expression *expression)
{
	assert(expression);

	switch (expression->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL:
		mCc_ast_delete_literal(expression->literal);
		break;

	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		mCc_ast_delete_expression(expression->lhs);
		mCc_ast_delete_expression(expression->rhs);
		break;

	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		mCc_ast_delete_expression(expression->expression);
		break;

	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
		mCc_ast_delete_function_call(expression->function_call);
		break;

	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		mCc_ast_delete_identifier(expression->identifier);
		break;

	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
		mCc_ast_delete_identifier(expression->array_identifier);
		mCc_ast_delete_expression(expression->array_index_expression);
		break;

	case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
		mCc_ast_delete_expression(expression->unary_rhs);
		break;
	}

	if (expression->next_expr) {
		mCc_ast_delete_expression(expression->next_expr);
	}

	free(expression);
}
