#ifndef MCC_ASSEMBLY_DECLARATION_H
#define MCC_ASSEMBLY_DECLARATION_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_declare_primitive_int(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem);

void mCc_assembly_declare_primitive_float(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem);

void mCc_assembly_declare_primitive_bool(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem);

void mCc_assembly_declare_primitive_string(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem);

void mCc_assembly_declare_array_int(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem);

void mCc_assembly_declare_array_float(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem);

void mCc_assembly_declare_array_bool(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem);

void mCc_assembly_declare_array_string(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
