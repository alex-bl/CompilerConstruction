#include "mCc/symtab/handler/symtab_handle_function.h"

#include <assert.h>
#include <stddef.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/base_validator.h"

/*
 * TODO:
 * - check for main
 * - check if has a return
 */
void mCc_symtab_handle_function_def(struct mCc_ast_function_def *def,
                                    void *data)
{
	assert(def);
	assert(data);

	log_debug("Processing function-def '%s'...",
	          def->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	// check for duplicates
	mCc_process_validation(mCc_validator_check_duplicates,
	                       mCc_symtab_insert_function_def_node,
	                       info_holder->symbol_table->parent, def->identifier,
	                       def->identifier, info_holder, def);

	// check for return-types
	mCc_process_validation(mCc_validator_check_return_type, NULL,
	                       info_holder->symbol_table->parent, def->identifier,
	                       def, info_holder, def);

	// only on last function
	if (!def->next_function_def) {
		// check for main
		mCc_process_validation(mCc_validator_check_main_presence, NULL,
		                       info_holder->symbol_table->parent,
		                       def->identifier, def, info_holder, def);
	}
	log_debug("Done");
}
