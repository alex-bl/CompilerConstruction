#ifndef MCC_SYMTAB_ERROR_PRINT_H
#define MCC_SYMTAB_ERROR_PRINT_H

#include <stdio.h>

#include "ast_program.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_print_semantic_errors(struct mCc_ast_program *program,
                                      FILE *out);

#ifdef __cplusplus
}
#endif

#endif
