#include "mCc/symtab/handler/symtab_handle_identifier.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validator.h"

#include "log.h"

static void
append_error_to_identifier(struct mCc_ast_identifier *identifier,
                           struct mCc_validation_status_result *error)
{
	if (!identifier->semantic_error) {
		identifier->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(identifier->semantic_error, error);
	}
}

static void
handle_identifier(struct mCc_ast_identifier *identifier,
                  enum mCc_validation_status_type status,
                  struct mCc_symtab_and_validation_holder *info_holder)
{
	const char *format_string;
	if (status == MCC_VALIDATION_STATUS_NO_DEF) {
		format_string = "Implicit declaration of '%s'";
	} else {
		format_string = "Duplicate identifier '%s'";
	}

	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE, format_string,
	         identifier->identifier_name);
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        status, strndup(error_msg, strlen(error_msg)));
	append_error_to_identifier(identifier, error);
	info_holder->error_occurred = true;
}

static void link_symtab_info(struct mCc_ast_identifier *identifier,
                             struct mCc_symbol_table_node *symtab_info)
{
	identifier->symtab_info = malloc(sizeof(*(identifier->symtab_info)));

	if (!identifier->symtab_info) {
		log_error("Malloc failed for associating symtab-info to identifier");
	} else {
		if (!memcpy(identifier->symtab_info, symtab_info,
		            sizeof(*symtab_info))) {
			log_error("Memcpy failed: Could not link symtab-info to "
			          "identifier '%'",
			          identifier->identifier_name);
		}
	}
}

// do this preorder
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

	// identifier does not exists
	if (!symtab_info) {

		log_debug("Identifier '%s' not found in symboltable",
		          identifier->identifier_name);
		handle_identifier(identifier, MCC_VALIDATION_STATUS_NO_DEF,
		                  info_holder);
	} // was already classified as duplicate
	else if (symtab_info->already_defined) {
		log_debug("Identifier '%s' already defined",
		          identifier->identifier_name);
		handle_identifier(identifier, MCC_VALIDATION_STATUS_NOT_UNIQUE,
		                  info_holder);
	} else {
		log_debug("Identifier '%s' found in symboltable. Proceed with linking",
		          identifier->identifier_name);
		/*
		 * link: use memcpy so that the hash-table can be freed without freeing
		 * the needed references to the values
		 */
		link_symtab_info(identifier, symtab_info);
	}
}
