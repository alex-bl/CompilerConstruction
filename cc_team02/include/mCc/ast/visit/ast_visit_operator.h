#ifndef MCC_AST_VISIT_OPERATOR_H
#define MCC_AST_VISIT_OPERATOR_H

#include "mCc/ast/basis/ast_operator.h"
// is "container"  of ast_visitors
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_operator(struct mCc_ast_operator *operator,
                            struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
