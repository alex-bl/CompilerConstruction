#ifndef MCC_AST_TAC_DECLARATION_H
#define MCC_AST_TAC_DECLARATION_H

#include <stdio.h>

#include "ast_declaration.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_tac_operation tac_helper_data_type_to_tac_declaration_primitive(
    enum mCc_ast_data_type data_type);

enum mCc_tac_operation
tac_helper_data_type_to_tac_declaration_array(enum mCc_ast_data_type data_type);

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
