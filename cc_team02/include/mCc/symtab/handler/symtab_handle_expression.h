#ifndef MCC_SYMTAB_HANDLE_EXPRESSION_H
#define MCC_SYMTAB_HANDLE_EXPRESSION_H

#include "mCc/ast/basis/ast_expression.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_handle_expression_binary_op_post_order(
    struct mCc_ast_expression *expression, void *data);

void mCc_handle_expression_parenth_post_order(
    struct mCc_ast_expression *expression, void *data);

void mCc_handle_expression_identifier_post_order(
    struct mCc_ast_expression *expression, void *data);

void mCc_handle_expression_identifier_array_post_order(
    struct mCc_ast_expression *expression, void *data);

void mCc_handle_expression_function_call_post_order(
    struct mCc_ast_expression *expression, void *data);

void mCc_handle_expression_unary_op_post_order(
    struct mCc_ast_expression *expression, void *data);

void mCc_handle_expression_literal_post_order(
    struct mCc_ast_expression *expression, void *data);

#ifdef __cplusplus
}
#endif

#endif
