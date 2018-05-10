#include "mCc/tac/basis/tac_program.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_program(struct mCc_ast_program *program, void *data)
{
	assert(program);
	assert(data);

	tac_new_element(MCC_TAC_OPARATION_RETURN, program->first_function_def, NULL,
	                NULL);
}
