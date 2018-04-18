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
	struct mCc_validation_status_result *first_semantic_error;
};


#ifdef __cplusplus
}
#endif

#endif
