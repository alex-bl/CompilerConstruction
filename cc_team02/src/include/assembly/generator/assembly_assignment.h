#ifndef MCC_ASSEMBLY_ASSIGNMENT_H
#define MCC_ASSEMBLY_ASSIGNMENT_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_assign_primitive_int(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem);

void mCc_assembly_pseudo_assign_int_literal(FILE *out,
                                            struct mCc_assembly_data *data,
                                            struct mCc_tac_element *tac_elem);

void mCc_assembly_assign_function_call_int(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem);

void mCc_assembly_assign_primitive_float(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem);

void mCc_assembly_pseudo_assign_float_literal(FILE *out,
                                              struct mCc_assembly_data *data,
                                              struct mCc_tac_element *tac_elem);

void mCc_assembly_assign_function_call_float(FILE *out,
                                             struct mCc_assembly_data *data,
                                             struct mCc_tac_element *tac_elem);

void mCc_assembly_assign_primitive_bool(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem);

void mCc_assembly_pseudo_assign_bool_literal(FILE *out,
                                             struct mCc_assembly_data *data,
                                             struct mCc_tac_element *tac_elem);

void mCc_assembly_assign_function_call_bool(FILE *out,
                                            struct mCc_assembly_data *data,
                                            struct mCc_tac_element *tac_elem);

void mCc_assembly_assign_primitive_string(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem);

void mCc_assembly_pseudo_assign_string_literal(
    FILE *out, struct mCc_assembly_data *data,
    struct mCc_tac_element *tac_elem);

void mCc_assembly_assign_function_call_string(FILE *out,
                                              struct mCc_assembly_data *data,
                                              struct mCc_tac_element *tac_elem);

void mCc_assembly_assign_array_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem);
void mCc_assembly_assign_array_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem);
void mCc_assembly_assign_array_bool(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem);
void mCc_assembly_assign_array_string(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem);

#ifdef __cplusplus
}
#endif

#endif
