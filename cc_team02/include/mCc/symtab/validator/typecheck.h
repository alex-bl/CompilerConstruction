#ifndef MCC_TYPECHECK_H
#define MCC_TYPECHECK_H

#include "mCc/ast.h"
#include "mCc/ast/basis/ast_data_type.h"
#include "mCc/symtab/symtab_types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_ast_data_type
mCc_typecheck_get_type(struct mCc_symbol_table *symbol_table,
                       struct mCc_ast_expression *expr);

enum mCc_validation_status_type
mCc_typecheck_validate_type(struct mCc_symbol_table *symbol_table,
                            void *validator_input);

#ifdef __cplusplus
}
#endif

#endif
