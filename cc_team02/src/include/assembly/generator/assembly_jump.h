#ifndef MCC_ASSEMBLY_JUMP_H
#define MCC_ASSEMBLY_JUMP_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

// TODO: remove?

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_generate_jump_equals(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_not_equals(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_greater(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_less(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_greater_equals(
    FILE *out, struct mCc_assembly_data *data,
    struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_less_equals(FILE *out,
                                            struct mCc_assembly_data *data,
                                            struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_and(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_or(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
