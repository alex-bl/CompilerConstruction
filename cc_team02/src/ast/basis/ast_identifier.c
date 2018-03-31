#include "mCc/ast/basis/ast_identifier.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct mCc_ast_identifier *mCc_ast_new_identifier(char *name)
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
	assert(ident);
	free(ident->identifier_name);
	free(ident);
}
