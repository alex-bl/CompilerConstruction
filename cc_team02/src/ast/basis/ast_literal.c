#include <stddef.h>
#include <stdlib.h>

#include "mCc/ast/basis/ast_literal.h"

struct mCc_ast_literal *mCc_ast_new_literal_int(long value)
{
	struct mCc_ast_literal *lit = malloc(sizeof(*lit));
	if (!lit) {
		return NULL;
	}

	lit->type = MCC_AST_LITERAL_TYPE_INT;
	lit->i_value = value;
	return lit;
}

struct mCc_ast_literal *mCc_ast_new_literal_float(double value)
{
	struct mCc_ast_literal *lit = malloc(sizeof(*lit));
	if (!lit) {
		return NULL;
	}

	lit->type = MCC_AST_LITERAL_TYPE_FLOAT;
	lit->f_value = value;
	return lit;
}

/* added */
struct mCc_ast_literal *mCc_ast_new_literal_bool(bool value)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_literal *mCc_ast_new_literal_string(const char *value)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_literal(struct mCc_ast_literal *literal)
{
	assert(literal);
	free(literal);
}
