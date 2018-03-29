#include "mCc/ast/visit/ast_visit_declaration.h"
#include "mCc/ast/visit/ast_visit_identifier.h"
#include <assert.h>

void mCc_ast_visit_optional_declaration(
    struct mCc_ast_declaration *declaration, struct mCc_ast_visitor *visitor)
{
	if (declaration) {
		mCc_ast_visit_declaration(declaration, visitor);
	}
}

void mCc_ast_visit_declaration(struct mCc_ast_declaration *declaration,
                               struct mCc_ast_visitor *visitor)
{
	assert(declaration);
	assert(visitor);

	visit_if_pre_order(declaration, visitor->declaration, visitor);

	switch (declaration->declaration_type) {
	case MCC_AST_DECLARATION_PRIMITIVE:
		visit_if_pre_order(declaration, visitor->declaration_primitive,
		                   visitor);

		mCc_ast_visit_identifier(declaration->identifier, visitor);
		mCc_ast_visit_optional_declaration(declaration->next_declaration,
		                                        visitor);

		visit_if_post_order(declaration, visitor->declaration_primitive,
		                    visitor);
		break;
	case MCC_AST_DECLARATION_ARRAY:
		visit_if_pre_order(declaration, visitor->declaration_array, visitor);

		mCc_ast_visit_identifier(declaration->array_identifier, visitor);

		mCc_ast_visit_optional_declaration(declaration->next_declaration,
		                                        visitor);

		visit_if_post_order(declaration, visitor->declaration_array, visitor);
		break;
	}

	visit_if_post_order(declaration, visitor->declaration, visitor);
}
