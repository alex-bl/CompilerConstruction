#ifndef MCC_SYMTAB_NODE_TYPES_H
#define MCC_SYMTAB_NODE_TYPES_H

#include <stdbool.h>

#include "ast_data_type.h"
#include "map.h"
#include "symtab_types.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: maybe extend with other information?
struct mCc_symbol_table_node {
	enum mCc_symtab_identifier_type entry_type;
	enum mCc_ast_data_type data_type;
	bool already_defined;
	int scope_level;
	// for arrays
	size_t size;
	struct mCc_symtab_parameter_ref *next_parameter;
};

#ifdef __cplusplus
}
#endif

#endif
