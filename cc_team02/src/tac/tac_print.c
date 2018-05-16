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

	fprintf(out, "Printing TAC-TABEL:\n");

	while (tac != NULL) {
		fprintf(out,
		        "operation: %i - argument1: %p - argument2: %p - result: %p\n",
		        tac->tac_operation, tac->tac_argument1->name,
		        tac->tac_argument2->name, tac->tac_result->name);
		tac = tac->tac_next_element;
	}
}
