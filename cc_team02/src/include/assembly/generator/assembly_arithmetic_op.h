#ifndef MCC_ASSEMBLY_ARITHMETIC_OP_H
#define MCC_ASSEMBLY_ARITHMETIC_OP_H

#include <stdio.h>

#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_generate_add(FILE *out, struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_sub(FILE *out, struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_mul(FILE *out, struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_div(FILE *out, struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
