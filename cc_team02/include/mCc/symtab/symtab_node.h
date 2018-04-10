#ifndef MCC_SYMTAB_NODE_H
#define MCC_SYMTAB_NODE_H

#include "mCc/ast/basis/ast_data_type.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_symtab_identifier_type {
	MCC_SYM_TAB_IDENTIFIER_VARIABLE,
	MCC_SYM_TAB_IDENTIFIER_FUNCTION,
	MCC_SYM_TAB_IDENTIFIER_FUNCTION_PARAMETER,
};

// TODO: maybe extend with other information?
struct mCc_symbol_table_node {
	enum mCc_symtab_identifier_type entry_type;
	// int scope_level;
	union {
		/*var*/
		enum mCc_ast_data_type data_type;
		/*function*/
		struct {
			enum mCc_ast_data_type return_type;
			struct mCc_symbol_table_node *first_parameter;
		};
		/*parameter*/
		struct {
			enum mCc_ast_data_type parameter_type;
			struct mCc_symbol_table_node *next_parameter;
		};
	};
};

#ifdef __cplusplus
}
#endif

#endif
