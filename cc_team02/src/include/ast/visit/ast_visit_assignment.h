#ifndef MCC_AST_VISIT_ASSIGNMENT_H
#define MCC_AST_VISIT_ASSIGNMENT_H

#include "ast_assignment.h"
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_assignment(struct mCc_ast_assignment *assignment,
                              struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
