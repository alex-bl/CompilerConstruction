#include <stddef.h>

#include "mCc/ast/basis/ast_statement.h"

struct mCc_ast_statement *
mCc_ast_new_if_statement(struct mCc_ast_expression *condition_expr,
                         struct mCc_ast_statement *if_stmt,
                         struct mCc_ast_statement *else_stmt)
{
	struct mCc_ast_statement *statement = malloc(sizeof(*statement));
	if (!statement) {
		return NULL;
	}

	statement->statement_type=MCC_AST_STATEMENT_IF;
	statement->condition_expression=condition_expr;
	statement->if_statement=if_stmt;
	statement->else_statement=else_stmt;

	return statement;
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
mCc_ast_new_expression_statement(struct mCc_ast_expression *expression_stmt)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_statement *
mCc_ast_new_declaration_statement(struct mCc_ast_declaration *declaration)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_statement *
mCc_ast_new_assign_statement(struct mCc_ast_assignment *assignment)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_statement(struct mCc_ast_statement *stmt)
{
	/* TODO */
}
