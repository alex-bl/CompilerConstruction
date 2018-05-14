#ifndef MCC_AST_TAC_FUNCTION_H
#define MCC_AST_TAC_FUNCTION_H

#include <stdio.h>

#include "mCc/ast/basis/ast_function.h"
#include "mCc/tac/basis/basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_function_def(struct mCc_ast_function_def *def,
                          struct mCc_tac_element *previous_tac);

void mCc_tac_function_call(struct mCc_ast_function_call *call,
                           struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
