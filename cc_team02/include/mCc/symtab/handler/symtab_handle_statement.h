#ifndef MCC_SYMTAB_HANDLE_STATEMENT_H
#define MCC_SYMTAB_HANDLE_STATEMENT_H

#include "mCc/ast/basis/ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_handle_statement_if(struct mCc_ast_statement *statement,
                                    void *data);

void mCc_symtab_handle_statement_while(struct mCc_ast_statement *statement,
                                       void *data);

void mCc_symtab_handle_statement_return(struct mCc_ast_statement *statement,
                                        void *data);

void mCc_symtab_handle_statement_declaration(
    struct mCc_ast_statement *statement, void *data);

void mCc_symtab_handle_statement_assignment(struct mCc_ast_statement *statement,
                                            void *data);

void mCc_symtab_handle_statement_expression(struct mCc_ast_statement *statement,
                                            void *data);

#ifdef __cplusplus
}
#endif

#endif
