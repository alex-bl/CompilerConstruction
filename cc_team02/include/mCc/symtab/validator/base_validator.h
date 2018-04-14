#ifndef MCC_BASE_VALIDATOR_H
#define MCC_BASE_VALIDATOR_H

#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validator.h"

#ifdef __cplusplus
extern "C" {
#endif

//TODO: provide implementation

/**
 *
 * @param symbol_table
 * @param identifier
 * @return
 */
struct mCc_validation_status_result *
mCc_validator_check_definition(struct mCc_symbol_table *symbol_table,
                               struct mCc_ast_identifier *identifier);

/**
 *
 * @param symbol_table
 * @param identifier
 * @return
 */
struct mCc_validation_status_result *
mCc_validator_check_duplicates(struct mCc_symbol_table *symbol_table,
                               struct mCc_ast_identifier *identifier);

#ifdef __cplusplus
}
#endif

#endif
