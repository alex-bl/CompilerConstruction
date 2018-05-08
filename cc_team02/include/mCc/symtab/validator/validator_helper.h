#ifndef MCC_VALIDATOR_HELPER_TYPE_H
#define MCC_VALIDATOR_HELPER_TYPE_H

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_ast_statement *
mCc_validator_find_return_statement(struct mCc_ast_function_def *function_def);

#ifdef __cplusplus
}
#endif

#endif
