#ifndef MCC_AST_VISIT_STATEMENT_H
#define MCC_AST_VISIT_STATEMENT_H

#include "ast_statement.h"
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_optional_statement(struct mCc_ast_statement *statement,
                                      struct mCc_ast_visitor *visitor);

void mCc_ast_visit_statement(struct mCc_ast_statement *statement,
                             struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
