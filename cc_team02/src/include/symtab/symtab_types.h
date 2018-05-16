#ifndef MCC_SYMTAB_TYPES_H
#define MCC_SYMTAB_TYPES_H

#include <stdbool.h>

#include "map.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef map_t(struct mCc_symbol_table_node *) mCc_symbol_table_map_t;

struct mCc_symbol_table {
	// TODO: local or on heap?
	mCc_symbol_table_map_t table;
	struct mCc_symbol_table *parent;
	int scope_level;
};

// is passed via userdata (visitors)
struct mCc_symtab_and_validation_holder {
	struct mCc_symbol_table *symbol_table;
	int scope_level;
	int error_count;
	// for error handling at statements
	struct mCc_ast_identifier *function_identifier;
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

enum mCc_symtab_identifier_type {
	MCC_SYM_TAB_IDENTIFIER_VARIABLE_PRIMITIVE,
	MCC_SYM_TAB_IDENTIFIER_VARIABLE_ARRAY,
	MCC_SYM_TAB_IDENTIFIER_FUNCTION,
	MCC_SYM_TAB_IDENTIFIER_FUNCTION_PARAMETER,
};

#ifdef __cplusplus
}
#endif

#endif
