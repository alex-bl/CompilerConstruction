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

	fprintf(out, "digraph \"AST\" {\n");
	fprintf(out, "\tnodesep=0.6\n");

	while (cfg_element->next_cfg_element_left != NULL) {
		//print node
		fprintf(out, "\t\"%p\" [shape=box, label=\"%s\"];\n", node, label);
		//print edge
		fprintf(out, "\t\"%p\" -> \"%p\" [label=\"%s\"];\n", src_node, dst_node,
		        label);

		if (cfg_element->next_cfg_element_right != NULL) {
		}
	}

	fprintf(out, "}\n");
}
