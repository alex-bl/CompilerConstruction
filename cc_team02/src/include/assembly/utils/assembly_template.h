#ifndef MCC_ASSEMBLY_TEMPLATE_H
#define MCC_ASSEMBLY_TEMPLATE_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void assembly_new_header(FILE *out, const char *file_name,
                         const char *next_function_label);

void assembly_new_function_def_enter(FILE *out, const char *function_label);

// TODO: what is correct?
void assembly_new_function_def_leave(FILE *out, const char *function_label,
                                     const char *next_function_label);

void assembly_main_function_enter(FILE *out);

void assembly_main_function_leave(FILE *out);

void assembly_new_string_enter(FILE *out, const char *label,
                               const char *str_value);

void assembly_new_string_leave_with_function(FILE *out,
                                             const char *next_function_label);

void assembly_new_float(FILE *out, float float_val, const char *label);

#ifdef __cplusplus
}
#endif

#endif
