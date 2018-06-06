#ifndef MCC_ASSEMBLY_UTILS_H
#define MCC_ASSEMBLY_UTILS_H

#include <stdio.h>
#include <stddef.h>
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t mCc_assembly_calc_int_space(int nr_of);

size_t mCc_assembly_calc_bool_space(int nr_of);

size_t mCc_assembly_calc_float_space(int nr_of);

size_t mCc_assembly_calc_string_space(const char *string);

size_t mCc_assembly_calc_param_space(struct mCc_tac_element *function_def);

int mCc_assembly_calc_stack_position(struct mCc_tac_identifier *identifier,
                                     int current_stack_ptr_pos);

const char *
mCc_assembly_get_next_function_label(struct mCc_tac_identifier *identifier);

#ifdef __cplusplus
}
#endif

#endif
