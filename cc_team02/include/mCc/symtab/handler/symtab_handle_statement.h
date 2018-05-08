#ifndef MCC_SYMTAB_HANDLE_STATEMENT_H
#define MCC_SYMTAB_HANDLE_STATEMENT_H

#include "mCc/ast/basis/ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_handle_if_statement_post_order(
    struct mCc_ast_statement *statement, void *data);

void mCc_symtab_handle_while_statement_post_order(
    struct mCc_ast_statement *statement, void *data);

#ifdef __cplusplus
}
#endif

#endif
