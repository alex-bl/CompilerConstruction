#include "mCc/tac/basis/tac_program.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_program(struct mCc_ast_program *program,
                     struct mCc_tac_element *previous_tac)
{
	assert(program);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_RETURN, program->first_function_def, NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}
