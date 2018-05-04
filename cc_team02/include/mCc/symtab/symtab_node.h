#ifndef MCC_SYMTAB_NODE_H
#define MCC_SYMTAB_NODE_H

#include <stddef.h>
#include <stdbool.h>

#include "mCc/ast/basis/ast_data_type.h"
#include "mCc/ast/basis/ast_identifier.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_symtab_identifier_type {
	MCC_SYM_TAB_IDENTIFIER_VARIABLE_PRIMITIVE,
	MCC_SYM_TAB_IDENTIFIER_VARIABLE_ARRAY,
	MCC_SYM_TAB_IDENTIFIER_FUNCTION,
	MCC_SYM_TAB_IDENTIFIER_FUNCTION_PARAMETER,
};

/**
 * Used for function defs:
 * - The symbol_table_node contains (if a function def) a link to the next
 * parameter
 * - Iterating over the parameters the signature can be constructed by a lookup
 * in the current scope-symbol-table
 */
struct mCc_symtab_parameter_ref {
	struct mCc_ast_identifier *identifier;
	struct mCc_symtab_parameter_ref *next_parameter;
};

// TODO: maybe extend with other information?
struct mCc_symbol_table_node {
	enum mCc_symtab_identifier_type entry_type;
	enum mCc_ast_data_type data_type;
	bool already_defined;
	// for arrays
	size_t size;
	struct mCc_symtab_parameter_ref *next_parameter;
};

void mCc_symtab_delete_symtab_parameter_ref(
    struct mCc_symtab_parameter_ref *ref);

void mCc_symtab_delete_symtab_node(struct mCc_symbol_table_node *node);

#ifdef __cplusplus
}
#endif

#endif
