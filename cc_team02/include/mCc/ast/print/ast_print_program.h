#ifndef MCC_AST_PRINT_PROGRAM_H
#define MCC_AST_PRINT_PROGRAM_H

#include <stdio.h>

#include "mCc/ast/basis/ast_program.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_program(FILE *out, struct mCc_ast_program *program);

#ifdef __cplusplus
}
#endif

#endif
