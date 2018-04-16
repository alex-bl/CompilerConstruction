#ifndef MCC_BASE_VALIDATOR_H
#define MCC_BASE_VALIDATOR_H

#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validator.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 * @param symbol_table
 * @param identifier
 * @return
 */
enum mCc_validation_status_type
mCc_validator_check_definition(struct mCc_symbol_table *symbol_table,
                               void *validator_input);

/**
 *
 * @param symbol_table
 * @param identifier
 * @return
 */
enum mCc_validation_status_type
mCc_validator_check_duplicates(struct mCc_symbol_table *symbol_table,
                               void *validator_input);

/**
 *
 * @param symbol_table
 * @param validator_input
 * @return
 */
enum mCc_validation_status_type
mCc_validator_check_main_presence(struct mCc_symbol_table *symbol_table,
                                  void *validator_input);

/**
 *
 * @param symbol_table
 * @param validator_input
 * @return
 */
enum mCc_validation_status_type
mCc_validator_check_return_type(struct mCc_symbol_table *symbol_table,
                                void *validator_input);

#ifdef __cplusplus
}
#endif

#endif
