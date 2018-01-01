#ifndef MCC_AST_PRINT_H
#define MCC_AST_PRINT_H

#include <stdio.h>

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *mC_ast_print_binary_op(enum mC_ast_binary_op op);

/* ------------------------------------------------------------- DOT Printer */

void mC_ast_print_dot_begin(FILE *out);

void mC_ast_print_dot_end(FILE *out);

void mC_ast_print_dot_expression(FILE *out,
                                 struct mC_ast_expression *expression);

#ifdef __cplusplus
}
#endif

#endif
