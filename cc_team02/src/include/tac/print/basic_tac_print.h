#ifndef MCC_AST_BASIC_TAC_H
#define MCC_AST_BASIC_TAC_H

#include <stdio.h>
#include "ast_data_type.h"
#include "basic_tac.h"

#define LABEL_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif

void tac_print(struct mCc_tac_element *element, void *data);

#ifdef __cplusplus
}
#endif

#endif