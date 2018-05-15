#include "tac_function.h"

#include <assert.h>
#include <stdlib.h>

#include "basic_tac.h"

void mCc_tac_function_def(struct mCc_ast_function_def *def,
                          struct mCc_tac_element *previous_tac)
{
	assert(def);
	assert(previous_tac);

	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_LABLE,
	                    tac_new_identifier(def->identifier->identifier_name),
	                    tac_new_identifier((char *)def->return_type), NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_function_call(struct mCc_ast_function_call *call,
                           struct mCc_tac_element *previous_tac)
{
	assert(call);
	assert(previous_tac);

	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_PROCEDURAL_CALL,
	                    tac_new_identifier(call->identifier->identifier_name),
	                    tac_new_identifier((char *)call->first_argument), NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}
