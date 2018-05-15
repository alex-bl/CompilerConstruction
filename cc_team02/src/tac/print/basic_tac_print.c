#include "basic_tac.h"

#include <assert.h>
#include <stdio.h>

//#include "mCc/ast/basis/ast_data_type.h"

void tac_print(struct mCc_tac_element *element, void *data)
{

	FILE *out = data;
	fprintf(out, "operation: %i - argument1: %p - argument2: %p - result: %p\n",
	        element->tac_operation, element->tac_argument1->name,
	        element->tac_argument2->name, element->tac_result->name);
}
