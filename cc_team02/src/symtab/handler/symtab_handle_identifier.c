#include "mCc/symtab/handler/symtab_handle_identifier.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validator.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "log.h"

void mCc_symtab_handle_identifier(struct mCc_ast_identifier *identifier,
                                  void *data)
{
	assert(identifier);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	// search for info
	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(info_holder->symbol_table, identifier, false);

	if (!symtab_info) {
		log_debug("Identifier '%s' not found in symboltable",
		          identifier->identifier_name);

		// TODO: more senseful error-msg
		struct mCc_validation_status_result *semantic_error =
		    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_NO_DEF,
		                                        identifier->identifier_name);
		// append
		mCc_validator_append_semantic_error(info_holder->first_semantic_error,
		                                    semantic_error);
	} else {
		log_debug("Identifier '%s' found in symboltable. Proceed with linking",
		          identifier->identifier_name);

		/*
		 * link: use memcpy so that the hash-table can be freed without freeing
		 * the needed references to the values
		 */
		identifier->symtab_info = malloc(sizeof(*(identifier->symtab_info)));

		if (!identifier->symtab_info) {
			log_error(
			    "Malloc failed for associating symtab-info to identifier");
		} else {
			if (!memcpy(identifier->symtab_info, symtab_info,
			            sizeof(*symtab_info))) {
				log_error("Memcpy failed: Could not link symtab-info to "
				          "identifier '%'",
				          identifier->identifier_name);
			}
		}
	}
}
