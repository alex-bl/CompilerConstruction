#ifndef MCC_ASSEMBLY_FORMATTER_H
#define MCC_ASSEMBLY_FORMATTER_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void mCc_assembly_print_shift(FILE *out);

void mCc_assembly_print_nl(FILE *out);

void mCc_assembly_print_op(FILE *out, const char *op);

#ifdef __cplusplus
}
#endif

#endif
