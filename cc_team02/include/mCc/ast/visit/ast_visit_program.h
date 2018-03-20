#ifndef MCC_AST_VISIT_PROGRAM_H
#define MCC_AST_VISIT_PROGRAM_H

#include "mCc/ast/basis/ast_program.h"
// is "container"  of ast_visitors
#include "mCc/ast_visit.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_visit_program(struct mCc_ast_program *program,
                           struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
