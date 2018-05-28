#include "mCc/tac_print.h"

#include "basic_tac.h"
#include <assert.h>
#include <stddef.h>

/*
 * should be the "top"
 * is "global"
 */
void mCc_tac_print_start_program(struct mCc_tac_element *tac, FILE *out)
{
	assert(tac);
	assert(out);

	fprintf(out, "Printing TAC-table:\n");

	while (tac != NULL) {
		char *argument1;
		char *argument2;
		char *result;

		if (tac->tac_argument1 != NULL) {
			argument1 = tac->tac_argument1->name;
		} else {
			argument1 = "NULL";
		}
		if (tac->tac_argument2 != NULL) {
			argument2 = tac->tac_argument2->name;
		} else {
			argument2 = "NULL";
		}
		if (tac->tac_result != NULL) {
			result = tac->tac_result->name;
		} else {
			result = "NULL";
		}
		fprintf(out,
		        "operation: %i - argument1: %s - argument2: %s - result: %s\n",
		        tac->tac_operation, argument1, argument2, result);
		tac = tac->tac_next_element;
	}
}
