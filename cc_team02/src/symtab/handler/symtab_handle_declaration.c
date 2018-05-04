#include "mCc/symtab/handler/symtab_handle_declaration.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/base_validator.h"
/*
 * TODO: Do checks if already defined within this scope!
 * - primitives and arrays are currently treated equally
 * - maybe there will be a different treatment, so both functions are kept
 */

static bool
handle_declaration(struct mCc_symtab_and_validation_holder *info_holder,
                   struct mCc_ast_declaration *declaration,
                   struct mCc_ast_identifier *identifier)
{
	int scope_level = info_holder->symbol_table->scope_level;
	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(info_holder->symbol_table, identifier, true);
	bool error_occurred = false;

	// already existing
	if (symtab_info) {
		symtab_info->already_defined = true;
		log_debug("Identifier '%s' already defined",
		          identifier->identifier_name);
		// other error handling done at identifier-level
		error_occurred = true;
	} else {
		mCc_symtab_insert_var_node(info_holder->symbol_table, declaration);
		log_debug("New variable declaration inserted to symbol-table scope %d",
		          scope_level);
	}
	return !error_occurred;
}

void mCc_symtab_handle_declaration_primitive_pre_order(
    struct mCc_ast_declaration *declaration, void *data)
{
	assert(declaration);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_identifier *identifier = declaration->identifier;

	handle_declaration(info_holder, declaration, identifier);
}

void mCc_symtab_handle_declaration_array_pre_order(
    struct mCc_ast_declaration *declaration, void *data)
{
	assert(declaration);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;
	int scope_level = info_holder->symbol_table->scope_level;

	struct mCc_ast_identifier *identifier = declaration->array_identifier;

	// adjust symtab-info with size
	if (handle_declaration(info_holder, declaration, identifier)) {
		struct mCc_symbol_table_node *previously_stored =
		    mCc_symtab_lookup(info_holder->symbol_table, identifier, true);
		assert(previously_stored);
		previously_stored->size = declaration->size;
	}
}
