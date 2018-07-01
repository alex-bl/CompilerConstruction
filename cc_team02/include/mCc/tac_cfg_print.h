#ifndef MCC_TAC_CFG_PRINT_H
#define MCC_TAC_CFG_PRINT_H

#include "basic_tac.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_tac_cfg_element *
mCc_tac_cfg_new_element(struct mCc_tac_element *tac_element,
                        struct mCc_tac_cfg_element *next_element_left,
                        struct mCc_tac_cfg_element *next_element_right);

#ifdef __cplusplus
}
#endif

#endif
