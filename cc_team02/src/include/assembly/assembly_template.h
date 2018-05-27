#ifndef MCC_ASSEMBLY_TEMPLATE_H
#define MCC_ASSEMBLY_TEMPLATE_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void assembly_new_header(FILE *out, const char *file_name,
                         const char *next_function_label);

void assembly_new_function_def_enter(FILE *out, const char *function_label);

void assembly_new_function_def_leave(FILE *out, const char *function_label,
                                     const char *next_function_label);

void assembly_main_function_enter(FILE *out);

void assembly_main_function_leave(FILE *out);

void assembly_new_string(FILE *out, int string_index, const char *str_value,
                         const char *next_function_label);

void assembly_add_integers(FILE *out, const char *operant_1,
                           const char *operant_2);

void assembly_sub_integers(FILE *out, const char *operant_1,
                           const char *operant_2);

void assembly_mul_integers(FILE *out, const char *operant_1,
                           const char *operant_2);
// TODO: check this
void assembly_div_integers(FILE *out, const char *operant_1,
                           const char *operant_2);
#ifdef __cplusplus
}
#endif

#endif
