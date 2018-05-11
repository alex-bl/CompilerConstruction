#ifndef MCC_SYMTAB_HANDLE_H
#define MCC_SYMTAB_HANDLE_H

#include <stdbool.h>

#include "mCc/ast.h"
#include "symbol_table.h"
#include "validator.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: only this one needed?
int mCc_symtab_perform_semantic_checks(struct mCc_ast_program *program);

#ifdef __cplusplus
}
#endif

#endif
