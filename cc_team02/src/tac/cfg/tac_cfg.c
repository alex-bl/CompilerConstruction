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
	assert(next_element_left);

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
	// TODO iterate throw all function -> each function separate cfg
	while (false) {
	}
	return NULL;
}

struct mCc_tac_cfg_element *
cfg_start_function(struct mCc_tac_element *tac_function_element)
{
	// TODO build up cfg for each function here
	return NULL;
}

void cfg_connect_elements(struct mCc_tac_cfg_element *previous_element,
                          struct mCc_tac_cfg_element *next_element_left,
                          struct mCc_tac_cfg_element *next_element_right)
{
	// TODO connect previous_elment with next elements
}
