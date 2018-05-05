#ifndef MCC_SYMTAB_HANDLE_H
#define MCC_SYMTAB_HANDLE_H

#include <stdbool.h>

#include "mCc/ast.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validator.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: only this one needed?
bool mCc_symtab_perform_semantic_checks(struct mCc_ast_program *program);

#ifdef __cplusplus
}
#endif

#endif
