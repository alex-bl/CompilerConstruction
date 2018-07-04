#include "mCc/tac_cfg_print.h"

#include "basic_tac.h"
#include "mCc/tac_print.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *
helper_get_element_type_as_string(enum mCc_tac_type element_type)
{
	switch (element_type) {
	case MCC_TAC_TYPE_NO_TYPE: return "NO_TYPE";
	case MCC_TAC_TYPE_INTEGER: return "INTEGER";
	case MCC_TAC_TYPE_BOOL: return "BOOL";
	case MCC_TAC_TYPE_FLOAT: return "FLOAT";
	case MCC_TAC_TYPE_STRING: return "STRING";
	}
	return "UNKNOWN";
}

static void helper_print_tac_arg(struct mCc_tac_identifier *tac_identifier,
                                 FILE *out)
{
	if (tac_identifier) {
		switch (tac_identifier->type) {
		case MCC_IDENTIFIER_TAC_TYPE_INTEGER:
			fprintf(out, "%ld", tac_identifier->i_val);
			break;
		case MCC_IDENTIFIER_TAC_TYPE_FLOAT:
			fprintf(out, "%lf", tac_identifier->f_val);
			break;
		case MCC_IDENTIFIER_TAC_TYPE_BOOL:
			fprintf(out, "%s", (tac_identifier->b_val) ? "true" : "false");
			break;
		case MCC_IDENTIFIER_TAC_TYPE_VAR:
		case MCC_IDENTIFIER_TAC_TYPE_STRING:
		case MCC_IDENTIFIER_TAC_TYPE_FUNCTION_CALL:
		case MCC_IDENTIFIER_TAC_TYPE_FUNCTION_DEF:
			fprintf(out, "%s", tac_identifier->name);
			break;
		default: fprintf(out, "%s", "unknown?"); break;
		}
	} else {
		fprintf(out, "%s", "-");
	}
}

static void helper_print_tac_element(struct mCc_tac_cfg_element *cfg_element,
                                     FILE *out)
{
	assert(cfg_element);
	assert(out);

	fprintf(out, "\t\"%p\" [shape=box, label=\"", cfg_element);
	fprintf(out, "op: %s",
	        mCc_tac_print_op(cfg_element->tac_element->tac_operation));
	fprintf(out, " | ");
	helper_print_tac_arg(cfg_element->tac_element->tac_argument1, out);
	fprintf(out, " | ");
	helper_print_tac_arg(cfg_element->tac_element->tac_argument2, out);
	fprintf(out, " | ");
	helper_print_tac_arg(cfg_element->tac_element->tac_result, out);
	fprintf(
	    out, " | %s",
	    helper_get_element_type_as_string(cfg_element->tac_element->tac_type));
	fprintf(out, "\"];\n");
}

static void helper_print_cfg_element_connection(
    struct mCc_tac_cfg_element *cfg_element,
    struct mCc_tac_cfg_element *cfg_next_element, FILE *out)
{
	assert(cfg_element);
	assert(cfg_next_element);
	assert(out);

	// checks if special treatment is needed, because of two after else labels
	if (/*cfg_next_element->next_cfg_element_left != NULL &&*/
	    (cfg_next_element->tac_element->tac_operation ==
	         MCC_TAC_OPARATION_LABEL_AFTER_ELSE &&
	     cfg_next_element->next_cfg_element_left->tac_element->tac_operation ==
	         MCC_TAC_OPARATION_LABEL_AFTER_ELSE)) {
		fprintf(out, "\t\"%p\" -- \"%p\" [label=\"\"];\n", cfg_element,
		        cfg_next_element->next_cfg_element_left);
	} else {
		fprintf(out, "\t\"%p\" -- \"%p\" [label=\"\"];\n", cfg_element,
		        cfg_next_element);
	}

	// fprintf(out, "\t\"%p\" -- \"%p\" [label=\"\"];\n", cfg_element,
	//      cfg_next_element);
}

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
	assert(out);
	assert(cfg_element);

	if (cfg_element->tac_element->tac_operation ==
	        MCC_TAC_OPARATION_LABEL_AFTER_ELSE &&
	    cfg_element->next_cfg_element_left->tac_element->tac_operation ==
	        MCC_TAC_OPARATION_LABEL_AFTER_ELSE) {
		// do nothing! ;)

	} else if (cfg_element->tac_element->tac_operation ==
	               MCC_TAC_OPARATION_JUMP &&
	           cfg_element->tac_element->tac_next_element->tac_operation ==
	               MCC_TAC_OPARATION_LABEL_WHILE) {
		// print last edge/node of the right side
		helper_print_tac_element(cfg_element, out);

		helper_print_cfg_element_connection(
		    cfg_element, cfg_element->next_cfg_element_left, out);

		helper_print_tac_element(cfg_element, out);

	} else {
		// printing the normal node + edge(s)
		if (cfg_element->next_cfg_element_left != NULL) {
			helper_print_tac_element(cfg_element, out);

			// print left edge

			helper_print_cfg_element_connection(
			    cfg_element, cfg_element->next_cfg_element_left, out);

			// print right edge if exists
			if (cfg_element->next_cfg_element_right != NULL) {
				helper_print_cfg_element_connection(
				    cfg_element, cfg_element->next_cfg_element_right, out);

				// call recursively
				tac_cfg_print_element(out, cfg_element->next_cfg_element_right);
			}

			// call recursively
			tac_cfg_print_element(out, cfg_element->next_cfg_element_left);
		} else {
			helper_print_tac_element(cfg_element, out);
		}
	}
}
