#include "tac_identifier.h"

#include <assert.h>
#include <stdlib.h>

#include "basic_tac.h"

//TODO recursive structure
struct mCc_tac_element *mCc_tac_identifier(struct mCc_ast_identifier *identifier,
                        struct mCc_tac_element *previous_tac)
{
	assert(identifier);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(identifier->identifier_name), NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
