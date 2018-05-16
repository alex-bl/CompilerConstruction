#ifndef MCC_AST_TAC_H
#define MCC_AST_TAC_H

#include "tac_print.h"

#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_print_start_program(struct mCc_tac_element *tac, FILE *out);

#ifdef __cplusplus
}
#endif

#endif
