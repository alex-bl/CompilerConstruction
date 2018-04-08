#ifndef MCC_SYMTAB_HANDLE_EXPRESSION_H
#define MCC_SYMTAB_HANDLE_EXPRESSION_H

#include "mCc/ast/basis/ast_expression.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_handle_expression_literal(struct mCc_ast_expression *expression,
                                          void *data);

void mCc_symtab_handle_expression_binary_op(
    struct mCc_ast_expression *expression, void *data);

void mCc_symtab_handle_expression_parenth(struct mCc_ast_expression *expression,
                                          void *data);

void mCc_symtab_handle_expression_identifier(
    struct mCc_ast_expression *expression, void *data);

void mCc_symtab_handle_expression_identifier_array(
    struct mCc_ast_expression *expression, void *data);

void mCc_symtab_handle_expression_function_call(
    struct mCc_ast_expression *expression, void *data);

void mCc_symtab_handle_expression_unary_op(
    struct mCc_ast_expression *expression, void *data);

#ifdef __cplusplus
}
#endif

#endif
