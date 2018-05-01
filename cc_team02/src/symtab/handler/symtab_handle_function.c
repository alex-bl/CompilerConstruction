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
	mCc_process_validation(
	    mCc_validator_check_duplicates, mCc_symtab_insert_function_def_node,
	    info_holder->symbol_table->parent, def->identifier, info_holder, def);

	// check for return-types
	mCc_process_validation(mCc_validator_check_return_type, NULL,
	                       info_holder->symbol_table->parent, def, info_holder,
	                       def);

	// only on last function
	if (!def->next_function_def) {
		// check for main
		mCc_process_validation(mCc_validator_check_main_presence, NULL,
		                       info_holder->symbol_table->parent, def,
		                       info_holder, def);
	}
	log_debug("Function-def checking completed");
}

void mCc_symtab_handle_function_call(struct mCc_ast_function_call *call,
                                     void *data)
{
	assert(call);
	assert(data);

	log_debug("Checking function-call-signature '%s'...",
	          call->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_symbol_table_node *identifier_info =
	    mCc_symtab_lookup(info_holder->symbol_table, call->identifier, false);
	// identifier-checker are usually called after function_calls
	if (!identifier_info) {
		log_debug("Function '%s' not found. Error will be reported later",
		          call->identifier->identifier_name);
	} else {
		/*
		 * this info is needed here to build the error-message
		 * it is just temporary because the subsequent identifier-handler will
		 * overwrite it (memcpy)
		 */
		call->identifier->symtab_info = identifier_info;

		mCc_process_validation(mCc_validator_check_signature, NULL,
		                       info_holder->symbol_table, call, info_holder,
		                       call);
	}
	log_debug("Signature checking completed");
}
