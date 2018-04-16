#include "mCc/symtab/validator/base_validator.h"

#include <stddef.h>

#include "mCc/symtab/symbol_table.h"

enum mCc_validation_status_type
mCc_validator_check_definition(struct mCc_symbol_table *symbol_table,
                               struct mCc_ast_identifier *identifier)
{
	// only look at current scope
	if (!mCc_symtab_lookup(symbol_table, identifier, true)) {
		return MCC_VALIDATION_STATUS_NO_DEF;
	}
	return MCC_VALIDATION_STATUS_VALID;
}

enum mCc_validation_status_type
mCc_validator_check_duplicates(struct mCc_symbol_table *symbol_table,
                               struct mCc_ast_identifier *identifier)
{
	// only look at current scope
	if (mCc_symtab_lookup(symbol_table, identifier, true)) {
		return MCC_VALIDATION_STATUS_NOT_UNIQUE;
	}
	return MCC_VALIDATION_STATUS_VALID;
}
