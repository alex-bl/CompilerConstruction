#ifndef MCC_ASSEMBLY_SPECIAL_H
#define MCC_ASSEMBLY_SPECIAL_H

#include <stdio.h>

#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_generate_empty(FILE *out, struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_copy(FILE *out, struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_procedural_call(FILE *out,
                                           struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_return_op(FILE *out,
                                     struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_indexing(FILE *out,
                                    struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_label(FILE *out, struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
