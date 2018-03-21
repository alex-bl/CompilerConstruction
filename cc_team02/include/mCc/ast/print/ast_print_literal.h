#ifndef MCC_AST_PRINT_LITERAL_H
#define MCC_AST_PRINT_LITERAL_H

#include <stdio.h>

#include "mCc/ast/basis/ast_literal.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_literal(FILE *out, struct mCc_ast_literal *literal);

#ifdef __cplusplus
}
#endif

#endif
