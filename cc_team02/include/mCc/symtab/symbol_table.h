#ifndef MCC_SYMBOL_TABLE_H
#define MCC_SYMBOL_TABLE_H

#include "ast/basis/ast_data_type.h"
#include "ast/basis/ast_declaration.h"
#include "ast/basis/ast_function.h"
#include "ast/basis/ast_identifier.h"

#include "map.h"

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

typedef map_t(struct mCc_symbol_table_node *) mCc_symbol_table_map_t;

struct mCc_symbol_table {
	mCc_symbol_table_map_t *table;
	struct mCc_symbol_table *parent;
	int scope_level_table;
	// reference to the scope-level which is set by the visitor
	int *scope_level_visitor;
};

/**
 * Creates a new symbol-table node out of a declaration
 *
 * @param declaration
 * 		The ast-element of declaration
 * @return
 * 		A new symbol-table-node element
 */
struct mCc_symbol_table_node *
mCc_symtab_new_declaration_node(struct mCc_ast_declaration *declaration);

/**
 * Creates a new symbol-table node out of a declaration (for parameter)
 *
 * @param declaration
 * 		The ast-element of declaration
 * @return
 * 		A new symbol-table-node element
 */
struct mCc_symbol_table_node *
mCc_symtab_new_parameter_declaration_node(struct mCc_ast_declaration *declaration);

/**
 * Creates a new symbol-table node out of a function def
 *
 * @param function_def
 * 		The ast-element of function_def
 * @return
 * 		A new symbol-table-node element
 */
struct mCc_symbol_table_node *
mCc_symtab_new_function_def_node(struct mCc_ast_function_def *function_def);

/**
 * Creates a new symbol-table
 *
 * @param parent
 * 		The parent-symbol-table or NULL if it is already the top-table
 * @return
 * 		A new symbol-table
 */
struct mCc_symbol_table *
mCc_symtab_new_symbol_table(struct mCc_symbol_table *parent);

/**
 * Inserts a node into the symbol-table
 *
 * @param symbol_table
 * 		The symbol-table
 * @param key
 * 		The key (identifier)
 * @param value
 * 		The value (information such as type, etc...)
 */
void mCc_symtab_insert_node(struct mCc_symbol_table *symbol_table,
                            struct mCc_ast_identifier *key,
                            struct mCc_symbol_table_node *value);

/**
 * Inserts a node into the symbol-table. More convenient if adding an
 * ast-declaration
 *
 * @param symbol_table
 * 		The symbol-table
 * @param declaration
 * 		The declaration (ast-element)
 */
void mCc_symtab_insert_var_node(struct mCc_symbol_table *symbol_table,
                                struct mCc_ast_declaration *declaration);

/**
 * Inserts a node into the symbol-table. More convenient if adding an
 * ast-function-def
 *
 * @param symbol_table
 * 		The symbol-table
 * @param function_def
 * 		The function-definition (ast-element)
 */
void mCc_symtab_insert_function_def_node(
    struct mCc_symbol_table *symbol_table,
    struct mCc_ast_function_def *function_def);

/**
 * Searches the node with the corresponding identifier within a symbol-table
 * (and its parents)
 *
 * @param symbol_table
 * 		The symbol-table where to search
 * @param identifier
 * 		The identifier (key)
 * @return
 * 		The corresponding node or NULL if identifier is not contained within the
 * symbol-table (and its parents)
 */
struct mCc_symbol_table_node *
mCc_symtab_lookup(struct mCc_symbol_table *symbol_table,
                  struct mCc_ast_identifier *identifier);

/**
 * Frees any allocated memory by the symbol-table (and its parents)
 *
 * @param symbol_table
 * 		The symbol-table
 */
void mCc_symtab_delete_symbol_table(struct mCc_symbol_table *symbol_table);

#ifdef __cplusplus
}
#endif

#endif
