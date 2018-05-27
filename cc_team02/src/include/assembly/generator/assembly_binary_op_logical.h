#ifndef MCC_ASSEMBLY_BINARY_OP_LOGICAL_H
#define MCC_ASSEMBLY_BINARY_OP_LOGICAL_H

#include <stdio.h>

#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_generate_less_than(FILE *out,
                                     struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_greater_than(FILE *out,
                                        struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_less_or_equals_than(
    FILE *out, struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_greater_or_equals_than(
    FILE *out, struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_and(FILE *out,
                                    struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_or(FILE *out, struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_equals(FILE *out,
                                       struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_not_equals(FILE *out,
                                           struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
