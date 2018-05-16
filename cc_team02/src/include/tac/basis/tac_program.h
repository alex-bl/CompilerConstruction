#ifndef MCC_AST_TAC_PROGRAM_H
#define MCC_AST_TAC_PROGRAM_H

#include <stdio.h>

#include "ast_program.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_tac_element *mCc_tac_program(struct mCc_ast_program *program,
                                        struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
