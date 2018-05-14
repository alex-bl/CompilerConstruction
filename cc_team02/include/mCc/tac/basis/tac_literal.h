#ifndef MCC_AST_TAC_LITERAL_H
#define MCC_AST_TAC_LITERAL_H

#include <stdio.h>

#include "mCc/ast/basis/ast_literal.h"
#include "mCc/tac/basis/basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_literal_int(struct mCc_ast_literal *literal,
                         struct mCc_tac_element *previous_tac);

void mCc_tac_literal_float(struct mCc_ast_literal *literal,
                           struct mCc_tac_element *previous_tac);

void mCc_tac_literal_bool(struct mCc_ast_literal *literal,
                          struct mCc_tac_element *previous_tac);

void mCc_tac_literal_string(struct mCc_ast_literal *literal,
                            struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
