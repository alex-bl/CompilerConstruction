#ifndef MCC_AST_PRINT_STATEMENT_H
#define MCC_AST_PRINT_STATEMENT_H

#include <stdio.h>

#include "mCc/ast/basis/ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_statement(FILE *out,
                                 struct mCc_ast_statement *statement);

#ifdef __cplusplus
}
#endif

#endif
