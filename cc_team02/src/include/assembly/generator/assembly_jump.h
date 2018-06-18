#ifndef MCC_ASSEMBLY_JUMP_H
#define MCC_ASSEMBLY_JUMP_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

// TODO: remove?

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_generate_jump(FILE *out, struct mCc_assembly_data *data,
                                struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_equals(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem);

void mCc_assembly_generate_jump_not_equals(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
