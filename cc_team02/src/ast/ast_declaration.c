#include <stddef.h>

#include "mCc/ast/ast_declaration.h"

struct mCc_ast_declaration *
mCc_ast_new_primitive_declaration(enum mCc_ast_literal_type data_type,
                                  const char *identifier)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_declaration *
mCc_ast_new_array_declaration(enum mCc_ast_literal_type data_type,
                              const char *identifier, size_t size)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_primitive_declaration(struct mCc_ast_declaration *name)
{
	/* TODO */
}

void mCc_ast_delete_array_declaration(struct mCc_ast_declaration *name)
{
	/* TODO */
}
