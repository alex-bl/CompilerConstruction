#include <stddef.h>

#include "mCc/ast/ast_program.h"

struct mCc_ast_statement
mCc_ast_new_if_statement(struct mCc_ast_expression *condition_expr,
                         struct mCc_ast_statement *if_stmt,
                         struct mCc_ast_statement *else_stmt)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_statement
mCc_ast_new_while_statement(struct mCc_ast_expression *loop_expr,
                            struct mCc_ast_statement *while_stmt)
{
	/* TODO */
	return NULL;
}
struct mCc_ast_statement
mCc_ast_new_return_statement(struct mCc_ast_statement *return_stmt)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_statement
mCc_ast_new_compound_statement(struct mCc_ast_compound_statement *compound_stmt)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_compound_statement
mCc_ast_new_compound_statement_build(struct mCc_ast_statement *_stmts,
                                     long nr_of_stmts)
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
