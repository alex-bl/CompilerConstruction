#ifndef MCC_AST_TAC_IDENTIFIER_H
#define MCC_AST_TAC_IDENTIFIER_H

#include <stdio.h>

#include "basic_tac.h"
#include "ast_identifier.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_tac_element *mCc_tac_identifier(struct mCc_ast_identifier *identifier,
                        struct mCc_tac_element *previous_tac);

#ifdef __cplusplus
}
#endif

#endif
