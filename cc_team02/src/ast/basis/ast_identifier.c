#include <stddef.h>

#include "mCc/ast/basis/ast_identifier.h"

struct mCc_ast_identifier *mCc_ast_new_identifier(const char *name)
{
	assert(name);

	struct mCc_ast_identifier *ident = malloc(sizeof(*ident));
	if (!ident) {
		return NULL;
	}

	ident->identifier_name = name;
	return ident;
}

void mCc_ast_delete_identifier(struct mCc_ast_identifier *ident)
{
	mCc_ast_delete_identifier_name(ident->identifier_name);
	free(ident);
}
