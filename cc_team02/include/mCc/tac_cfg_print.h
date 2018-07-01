#ifndef MCC_TAC_CFG_PRINT_H
#define MCC_TAC_CFG_PRINT_H

#include "basic_tac.h"
#include "tac_cfg.h"
#include <stdbool.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_cfg_print(FILE *out, struct mCc_tac_cfg_element *cfg_element);

#ifdef __cplusplus
}
#endif

#endif
