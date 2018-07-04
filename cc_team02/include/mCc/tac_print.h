#ifndef MCC_TAC_PRINT_H
#define MCC_TAC_PRINT_H

#include "tac_print.h"

#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_print_start_program(struct mCc_tac_element *tac, FILE *out);

const char *mCc_tac_print_op(enum mCc_tac_operation tac_operation);

#ifdef __cplusplus
}
#endif

#endif
