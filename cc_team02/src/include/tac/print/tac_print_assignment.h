#ifndef MCC_AST_TAC_ASSIGNMENT_H
#define MCC_AST_TAC_ASSIGNMENT_H

#include <stdio.h>

#include "ast_assignment.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_tac_print_assignment_primitive(struct mCc_ast_assignment *assignment,
                                        void *data);

void mCc_tac_print_assignment_array(struct mCc_ast_assignment *assignment,
                                    void *data);

#ifdef __cplusplus
}
#endif

#endif
