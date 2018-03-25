#ifndef MCC_AST_PRINT_IDENTIFIER_H
#define MCC_AST_PRINT_IDENTIFIER_H

#include <stdio.h>

#include "mCc/ast/basis/ast_identifier.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_print_dot_identifier(struct mCc_ast_identifier *identifier,
                              void *data);

#ifdef __cplusplus
}
#endif

#endif
