#ifndef MCC_AST_PRINT_IDENTIFIER_H
#define MCC_AST_PRINT_IDENTIFIER_H

#include <stdio.h>

#include "mCc/ast/basis/ast_identifier.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_identifier(FILE *out, struct mCc_ast_identifier *identifier);

#ifdef __cplusplus
}
#endif

#endif
