#ifndef MCC_AST_PRINT_ASSIGNMENT_H
#define MCC_AST_PRINT_ASSIGNMENT_H

#include <stdio.h>

#include "mCc/ast/basis/ast_assignment.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_assignment(FILE *out,
                                  struct mCc_ast_assignment *assignment);

#ifdef __cplusplus
}
#endif

#endif