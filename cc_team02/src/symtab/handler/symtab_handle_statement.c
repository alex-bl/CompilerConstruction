#include "mCc/symtab/handler/symtab_handle_statement.h"

#include <assert.h>
#include <stddef.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/base_validator.h"
/*
 * TODO: Do checks if already defined within this scope!
 */
void mCc_symtab_handle_statement_declaration(
    struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;
	int scope_level = info_holder->symbol_table->scope_level;

	/*
	 * TODO:
	 * - base_validator-h-checks
	 * - var declaration and array declaration
	 */

	log_debug("Inserting variable declaration to symbol-table scope %d...",
	          scope_level);
	// are always var-nodes
	mCc_symtab_insert_var_node(info_holder->symbol_table,
	                           statement->declaration);

	log_debug("New variable declaration inserted to symbol-table scope %d",
	          scope_level);
}
