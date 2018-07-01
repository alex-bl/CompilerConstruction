#include "mCc/tac_cfg_print.h"

#include "basic_tac.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mCc_tac_cfg_print(FILE *out, struct mCc_tac_cfg_element *cfg_element)
{
	assert(cfg_element);
	assert(cfg_element->next_cfg_element_left);

	fprintf(out, "digraph \"TAC-CFG\" {\n");
	fprintf(out, "\tnodesep=0.6\n");

	while (cfg_element->next_cfg_element_left != NULL) {
		// TODO not just print number of tac_operation enum -> print operation
		// name
		// print node
		fprintf(out, "\t\"%p\" [shape=box, label=\"%d\"];\n", cfg_element,
		        cfg_element->tac_element->tac_operation);
		// print left edge
		fprintf(out, "\t\"%p\" -> \"%p\" [label=\"left_side\"];\n", cfg_element,
		        cfg_element->next_cfg_element_left);

		// print right edge if exists
		if (cfg_element->next_cfg_element_right != NULL) {
			fprintf(out, "\t\"%p\" -> \"%p\" [label=\"right_side\"];\n",
			        cfg_element, cfg_element->next_cfg_element_right);
		}
		cfg_element = cfg_element->next_cfg_element_left;
	}

	fprintf(out, "\t\"%p\" [shape=box, label=\"%d\"];\n", cfg_element,
	        cfg_element->tac_element->tac_operation);

	fprintf(out, "}\n");
}
