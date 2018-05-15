#include "tac_declaration.h"

#include <assert.h>

#include "basic_tac.h"

// x:= y
struct mCc_tac_element *
mCc_tac_declaration_primitive(struct mCc_ast_declaration *declaration,
                              struct mCc_tac_element *previous_tac)
{
	assert(declaration);
	assert(previous_tac);

	// not correct?
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_COPY, NULL, NULL,
	    tac_new_identifier(declaration->identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

// y[i]:=x
struct mCc_tac_element *
mCc_tac_declaration_array(struct mCc_ast_declaration *declaration,
                          struct mCc_tac_element *previous_tac)
{
	assert(declaration);
	assert(previous_tac);

	// not correct?
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_INDEXING, tac_new_identifier(declaration->size), NULL,
	    tac_new_identifier(declaration->array_identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
