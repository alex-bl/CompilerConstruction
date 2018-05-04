#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/symtab/symtab_node.h"

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
	ident->symtab_info = NULL;
	ident->semantic_error = NULL;

	return ident;
}

void mCc_ast_delete_identifier(struct mCc_ast_identifier *ident)
{
	assert(ident);

	mCc_validator_delete_validation_result(ident->semantic_error);

	free(ident->identifier_name);
	// if there is symbol-table-information associated
	if (ident->symtab_info) {
		mCc_symtab_delete_symtab_node(ident->symtab_info);
	}

	free(ident);
}
