#ifndef MCC_AST_TAC_DECLARATION_H
#define MCC_AST_TAC_DECLARATION_H

#include <stdio.h>

#include "ast_declaration.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_tac_element *
mCc_tac_declaration_primitive(struct mCc_ast_declaration *declaration,
                              struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_declaration_array(struct mCc_ast_declaration *declaration,
                          struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
