#ifndef MCC_AST_TAC_PROGRAM_H
#define MCC_AST_TAC_PROGRAM_H

#include <stdio.h>

#include "mCc/ast/basis/ast_program.h"
#include "mCc/tac/basis/basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_program(struct mCc_ast_program *program,
                     struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
