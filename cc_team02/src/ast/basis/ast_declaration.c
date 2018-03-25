#include "mCc/ast/basis/ast_declaration.h"
#include <stddef.h>
#include <stdlib.h>

struct mCc_ast_declaration *
mCc_ast_new_primitive_declaration(enum mCc_ast_literal_type data_type,
                                  struct mCc_ast_identifier *identifier)
{
	struct mCc_ast_declaration *declaration = malloc(sizeof(*declaration));
	if (!declaration) {
		return NULL;
	}

	declaration->declaration_type = MCC_AST_DECLARATION_PRIMITIVE;
	declaration->data_type = data_type;
	declaration->identifier = identifier;
	//set explicitly to null
	declaration->next_declaration = NULL;
	return declaration;
}

struct mCc_ast_declaration *
mCc_ast_new_array_declaration(enum mCc_ast_literal_type data_type,
                              struct mCc_ast_identifier *identifier,
                              size_t size)
{
	struct mCc_ast_declaration *declaration = malloc(sizeof(*declaration));
	if (!declaration) {
		return NULL;
	}

	declaration->declaration_type = MCC_AST_DECLARATION_ARRAY;
	declaration->data_type = data_type;
	declaration->array_identifier = identifier;
	declaration->size = size;
	//set explicitly to null
	declaration->next_declaration = NULL;
	return declaration;
}

void mCc_ast_delete_declaration(struct mCc_ast_declaration *declaration)
{

	if (declaration->declaration_type == MCC_AST_DECLARATION_PRIMITIVE) {
		mCc_ast_delete_identifier(declaration->identifier);
	} else if (declaration->declaration_type == MCC_AST_DECLARATION_PRIMITIVE) {
		mCc_ast_delete_identifier(declaration->array_identifier);
	}
	free(declaration);
}
