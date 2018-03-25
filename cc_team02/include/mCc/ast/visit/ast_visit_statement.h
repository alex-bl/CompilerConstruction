#ifndef MCC_AST_VISIT_STATEMENT_H
#define MCC_AST_VISIT_STATEMENT_H

#include "mCc/ast/basis/ast_statement.h"
// is "container"  of ast_visitors
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_statement(struct mCc_ast_statement *statement,
                             struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif


