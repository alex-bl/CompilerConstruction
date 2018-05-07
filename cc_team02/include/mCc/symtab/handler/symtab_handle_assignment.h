#ifndef MCC_SYMTAB_HANDLE_ASSIGNMENT_H
#define MCC_SYMTAB_HANDLE_ASSIGNMENT_H

#include "mCc/ast/basis/ast_assignment.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_handle_primitive_assignment_post_order(struct mCc_ast_assignment *assignment,
                                  void *data);

void mCc_symtab_handle_array_assignment_post_order(struct mCc_ast_assignment *assignment,
                                        void *data);

#ifdef __cplusplus
}
#endif

#endif
