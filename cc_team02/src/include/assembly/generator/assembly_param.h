#ifndef MCC_ASSEMBLY_PARAM_H
#define MCC_ASSEMBLY_PARAM_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_param_int_primitive(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem);

void mCc_assembly_param_float_primitive(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem);

void mCc_assembly_param_bool_primitive(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem);

void mCc_assembly_param_string_primitive(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem);

void mCc_assembly_param_int_array(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem);

void mCc_assembly_param_float_array(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem);

void mCc_assembly_param_bool_array(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem);

void mCc_assembly_param_string_array(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
