#include "mCc/symtab/handler/symtab_handle_declaration.h"

#include <assert.h>
#include <stddef.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/base_validator.h"
/*
 * TODO: Do checks if already defined within this scope!
 * - primitives and arrays are currently treated equally
 * - maybe there will be a different treatment, so both functions are kept
 */

void mCc_symtab_handle_declaration_primitive(
    struct mCc_ast_declaration *declaration, void *data)
{
	assert(declaration);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;
	int scope_level = info_holder->symbol_table->scope_level;

	/*
	 * TODO:
	 * - base_validator-h-checks
	 */

	log_debug("Inserting variable declaration to symbol-table scope %d...",
	          scope_level);

	mCc_process_validation(mCc_validator_check_duplicates,
	                       mCc_symtab_insert_var_node,
	                       info_holder->symbol_table, declaration->identifier,
	                       info_holder, declaration);

	log_debug("New variable declaration inserted to symbol-table scope %d",
	          scope_level);
}

void mCc_symtab_handle_declaration_array(
    struct mCc_ast_declaration *declaration, void *data)
{
	assert(declaration);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;
	int scope_level = info_holder->symbol_table->scope_level;

	/*
	 * TODO:
	 * - base_validator-h-checks
	 * - var declaration and array declaration
	 */

	log_debug("Inserting array declaration to symbol-table scope %d...",
	          scope_level);
	// are always var-nodes
	mCc_process_validation(
	    mCc_validator_check_duplicates, mCc_symtab_insert_var_node,
	    info_holder->symbol_table, declaration->array_identifier, info_holder,
	    declaration);

	log_debug("New array declaration inserted to symbol-table scope %d",
	          scope_level);
}
