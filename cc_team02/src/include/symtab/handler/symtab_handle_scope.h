#ifndef MCC_SYMTAB_HANDLE_SCOPE_H
#define MCC_SYMTAB_HANDLE_SCOPE_H

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_enter_scope(void *data);

void mCc_symtab_leave_scope(void *data);

#ifdef __cplusplus
}
#endif

#endif
