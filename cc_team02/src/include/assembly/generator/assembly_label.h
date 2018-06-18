#ifndef MCC_ASSEMBLY_LABEL_H
#define MCC_ASSEMBLY_LABEL_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_label_function(FILE *out, struct mCc_assembly_data *data,
                                 struct mCc_tac_element *tac_elem);

void mCc_assembly_label_float(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem);

void mCc_assembly_label_string(FILE *out, struct mCc_assembly_data *data,
                               struct mCc_tac_element *tac_elem);

void mCc_assembly_label_if(FILE *out, struct mCc_assembly_data *data,
                           struct mCc_tac_element *tac_elem);

void mCc_assembly_label_else(FILE *out, struct mCc_assembly_data *data,
                             struct mCc_tac_element *tac_elem);

void mCc_assembly_label_after_else(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem);

void mCc_assembly_label_while(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
