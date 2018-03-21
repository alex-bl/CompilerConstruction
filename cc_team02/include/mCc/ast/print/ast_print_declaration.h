#ifndef MCC_AST_PRINT_DECLARATION_H
#define MCC_AST_PRINT_DECLARATION_H

#include <stdio.h>

#include "mCc/ast/basis/ast_declaration.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_declaration(FILE *out,
                                  struct mCc_ast_declaration *declaration);

#ifdef __cplusplus
}
#endif

#endif
