#ifndef MCC_AST_PRINT_FUNCTION_H
#define MCC_AST_PRINT_FUNCTION_H

#include <stdio.h>

#include "mCc/ast/basis/ast_function.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_function_def(FILE *out,
                                    struct mCc_ast_function_def *function_def);

void mCc_ast_print_dot_function_call(
    FILE *out, struct mCc_ast_function_call *function_call);

#ifdef __cplusplus
}
#endif

#endif
