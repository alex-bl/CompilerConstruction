#include "mCc/symtab/handler/symtab_handle_function.h"

#include <assert.h>
#include <stddef.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/base_validator.h"

/*
 * TODO: Do checks if already defined within this scope!
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

	// function-defs are stored at symboltable with scope lvl 0
	enum mCc_validation_status_type duplicate_check =
	    mCc_validator_check_duplicates(info_holder->symbol_table->parent,
	                                  def->identifier);

	if (duplicate_check == MCC_VALIDATION_STATUS_VALID) {
		log_debug("Function-def '%s' is valid. Store it int symbol-table.",
		          def->identifier->identifier_name);
		// function-defs are always inserted at scope-level 0 => so parent
		mCc_symtab_insert_function_def_node(info_holder->symbol_table->parent,
		                                    def);
		log_debug("Done");
	} else {
		struct mCc_validation_status_result *status_result =
		    mCc_validator_create_error_status(duplicate_check, def->identifier);
		mCc_validor_store_result_to_handler(info_holder, status_result);

		log_debug("Function-def '%s' already defined. Semantic error reported",
		          def->identifier->identifier_name);
	}

	log_debug("Done");
}
