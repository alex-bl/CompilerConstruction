#ifndef MCC_AST_VISIT_DECLARATION_H
#define MCC_AST_VISIT_DECLARATION_H

#include "mCc/ast/basis/ast_declaration.h"
// is "container"  of ast_visitors
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_declaration(struct mCc_ast_declaration *declaration,
                               struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
