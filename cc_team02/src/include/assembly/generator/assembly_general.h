#ifndef MCC_ASSEMBLY_GENERAL_H
#define MCC_ASSEMBLY_GENERAL_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_load_int_from_stack(FILE *out, int stack_offset,
                                      const char *dest);

void mCc_assembly_load_float_from_stack(FILE *out, int stack_offset);

void mCc_assembly_load_int_val_to_register(FILE *out, long int_val,
                                           const char *dest);

void mCc_assembly_store_float_val(FILE *out, float float_val,
                                  int float_counter);

void mCc_assembly_allocate_int_on_stack(FILE *out, size_t space);

void mCc_assembly_allocate_float_on_stack(FILE *out, size_t space);

void mCc_assembly_push_int_on_stack(FILE *out, int stack_offset,
                                    const char *dest);

void mCc_assembly_push_float_on_stack(FILE *out, int stack_offset);

#ifdef __cplusplus
}
#endif

#endif
