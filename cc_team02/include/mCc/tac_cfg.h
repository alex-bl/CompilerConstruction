#ifndef MCC_TAC_CFG_H
#define MCC_TAC_CFG_H

#include "basic_tac.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_tac_cfg_type {
	MCC_TAC_CFG_EMPTY,
	MCC_TAC_CFG_IF_START,
	MCC_TAC_CFG_ELSE_END,
};

struct mCc_tac_cfg_element {
	struct mCc_tac_element *tac_element;
	struct mCc_tac_cfg_element *next_cfg_element_left;
	struct mCc_tac_cfg_element *next_cfg_element_right;
	enum mCc_tac_cfg_type type_info;
	void *meta_info;
};

struct mCc_tac_cfg_element *
mCc_tac_cfg_new_element(struct mCc_tac_element *tac_element,
                        struct mCc_tac_cfg_element *next_element_left,
                        struct mCc_tac_cfg_element *next_element_right);

struct mCc_tac_cfg_element *mCc_tac_cfg_generate(struct mCc_tac_element *tac);

struct mCc_tac_cfg_element *
cfg_start_function(struct mCc_tac_element *tac_function_element);

struct mCc_tac_element *
cfg_if_statement(struct mCc_tac_cfg_element *prev_cfg_element,
                 struct mCc_tac_element *tac_if_statement);

struct mCc_tac_element *
cfg_while_statement(struct mCc_tac_cfg_element *prev_cfg_element,
                    struct mCc_tac_element *tac_while_statement);

struct mCc_tac_cfg_element *
cfg_connect_elements_to_left(struct mCc_tac_cfg_element *prev_cfg_element,
                             struct mCc_tac_element *tac_statement);

struct mCc_tac_element *
cfg_connect_elements(struct mCc_tac_cfg_element *prev_cfg_element,
                     struct mCc_tac_element *tac_next_element);

void mCc_tac_cfg_element_delete(struct mCc_tac_cfg_element *cfg_element);

void mCc_tac_cfg_delete(struct mCc_tac_cfg_element *cfg_element);

#ifdef __cplusplus
}
#endif

#endif
