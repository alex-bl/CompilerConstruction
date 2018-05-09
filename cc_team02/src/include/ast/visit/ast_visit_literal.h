#ifndef MCC_AST_VISIT_LITERAL_H
#define MCC_AST_VISIT_LITERAL_H

#include "ast_literal.h"
// is "container"  of ast_visitors
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_literal(struct mCc_ast_literal *literal,
                           struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
