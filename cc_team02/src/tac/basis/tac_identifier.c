#include "mCc/tac/basis/tac_identifier.h"

#include <assert.h>
#include <stdlib.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_identifier(struct mCc_ast_identifier *identifier,
                        struct mCc_tac_element *previous_tac)
{
	assert(identifier);
	assert(previous_tac);

	tac_new_element(MCC_TAC_OPERATION_EMPTY,
	                tac_new_identifier(identifier->identifier_name), NULL,
	                NULL);
}
