#ifndef MCC_AST_PRINT_OPERATOR_H
#define MCC_AST_PRINT_OPERATOR_H

#include <stdio.h>

#include "mCc/ast/basis/ast_operator.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_operator(FILE *out, struct mCc_ast_operator *operator);

#ifdef __cplusplus
}
#endif

#endif
