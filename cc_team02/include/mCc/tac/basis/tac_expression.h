#ifndef MCC_AST_TAC_EXPRESSION_H
#define MCC_AST_TAC_EXPRESSION_H

#include <stdio.h>

#include "mCc/ast/basis/ast_expression.h"
#include "mCc/tac/basis/basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_expression_literal(struct mCc_ast_expression *expression,
                                struct mCc_tac_element *previous_tac);

void mCc_tac_expression_binary_op(struct mCc_ast_expression *expression,
                                  struct mCc_tac_element *previous_tac);

void mCc_tac_expression_parenth(struct mCc_ast_expression *expression,
                                struct mCc_tac_element *previous_tac);

void mCc_tac_expression_identifier(struct mCc_ast_expression *expression,
                                   struct mCc_tac_element *previous_tac);

void mCc_tac_expression_identifier_array(struct mCc_ast_expression *expression,
                                         struct mCc_tac_element *previous_tac);

void mCc_tac_expression_function_call(struct mCc_ast_expression *expression,
                                      struct mCc_tac_element *previous_tac);

void mCc_tac_expression_unary_op(struct mCc_ast_expression *expression,
                                 struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
