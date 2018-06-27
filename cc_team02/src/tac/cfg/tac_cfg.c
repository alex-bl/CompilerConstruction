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
			if (prev_cfg_element->tac_element->tac_operation ==
			        MCC_TAC_OPARATION_JUMP_NOT_EQUALS ||
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

// function not needed?
void cfg_connect_elements(struct mCc_tac_cfg_element *previous_element,
                          struct mCc_tac_cfg_element *next_element_left,
                          struct mCc_tac_cfg_element *next_element_right)
{
	previous_element->next_cfg_element_left = next_element_left;
	previous_element->next_cfg_element_right = next_element_right;
}
