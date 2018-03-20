#ifndef MCC_AST_PRINT_EXPRESSION_H
#define MCC_AST_PRINT_EXPRESSION_H

#include <stdio.h>

#include "mCc/ast/basis/ast_expression.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_expression(FILE *out,
                                  struct mCc_ast_expression *expression);

#ifdef __cplusplus
}
#endif

#endif
