#ifndef MCC_AST_VISIT_IDENTIFIER_H
#define MCC_AST_VISIT_IDENTIFIER_H

#include "mCc/ast/basis/ast_identifier.h"
// is "container"  of ast_visitors
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_identifier(struct mCc_ast_identifier *identifier,
                              struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
