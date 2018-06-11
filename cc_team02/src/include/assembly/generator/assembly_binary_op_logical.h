#ifndef MCC_ASSEMBLY_BINARY_OP_LOGICAL_H
#define MCC_ASSEMBLY_BINARY_OP_LOGICAL_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_equals_int(FILE *out, struct mCc_assembly_data *data,
                             struct mCc_tac_element *tac_elem);

void mCc_assembly_equals_float(FILE *out, struct mCc_assembly_data *data,
                               struct mCc_tac_element *tac_elem);

void mCc_assembly_equals_bool(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem);
/*==================================== not equals*/

void mCc_assembly_not_equals_int(FILE *out, struct mCc_assembly_data *data,
                                 struct mCc_tac_element *tac_elem);

void mCc_assembly_not_equals_float(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem);

void mCc_assembly_not_equals_bool(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem);

/*==================================== greater*/

void mCc_assembly_greater_int(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem);

void mCc_assembly_greater_float(FILE *out, struct mCc_assembly_data *data,
                                struct mCc_tac_element *tac_elem);

/*==================================== less*/

void mCc_assembly_less_int(FILE *out, struct mCc_assembly_data *data,
                           struct mCc_tac_element *tac_elem);

void mCc_assembly_less_float(FILE *out, struct mCc_assembly_data *data,
                             struct mCc_tac_element *tac_elem);

/*==================================== greater equals*/
void mCc_assembly_greater_equals_int(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem);

void mCc_assembly_greater_equals_float(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem);

/*==================================== less equals*/
void mCc_assembly_less_equals_int(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem);

void mCc_assembly_less_equals_float(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem);
/*==================================== and/or */
void mCc_assembly_and(FILE *out, struct mCc_assembly_data *data,
                      struct mCc_tac_element *tac_elem);

void mCc_assembly_or(FILE *out, struct mCc_assembly_data *data,
                     struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
