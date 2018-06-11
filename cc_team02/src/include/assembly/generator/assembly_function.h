#ifndef MCC_ASSEMBLY_FUNCTION_H
#define MCC_ASSEMBLY_FUNCTION_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_start_function_def(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem);

void mCc_assembly_end_function_def(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem);

void mCc_assembly_function_call(FILE *out, struct mCc_assembly_data *data,
                                struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
