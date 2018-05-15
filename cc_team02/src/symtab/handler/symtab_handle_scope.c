#include "handler/symtab_handle_scope.h"

#include <assert.h>

#include "log.h"
#include "symbol_table.h"

void mCc_symtab_enter_scope(void *data)
{
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;
	info_holder->scope_level = info_holder->scope_level + 1;

	log_debug("Entering new scope %d", info_holder->scope_level);

	// create a new symbol-table
	struct mCc_symbol_table *symbol_table_new_scope =
	    mCc_symtab_new_symbol_table(info_holder->symbol_table,
	                                info_holder->scope_level);
	// set as new actual symbol-table
	info_holder->symbol_table = symbol_table_new_scope;
}

void mCc_symtab_leave_scope(void *data)
{
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	log_debug("Leaving scope %d", info_holder->symbol_table->scope_level);

	// get current table
	struct mCc_symbol_table *current_symbol_table = info_holder->symbol_table;
	// set parent as actual end remove the table from closing scope
	info_holder->symbol_table = current_symbol_table->parent;
	// remove symtab from closing scope
	mCc_symtab_delete_symbol_table(current_symbol_table);

	log_debug("Reentering parent scope %d",
	          info_holder->symbol_table->scope_level);
}
