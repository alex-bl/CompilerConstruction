#ifndef MCC_AST_PRINT_STATEMENT_H
#define MCC_AST_PRINT_STATEMENT_H

#include <stdio.h>

#include "mCc/ast/basis/ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_print_dot_statement_if(struct mCc_ast_statement *statement,
                                void *data);

void mCc_print_dot_statement_while(struct mCc_ast_statement *statement,
                                   void *data);

void mCc_print_dot_statement_return(struct mCc_ast_statement *statement,
                                    void *data);

void mCc_print_dot_statement_declaration(struct mCc_ast_statement *statement,
                                         void *data);

void mCc_print_dot_statement_assignment(struct mCc_ast_statement *statement,
                                        void *data);

void mCc_print_dot_statement_expression(struct mCc_ast_statement *statement,
                                        void *data);

#ifdef __cplusplus
}
#endif

#endif
