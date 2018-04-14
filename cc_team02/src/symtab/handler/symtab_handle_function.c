#include "mCc/symtab/handler/symtab_handle_function.h"

#include <assert.h>
#include <stddef.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"

/*
 * TODO: Do checks if already defined within this scope!
 */
void mCc_symtab_handle_function_def(struct mCc_ast_function_def *def,
                                    void *data)
{
	assert(def);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;
	int scope_level = info_holder->symbol_table->scope_level;

	//TODO: base_validator-h-checks

	log_debug("Inserting function-definition and parameters to symbol-table "
	          "scope %d...",
	          scope_level);

	mCc_symtab_insert_function_def_node(info_holder->symbol_table, def);

	log_debug("Function-definition and parameters inserted to symbol-table "
	          "scope %d...",
	          scope_level);
}
