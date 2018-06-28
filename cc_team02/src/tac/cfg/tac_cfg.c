#include "mCc/tac_cfg.h"

#include "basic_tac.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mCc_tac_cfg_element *
mCc_tac_cfg_new_element(struct mCc_tac_element *tac_element,
                        struct mCc_tac_cfg_element *next_element_left,
                        struct mCc_tac_cfg_element *next_element_right)
{
	assert(tac_element);
	// assert(next_element_left);

	struct mCc_tac_cfg_element *tac_cfg_element =
	    malloc(sizeof(*tac_cfg_element));
	if (!tac_cfg_element) {
		return NULL;
	}

	tac_cfg_element->tac_element = tac_element;
	tac_cfg_element->next_cfg_element_left = next_element_left;
	tac_cfg_element->next_cfg_element_right = next_element_right;
	return tac_cfg_element;
}

struct mCc_tac_cfg_element *mCc_tac_cfg_generate(struct mCc_tac_element *tac)
{
	struct mCc_tac_element *tac_next_element = tac;
	// TODO iterate throw all function -> each function separate cfg
	struct mCc_tac_cfg_element *cfg_function;
	while (tac_next_element != NULL) {
		if (tac_next_element->tac_operation ==
		    MCC_TAC_OPARATION_START_FUNCTION_DEF) {
			cfg_function = cfg_start_function(tac_next_element);
		}
		tac_next_element = tac_next_element->tac_next_element;
	}
	// TODO just returns the cfg of the last function
	return cfg_function;
}

/*
 * improvment:
 * left side always continues with next tac elements
 * if label where the jump points to comes up -> continue with the right side
 * storing the element where the left side ends and connect it with the end of
 * the right side
 *
 */

struct mCc_tac_cfg_element *
cfg_start_function(struct mCc_tac_element *tac_function_element)
{
	struct mCc_tac_element *tac_next_element = tac_function_element;
	struct mCc_tac_cfg_element *cfg_element;
	struct mCc_tac_cfg_element *prev_cfg_element;
	// TODO build up cfg for each function here
	while (tac_next_element->tac_operation !=
	       MCC_TAC_OPARATION_END_FUNCTION_DEF) {
		prev_cfg_element = cfg_element;
		cfg_element = mCc_tac_cfg_new_element(tac_next_element, NULL, NULL);

		if (prev_cfg_element != NULL) {
			if ((prev_cfg_element->tac_element->tac_operation ==
			     MCC_TAC_OPARATION_JUMP_NOT_EQUALS) ||
			    prev_cfg_element->tac_element->tac_operation ==
			        MCC_TAC_OPARATION_JUMP ||
			    prev_cfg_element->tac_element->tac_operation ==
			        MCC_TAC_OPARATION_JUMP_EQUALS) {
				// TODO where to jump? -> what is the right side?
				prev_cfg_element->next_cfg_element_right = cfg_element;
			}
			prev_cfg_element->next_cfg_element_left = cfg_element;
		}
		tac_next_element = tac_next_element->tac_next_element;
	}
	return NULL;
}

/*
 * TODO
 * TODO
 * TODO
 * find evaluation of first argument of jump operation of tac element
 * -> check if it is true or not -> checks if to jump or not
 */

// no comparison needed -> this tac element just have one argument
bool cfg_evaluate_jump_element(struct mCc_tac_element *jump_element)
{
	switch (jump_element->tac_argument1->type) {
	case MCC_IDENTIFIER_TAC_TYPE_INTEGER:
		return jump_element->tac_argument1->s_val ==
		       jump_element->tac_argument2->s_val;
		break;
	case MCC_IDENTIFIER_TAC_TYPE_FLOAT:
		return jump_element->tac_argument1->s_val ==
		       jump_element->tac_argument2->s_val;
		break;
	case MCC_IDENTIFIER_TAC_TYPE_BOOL:
		return jump_element->tac_argument1->s_val ==
		       jump_element->tac_argument2->s_val;
		break;
	case MCC_IDENTIFIER_TAC_TYPE_STRING:
		return strcmp(jump_element->tac_argument1->s_val,
		              jump_element->tac_argument2->s_val);
		break;
	default: return false;
	}
	return false;
}

// function not needed?
void cfg_connect_elements(struct mCc_tac_cfg_element *previous_element,
                          struct mCc_tac_cfg_element *next_element_left,
                          struct mCc_tac_cfg_element *next_element_right)
{
	previous_element->next_cfg_element_left = next_element_left;
	previous_element->next_cfg_element_right = next_element_right;
}
