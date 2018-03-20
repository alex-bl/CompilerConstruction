#include <stddef.h>

#include "mCc/ast/basis/ast_statement.h"

struct mCc_ast_statement *
mCc_ast_new_if_statement(struct mCc_ast_expression *condition_expr,
                         struct mCc_ast_statement *if_stmt,
                         struct mCc_ast_statement *else_stmt)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_statement *
mCc_ast_new_while_statement(struct mCc_ast_expression *loop_expr,
                            struct mCc_ast_statement *while_stmt)
{
	/* TODO */
	return NULL;
}
struct mCc_ast_statement *
mCc_ast_new_return_statement(struct mCc_ast_statement *return_stmt)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_statement *
mCc_ast_new_compound_statement(struct mCc_ast_statement *stmt, struct mCc_ast_statement *to_append)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_if_statement(struct mCc_ast_statement *stmt)
{
	/* TODO */
}

void mCc_ast_delete_while_statement(struct mCc_ast_statement *stmt)
{
	/* TODO */
}

void mCc_ast_delete_return_statement(struct mCc_ast_statement *stmt)
{
	/* TODO */
}

void mCc_ast_delete_compound_statement(struct mCc_ast_statement *stmt)
{
	/* TODO */
}
