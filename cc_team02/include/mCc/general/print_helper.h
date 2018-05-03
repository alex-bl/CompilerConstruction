#ifndef MCC_PRINT_HELPER_H
#define MCC_PRINT_HELPER_H

#include "mCc/ast/basis/ast_data_type.h"
#include "mCc/ast/basis/ast_identifier.h"

#ifdef __cplusplus
extern "C" {
#endif

const char *print_data_type(enum mCc_ast_data_type type);

void print_signature(struct mCc_ast_identifier *identifier, char* buffer);

#ifdef __cplusplus
}
#endif

#endif
