#ifndef MCC_AST_PRINT_LITERAL_H
#define MCC_AST_PRINT_LITERAL_H

#include <stdio.h>

#include "mCc/ast/basis/ast_literal.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_print_dot_literal_int(struct mCc_ast_literal *literal, void *data);

void mCc_print_dot_literal_float(struct mCc_ast_literal *literal, void *data);

void mCc_print_dot_literal_bool(struct mCc_ast_literal *literal, void *data);

void mCc_print_dot_literal_string(struct mCc_ast_literal *literal, void *data);

#ifdef __cplusplus
}
#endif

#endif
