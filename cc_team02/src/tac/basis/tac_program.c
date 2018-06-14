#include "tac_program.h"

#include <assert.h>

#include "basic_tac.h"
#include "tac_function.h"

struct mCc_tac_element *mCc_tac_program(struct mCc_ast_program *program,
                                        struct mCc_tac_element *previous_tac)
{
	assert(program);
	assert(previous_tac);

//TODO: currently not needed?
//	// writing a list of all function at the beginning of the tac table:
//	struct mCc_ast_function_def *function_def_list =
//	    program->first_function_def;
//	while (function_def_list != NULL) {
//		/* Skip all build-ins */
//		if (!function_def_list->build_in_stub) {
//			struct mCc_tac_element *tac_element = tac_new_element(
//			    MCC_TAC_OPARATION_LABEL_FUNCTION, NULL, NULL,
//			    tac_new_identifier(
//			        function_def_list->identifier->identifier_name),
//			    MCC_TAC_TYPE_NO_TYPE, 0);
//			mCc_tac_connect_tac_entry(previous_tac, tac_element);
//			previous_tac = tac_element;
//		}
//		function_def_list = function_def_list->next_function_def;
//	}
//
//	// one empty element in the tac table to separate the function list from the
//	// following
//	struct mCc_tac_element *tac_element = tac_new_element(
//	    MCC_TAC_OPARATION_EMPTY, NULL, NULL, NULL, MCC_TAC_TYPE_NO_TYPE, 0);
//	mCc_tac_connect_tac_entry(previous_tac, tac_element);
//	previous_tac = tac_element;


	// looping throw all function defs and building up the tac table
	struct mCc_ast_function_def *function_def = program->first_function_def;

	while (function_def != NULL) {
		/* Skip all build-ins */
		if (!function_def->build_in_stub) {
			struct mCc_tac_element *tac =
			    mCc_tac_function_def(function_def, previous_tac);
			// mCc_tac_connect_tac_entry(previous_tac, tac);
			previous_tac = tac;
		}
		function_def = function_def->next_function_def;
	}

	return previous_tac;
}
