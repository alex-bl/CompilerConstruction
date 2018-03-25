#include <stddef.h>

#include "mCc/ast/basis/ast_declaration.h"

struct mCc_ast_declaration *
mCc_ast_new_primitive_declaration(enum mCc_ast_literal_type data_type,
                                  struct mCc_ast_identifier *identifier)
{
	struct mCc_ast_declation *declaration = malloc(sizeof(*declaration));
	if (!declaration) {
		return NULL;
	}

	declaration->declaration_type = MCC_AST_DECLARATION_PRIMITIVE;
	declaration->data_type = data_type;
	declaration->identifier = identifier;
	return declaration;
}

struct mCc_ast_declaration *
mCc_ast_new_array_declaration(enum mCc_ast_literal_type data_type,
                              struct mCc_ast_identifier *identifier,
                              size_t size)
{
	struct mCc_ast_declation *declaration = malloc(sizeof(*declaration));
	if (!declaration) {
		return NULL;
	}

	declaration->declaration_type = MCC_AST_DECLARATION_ARRAY;
	declaration->data_type = data_type;
	declaration->array_identifier = identifier;
	declaration->size = size;
	return declaration;
}

void mCc_ast_delete_declaration(struct mCc_ast_declaration *declaration)
{

	if (declaration->data_type==MCC_AST_DECLARATION_PRIMITIVE) {
		mCc_ast_delete_identifier(declaration->identifier);
	} else if (declaration->data_type==MCC_AST_DECLARATION_PRIMITIVE) {
		mCc_ast_delete_array_identifier(declaration->array_identifier);
		mCc_ast_delete_size(declaration->size);
	}
	mCc_ast_delete_declaration_type(declaration->data_type);
	free(declaration);
}
