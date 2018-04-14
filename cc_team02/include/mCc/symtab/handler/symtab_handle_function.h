#ifndef MCC_SYMTAB_HANDLE_FUNCTION_H
#define MCC_SYMTAB_HANDLE_FUNCTION_H

#include "mCc/ast/basis/ast_function.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_function_def_enter_scope(struct mCc_ast_function_def *def,
                                    void *data);

void mCc_symtab_function_def_leave_scope(struct mCc_ast_function_def *def,
                                    void *data);

#ifdef __cplusplus
}
#endif

#endif
