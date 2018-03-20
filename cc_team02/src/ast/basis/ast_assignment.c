
#include "mCc/ast/basis/ast_assignment.h"
#include <stddef.h>

struct mCc_ast_assignment *mCc_ast_new_primitive_assignment(
    struct mCc_ast_identifier *identifier,
    struct mCc_ast_expression *assigned_expresion_value)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_assignment *
mCc_ast_new_array_assignment(struct mCc_ast_identifier *identifier,
                             struct mCc_ast_expression *index,
                             struct mCc_ast_expression *value)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_primitive_assignment(struct mCc_ast_assignment *name)
{
	/* TODO */
}

void mCc_ast_delete_array_assignment(struct mCc_ast_assignment *name)
{
	/* TODO */
}
