#ifndef MCC_SYMTAB_HANDLE_LITERAL_H
#define MCC_SYMTAB_HANDLE_LITERAL_H

#include "mCc/ast/basis/ast_literal.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_handle_literal_int(struct mCc_ast_literal *literal, void *data);

void mCc_symtab_handle_literal_float(struct mCc_ast_literal *literal,
                                     void *data);

void mCc_symtab_handle_literal_bool(struct mCc_ast_literal *literal,
                                    void *data);

void mCc_symtab_handle_literal_string(struct mCc_ast_literal *literal,
                                      void *data);

#ifdef __cplusplus
}
#endif

#endif
