#include <stddef.h>

#include "mCc/ast/basis/ast_identifier.h"

struct mCc_ast_identifier *mCc_ast_new_identifier(const char *name)
{
	assert(name);

	struct mCc_ast_identifier *expr = malloc(sizeof(*expr));
	if (!expr) {
		return NULL;
	}

	expr->identifier_name = name;
	return expr;
}

void mCc_ast_delete_identifier(struct mCc_ast_identifier *name)
{
	mCc_ast_delete_identifier(name);
}
