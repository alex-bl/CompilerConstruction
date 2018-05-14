#ifndef MCC_AST_TAC_ASSIGNMENT_H
#define MCC_AST_TAC_ASSIGNMENT_H

#include <stdio.h>

#include "mCc/ast/basis/ast_assignment.h"
#include "mCc/tac/basis/basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                                  struct mCc_tac_element *previous_tac);

void mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                              struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
