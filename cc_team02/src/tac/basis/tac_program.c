#include "tac_program.h"

#include <assert.h>

#include "basic_tac.h"
#include "tac_function.h"

struct mCc_tac_element *mCc_tac_program(struct mCc_ast_program *program,
                                        struct mCc_tac_element *previous_tac)
{
	assert(program);
	assert(previous_tac);

	struct mCc_ast_function_def *function_def = program->first_function_def;
	/* Skip all build-ins */
	while (function_def != NULL && function_def->build_in_stub) {
		function_def = function_def->next_function_def;
	}

	while (function_def != NULL) {
		struct mCc_tac_element *tac =
		    mCc_tac_function_def(function_def, previous_tac);
		mCc_tac_connect_tac_entry(previous_tac, tac);
		previous_tac = tac;
		function_def = function_def->next_function_def;
	}

	// no tac element necessary for program
	// struct mCc_tac_element *tac = tac_new_element(
	//    MCC_TAC_OPARATION_RETURN,
	//    tac_new_identifier(program->first_function_def), NULL, NULL);
	// mCc_tac_connect_tac_entry(previous_tac, tac);
	return previous_tac;
}
