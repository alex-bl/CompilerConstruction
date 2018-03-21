#include <stddef.h>

#include "mCc/ast/basis/ast_declaration.h"

struct mCc_ast_declaration *
mCc_ast_new_primitive_declaration(enum mCc_ast_literal_type data_type,
                                  struct mCc_ast_identifier *identifier)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_declaration *
mCc_ast_new_array_declaration(enum mCc_ast_literal_type data_type,
                              struct mCc_ast_identifier *identifier,
                              size_t size)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_declaration(struct mCc_ast_declaration *name)
{
	/* TODO */
}
