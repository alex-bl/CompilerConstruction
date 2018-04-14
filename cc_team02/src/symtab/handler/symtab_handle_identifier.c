#include "mCc/symtab/handler/symtab_handle_identifier.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validator.h"

#include "log.h"

#include <assert.h>
#include <stddef.h>

void mCc_symtab_handle_identifier(struct mCc_ast_identifier *identifier,
                                  void *data)
{
	assert(identifier);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	// search for info
	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(info_holder->symbol_table, identifier);

	if (!symtab_info) {
		// TODO: more senseful error-msg
		struct mCc_validation_status_result *semantic_error =
		    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_NO_DEF,
		                                        identifier->identifier_name);
		// append
		mCc_validator_append_semantic_error(info_holder->first_semantic_error,
		                                    semantic_error);
	} else {
		// link
		identifier->symtab_info = symtab_info;
	}
}
