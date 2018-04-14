#ifndef MCC_SYMTAB_HANDLE_STATEMENT_H
#define MCC_SYMTAB_HANDLE_STATEMENT_H

#include "mCc/ast/basis/ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_statement_if_enter_scope(struct mCc_ast_statement *statement,
                                         void *data);

void mCc_symtab_statement_if_leave_scope(struct mCc_ast_statement *statement,
                                         void *data);

void mCc_symtab_statement_while_enter_scope(struct mCc_ast_statement *statement,
                                            void *data);

void mCc_symtab_statement_while_leave_scope(struct mCc_ast_statement *statement,
                                            void *data);

#ifdef __cplusplus
}
#endif

#endif
