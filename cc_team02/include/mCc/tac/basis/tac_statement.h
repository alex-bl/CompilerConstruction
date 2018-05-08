#ifndef MCC_AST_TAC_STATEMENT_H
#define MCC_AST_TAC_STATEMENT_H

#include <stdio.h>

#include "mCc/tac/basis/ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_statement_if(struct mCc_ast_statement *statement,
                                void *data);

void mCc_tac_statement_while(struct mCc_ast_statement *statement,
                                   void *data);

void mCc_tac_statement_return(struct mCc_ast_statement *statement,
                                    void *data);

void mCc_tac_statement_declaration(struct mCc_ast_statement *statement,
                                         void *data);

void mCc_tac_statement_assignment(struct mCc_ast_statement *statement,
                                        void *data);

void mCc_tac_statement_expression(struct mCc_ast_statement *statement,
                                        void *data);

#ifdef __cplusplus
}
#endif

#endif
