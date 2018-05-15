#ifndef MCC_AST_TAC_DECLARATION_H
#define MCC_AST_TAC_DECLARATION_H

#include <stdio.h>

#include "basic_tac.h"
#include "ast_declaration.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_declaration_primitive(struct mCc_ast_declaration *declaration,
                                   struct mCc_tac_element *previous_tac);

void mCc_tac_declaration_array(struct mCc_ast_declaration *declaration,
                               struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
