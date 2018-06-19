#ifndef MCC_ASSEMBLY_ARRAY_H
#define MCC_ASSEMBLY_ARRAY_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_index_acc_arr_int(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem);

void mCc_assembly_index_acc_arr_float(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem);

void mCc_assembly_index_acc_arr_bool(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem);

void mCc_assembly_index_acc_arr_string(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
