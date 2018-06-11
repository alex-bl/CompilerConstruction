#ifndef MCC_ASSEMBLY_UNARY_OP_H
#define MCC_ASSEMBLY_UNARY_OP_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_generate_unary_minus_int(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_unary_minus_float(FILE *out,
                                             struct mCc_assembly_data *data,
                                             struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_unary_negation(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
