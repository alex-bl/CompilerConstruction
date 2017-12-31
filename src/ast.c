#include "mCc/ast.h"

#include <assert.h>
#include <stdlib.h>

/* ------------------------------------------------------------- Expressions */

struct mC_ast_expression *
mC_ast_new_expression_literal(struct mC_ast_literal *literal)
{
	assert(literal);

	struct mC_ast_expression *expr = malloc(sizeof(struct mC_ast_expression));
	if (!expr) {
		return NULL;
	}

	expr->type = MC_AST_EXPRESSION_TYPE_LITERAL;
	expr->literal = literal;
	return expr;
}

struct mC_ast_expression *
mC_ast_new_expression_parenth(struct mC_ast_expression *expression)
{
	assert(expression);

	struct mC_ast_expression *expr = malloc(sizeof(struct mC_ast_expression));

	if (!expr) {
		return NULL;
	}

	expr->type = MC_AST_EXPRESSION_TYPE_PARENTH;
	expr->expression = expression;
	return expr;
}

struct mC_ast_expression *
mC_ast_new_expression_binary_op(enum mC_ast_binary_op op,
                                struct mC_ast_expression *lhs,
                                struct mC_ast_expression *rhs)
{
	assert(lhs);
	assert(rhs);

	struct mC_ast_expression *expr = malloc(sizeof(struct mC_ast_expression));
	if (!expr) {
		return NULL;
	}

	expr->type = MC_AST_EXPRESSION_TYPE_BINARY_OP;
	expr->op = op;
	expr->lhs = lhs;
	expr->rhs = rhs;
	return expr;
}

void mC_ast_delete_expression(struct mC_ast_expression *expression)
{
	assert(expression);

	switch (expression->type) {
		case MC_AST_EXPRESSION_TYPE_LITERAL:
			mC_ast_delete_literal(expression->literal);
			break;

		case MC_AST_EXPRESSION_TYPE_BINARY_OP:
			mC_ast_delete_expression(expression->lhs);
			mC_ast_delete_expression(expression->rhs);
			break;

		case MC_AST_EXPRESSION_TYPE_PARENTH:
			mC_ast_delete_expression(expression->expression);
			break;
	}

	free(expression);
}

/* ---------------------------------------------------------------- Literals */

struct mC_ast_literal *mC_ast_new_literal_int(long value)
{
	struct mC_ast_literal *lit = malloc(sizeof(struct mC_ast_literal));
	if (!lit) {
		return NULL;
	}

	lit->type = MC_AST_LITERAL_TYPE_INT;
	lit->i_value = value;
	return lit;
}

struct mC_ast_literal *mC_ast_new_literal_float(double value)
{
	struct mC_ast_literal *lit = malloc(sizeof(struct mC_ast_literal));
	if (!lit) {
		return NULL;
	}

	lit->type = MC_AST_LITERAL_TYPE_FLOAT;
	lit->f_value = value;
	return lit;
}

void mC_ast_delete_literal(struct mC_ast_literal *literal)
{
	assert(literal);
	free(literal);
}
