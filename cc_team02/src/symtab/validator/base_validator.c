#include "mCc/symtab/validator/base_validator.h"

#include <stddef.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"

struct mCc_validation_status_result *
mCc_validator_check_definition(struct mCc_symbol_table *symbol_table,
                               struct mCc_ast_identifier *identifier)
{
	// only look at current scope
	if (!mCc_symtab_lookup(symbol_table, identifier, true)) {
		char error_msg[ERROR_MSG_BUF_SIZE];
		snprintf(error_msg, sizeof(error_msg), "Implicit declaration of '%s'",
		         identifier->identifier_name);
		return mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_NO_DEF,
		                                           error_msg);
	}
	// return for consistency
	return mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_VALID, "");
}

struct mCc_validation_status_result *
mCc_validator_check_duplicates(struct mCc_symbol_table *symbol_table,
                               struct mCc_ast_identifier *identifier)
{
	// only look at current scope
	if (mCc_symtab_lookup(symbol_table, identifier, true)) {
		char error_msg[ERROR_MSG_BUF_SIZE];
		snprintf(error_msg, sizeof(error_msg), "'%s' already defined",
		         identifier->identifier_name);
		return mCc_validator_new_validation_result(
		    MCC_VALIDATION_STATUS_NOT_UNIQUE, error_msg);
	}
	// return for consistency
	return mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_VALID, "");
}
