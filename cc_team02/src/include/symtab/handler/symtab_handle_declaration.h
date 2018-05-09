#ifndef MCC_SYMTAB_HANDLE_DECLARATION_H
#define MCC_SYMTAB_HANDLE_DECLARATION_H

#include "ast_declaration.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_handle_declaration_primitive_pre_order(
    struct mCc_ast_declaration *declaration, void *data);

void mCc_symtab_handle_declaration_array_pre_order(
    struct mCc_ast_declaration *declaration, void *data);

#ifdef __cplusplus
}
#endif

#endif
