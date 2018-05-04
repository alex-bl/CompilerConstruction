#ifndef MCC_SYMTAB_HANDLE_IDENTIFIER_H
#define MCC_SYMTAB_HANDLE_IDENTIFIER_H

#include "mCc/ast/basis/ast_identifier.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_handle_identifier(
    struct mCc_ast_identifier *identifier, void *data);

#ifdef __cplusplus
}
#endif

#endif
