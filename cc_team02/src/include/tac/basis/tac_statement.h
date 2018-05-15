#ifndef MCC_AST_TAC_STATEMENT_H
#define MCC_AST_TAC_STATEMENT_H

#include <stdio.h>

#include "basic_tac.h"
#include "ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_statement_if(struct mCc_ast_statement *statement,
                          struct mCc_tac_element *previous_tac);

void mCc_tac_statement_while(struct mCc_ast_statement *statement,
                             struct mCc_tac_element *previous_tac);

void mCc_tac_statement_return(struct mCc_ast_statement *statement,
                              struct mCc_tac_element *previous_tac);

void mCc_tac_statement_declaration(struct mCc_ast_statement *statement,
                                   struct mCc_tac_element *previous_tac);

void mCc_tac_statement_assignment(struct mCc_ast_statement *statement,
                                  struct mCc_tac_element *previous_tac);

void mCc_tac_statement_expression(struct mCc_ast_statement *statement,
                                  struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
