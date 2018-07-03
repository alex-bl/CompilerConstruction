#include "mCc/tac_cfg_print.h"

#include "basic_tac.h"
#include "mCc/tac_print.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mCc_tac_cfg_print(FILE *out, struct mCc_tac_cfg_element *cfg_element)
{
	assert(cfg_element);
	assert(cfg_element->next_cfg_element_left);

	fprintf(out, "graph \"TAC-CFG\" {\n");
	fprintf(out, "\tnodesep=0.6\n");

	tac_cfg_print_element(out, cfg_element);

	fprintf(out, "}\n");
}

void tac_cfg_print_element(FILE *out, struct mCc_tac_cfg_element *cfg_element)
{
	if (cfg_element->tac_element->tac_operation ==
	    MCC_TAC_OPARATION_LABEL_AFTER_ELSE) {
		// print last edge/node of the right side
		fprintf(out, "\t\"%p\" [shape=box, label=\"%s\"];\n", cfg_element,
		        mCc_tac_print_op(cfg_element->tac_element->tac_operation));
		fprintf(out, "\t\"%p\" -> \"%p\" [label=\"left_side\"];\n", cfg_element,
		        cfg_element->next_cfg_element_left);
	} else if (cfg_element->tac_element->tac_operation ==
	               MCC_TAC_OPARATION_JUMP &&
	           cfg_element->tac_element->tac_next_element->tac_operation ==
	               MCC_TAC_OPARATION_LABEL_WHILE) {
		// print last edge/node of the right side
		fprintf(out, "\t\"%p\" [shape=box, label=\"%s\"];\n", cfg_element,
		        mCc_tac_print_op(cfg_element->tac_element->tac_operation));
		fprintf(out, "\t\"%p\" -> \"%p\" [label=\"left_side\"];\n", cfg_element,
		        cfg_element->next_cfg_element_left);
		fprintf(out, "\t\"%p\" [shape=box, label=\"%s\"];\n",
		        cfg_element->next_cfg_element_left,
		        mCc_tac_print_op(cfg_element->next_cfg_element_left->tac_element
		                             ->tac_operation));
		// fprintf(out, "\t\"%p\" -> \"%p\" [label=\"left_side\"];\n",
		// cfg_element->next_cfg_element_left,
		// cfg_element->next_cfg_element_left->next_cfg_element_left);
	} else {
		// printing the normal node + edge(s)
		if (cfg_element->next_cfg_element_left != NULL) {
			// TODO not just print number of tac_operation enum -> print
			// operation name print node
			fprintf(out, "\t\"%p\" [shape=box, label=\"%s\"];\n", cfg_element,
			        mCc_tac_print_op(cfg_element->tac_element->tac_operation));
			// print left edge
			fprintf(out, "\t\"%p\" -> \"%p\" [label=\"left_side\"];\n",
			        cfg_element, cfg_element->next_cfg_element_left);

			// print right edge if exists
			if (cfg_element->next_cfg_element_right != NULL) {
				fprintf(out, "\t\"%p\" -> \"%p\" [label=\"right_side\"];\n",
				        cfg_element, cfg_element->next_cfg_element_right);
				tac_cfg_print_element(out, cfg_element->next_cfg_element_right);
			}
			// cfg_element = cfg_element->next_cfg_element_left;

			tac_cfg_print_element(out, cfg_element->next_cfg_element_left);
		} else {
			// print last element without further connections:
			fprintf(out, "\t\"%p\" [shape=box, label=\"%d\"];\n", cfg_element,
			        cfg_element->tac_element->tac_operation);
		}
	}
}
