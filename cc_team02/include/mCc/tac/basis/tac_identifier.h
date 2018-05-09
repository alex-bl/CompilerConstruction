#ifndef MCC_AST_TAC_IDENTIFIER_H
#define MCC_AST_TAC_IDENTIFIER_H

#include <stdio.h>

#include "mCc/ast/basis/ast_identifier.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_identifier(struct mCc_ast_identifier *identifier,
                              void *data);

#ifdef __cplusplus
}
#endif

#endif
