#ifndef MCC_AST_VISIT_DECLARATION_H
#define MCC_AST_VISIT_DECLARATION_H

#include "ast_declaration.h"
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_optional_declaration(struct mCc_ast_declaration *declaration,
                                        struct mCc_ast_visitor *visitor);

void mCc_ast_visit_declaration(struct mCc_ast_declaration *declaration,
                               struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
