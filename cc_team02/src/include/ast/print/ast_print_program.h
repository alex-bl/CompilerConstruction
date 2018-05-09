#ifndef MCC_AST_PRINT_PROGRAM_H
#define MCC_AST_PRINT_PROGRAM_H

#include <stdio.h>

#include "ast_program.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_print_dot_program(struct mCc_ast_program *program, void *data);

#ifdef __cplusplus
}
#endif

#endif
