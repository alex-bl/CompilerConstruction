#ifndef MCC_AST_TAC_EXPRESSION_H
#define MCC_AST_TAC_EXPRESSION_H

#include <stdio.h>

#include "ast_expression.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_tac_element *
helper_get_tac_of_expression(struct mCc_ast_expression *expression,
                             struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_expression_literal(struct mCc_ast_expression *expression,
                           struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_expression_binary_op(struct mCc_ast_expression *expression,
                             struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_expression_parenth(struct mCc_ast_expression *expression,
                           struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_expression_identifier(struct mCc_ast_expression *expression,
                              struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_expression_identifier_array(struct mCc_ast_expression *expression,
                                    struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_expression_function_call(struct mCc_ast_expression *expression,
                                 struct mCc_tac_element *previous_tac);

struct mCc_tac_element *
mCc_tac_expression_unary_op(struct mCc_ast_expression *expression,
                            struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
