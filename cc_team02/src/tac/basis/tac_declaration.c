#include "mCc/tac/basis/tac_declaration.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_declaration_primitive(struct mCc_ast_declaration *declaration,
                                   struct mCc_tac_element *previous_tac)
{
	assert(declaration);
	assert(previous_tac);

	// not correct?
	tac_new_element(
	    MCC_TAC_OPARATION_COPY,
	    tac_new_identifier(declaration->identifier->identifier_name), NULL,
	    NULL);
}

void mCc_tac_declaration_array(struct mCc_ast_declaration *declaration,
                               struct mCc_tac_element *previous_tac)
{
	assert(declaration);
	assert(previous_tac);

	// not correct?
	tac_new_element(
	    MCC_TAC_OPARATION_INDEXING, tac_new_identifier(declaration->size),
	    tac_new_identifier(declaration->array_identifier->identifier_name),
	    NULL);
}
