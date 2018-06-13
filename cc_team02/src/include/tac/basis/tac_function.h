#ifndef MCC_AST_TAC_FUNCTION_H
#define MCC_AST_TAC_FUNCTION_H

#include <stdio.h>

#include "ast_function.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_tac_operation tac_helper_get_tac_oparation_for_parameter_type(
    enum mCc_tac_operation operation);

struct mCc_tac_element *
mCc_tac_function_def(struct mCc_ast_function_def *def,
                     struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_function_call(struct mCc_ast_function_call *call,
                      struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
