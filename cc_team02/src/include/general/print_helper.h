#ifndef MCC_PRINT_HELPER_H
#define MCC_PRINT_HELPER_H

#include "ast_data_type.h"
#include "ast_identifier.h"
#include "ast_operator.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *print_data_type(enum mCc_ast_data_type type);

void print_signature(struct mCc_ast_identifier *identifier, char *buffer);

const char *mCc_ast_print_binary_op(enum mCc_ast_binary_op op);

const char *mCc_ast_print_unary_op(enum mCc_ast_unary_op op);

#ifdef __cplusplus
}
#endif

#endif
