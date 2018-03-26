#ifndef MCC_AST_VISIT_EXPRESSION_H
#define MCC_AST_VISIT_EXPRESSION_H

#include "mCc/ast/basis/ast_expression.h"
// is "container"  of ast_visitors
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_visit_next_expression(struct mCc_ast_expression *expr,
                               struct mCc_ast_visitor *visitor);

void mCc_ast_visit_expression(struct mCc_ast_expression *expression,
                              struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
