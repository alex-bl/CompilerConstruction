#ifndef MCC_AST_TAC_FUNCTION_H
#define MCC_AST_TAC_FUNCTION_H

#include <stdio.h>

#include "mCc/ast/basis/ast_function.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_function_def(struct mCc_ast_function_def *def, void *data);

void mCc_tac_function_call(struct mCc_ast_function_call *call,
                                 void *data);

#ifdef __cplusplus
}
#endif

#endif
