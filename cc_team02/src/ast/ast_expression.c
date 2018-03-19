#include <stddef.h>

#include "mCc/ast/ast_expression.h"

struct mCc_ast_expression *
mCc_ast_new_expression_literal(struct mCc_ast_literal *literal)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_expression *
mCc_ast_new_expression_binary_op(enum mCc_ast_binary_op op,
                                 struct mCc_ast_expression *lhs,
                                 struct mCc_ast_expression *rhs)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_expression *
mCc_ast_new_expression_parenth(struct mCc_ast_expression *expression)
{
	/* TODO */
	return NULL;
}

/*added*/
struct mCc_ast_expression *
mCc_ast_new_expression_unary_op(struct mCc_ast_expression *expression)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_expression(struct mCc_ast_expression *expression)
{
	/* TODO */
}
