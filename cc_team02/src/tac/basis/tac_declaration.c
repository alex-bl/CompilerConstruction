#include "mCc/tac/basis/tac_declaration.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_declaration_primitive(struct mCc_ast_declaration *declaration,
                                   void *data)
{
	assert(declaration);
	assert(data);

	tac_new_element(
	    MCC_TAC_OPARATION_COPY,
		tac_new_identifier(
	        declaration->next_declaration->identifier->identifier_name),
	    NULL, tac_new_identifier(declaration->identifier->identifier_name));
}

void mCc_tac_declaration_array(struct mCc_ast_declaration *declaration,
                               void *data)
{
	assert(declaration);
	assert(data);

	tac_new_element(
	    MCC_TAC_OPARATION_INDEXING,
	    tac_new_identifier(
	        declaration->next_declaration->identifier->identifier_name),
	    tac_new_identifier(declaration->size),
	    tac_new_identifier(declaration->array_identifier->identifier_name));
}
