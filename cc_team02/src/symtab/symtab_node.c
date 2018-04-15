#include "mCc/symtab/symtab_node.h"

#include <assert.h>
#include <stdlib.h>

void mCc_symtab_delete_symtab_parameter_ref(
    struct mCc_symtab_parameter_ref *ref)
{
	assert(ref);
	if (ref->next_parameter) {
		mCc_symtab_delete_symtab_parameter_ref(ref->next_parameter);
	}
	/*
	 * TODO: identifier is not freed, because it is the same address from the
	 * ast-identifier and it is freed there
	 */
	free(ref);
}

void mCc_symtab_free_symtab_node(struct mCc_symbol_table_node *node)
{

	assert(node);

	switch (node->entry_type) {
	// currently no special treatment in case of freeing
	case MCC_SYM_TAB_IDENTIFIER_FUNCTION_PARAMETER:
	case MCC_SYM_TAB_IDENTIFIER_VARIABLE: free(node); break;
	case MCC_SYM_TAB_IDENTIFIER_FUNCTION:
		if (node->next_parameter) {
			mCc_symtab_delete_symtab_parameter_ref(node->next_parameter);
		}
		free(node);
		break;
	}
}
