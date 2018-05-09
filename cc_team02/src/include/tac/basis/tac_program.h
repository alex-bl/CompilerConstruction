#ifndef MCC_AST_TAC_PROGRAM_H
#define MCC_AST_TAC_PROGRAM_H

#include <stdio.h>

#include "ast_program.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_program(struct mCc_ast_program *program, void *data);

#ifdef __cplusplus
}
#endif

#endif
