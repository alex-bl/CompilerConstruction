#ifndef MCC_TAC_CFG_H
#define MCC_TAC_CFG_H

#include "basic_tac.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_tac_cfg_element {
	struct mCc_tac_element *tac_element;
	struct mCc_tac_cfg_element *next_cfg_element_left;
	struct mCc_tac_cfg_element *next_cfg_element_right;
	void *meta_info;
};

struct mCc_tac_cfg_element *
mCc_tac_cfg_new_element(struct mCc_tac_element *tac_element,
                        struct mCc_tac_cfg_element *next_element_left,
                        struct mCc_tac_cfg_element *next_element_right);

struct mCc_tac_cfg_element *mCc_tac_cfg_generate(struct mCc_tac_element *tac);

struct mCc_tac_cfg_element *
cfg_start_function(struct mCc_tac_element *tac_function_element);

void cfg_connect_elements(struct mCc_tac_cfg_element *previous_element,
                          struct mCc_tac_cfg_element *next_element_left,
                          struct mCc_tac_cfg_element *next_element_right);

#ifdef __cplusplus
}
#endif

#endif
