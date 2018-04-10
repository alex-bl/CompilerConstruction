#include "mCc/symtab/handler/symtab_handle_function.h"
#include "mCc/symtab/symbol_table.h"

#include <assert.h>
#include <stddef.h>

void mCc_symtab_handle_function_def(struct mCc_ast_function_def *def,
                                    void *data)
{
	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_symbol_table *parent_scope_symtab = info_holder->symbol_table;

	struct mCc_symbol_table *current_scope_symtab =
	    mCc_symtab_new_symbol_table(parent_scope_symtab);

	// set new actual symtab
	((struct mCc_symtab_and_validation_holder *)data)->symbol_table =
	    current_scope_symtab;

	/*
	 * TODO: Wie kehrt man zum "alten" scope zurück?
	 * => Machbar so wie jetzt oder "scope-counter"?
	 * => Eigene "scope-manager"? => callbacks, die symbol-table verschieben
	 */
}

void mCc_symtab_handle_function_call(struct mCc_ast_function_call *call,
                                     void *data)
{
	/*TODO*/
}
