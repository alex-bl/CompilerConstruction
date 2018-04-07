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

enum mCc_sym_tab_identifier_type {
	MCC_SYM_TAB_IDENTIFIER_VARIABLE,
	MCC_SYM_TAB_IDENTIFIER_FUNCTION,
};

// TODO: necessary or just use string?
typedef map_t(struct mCc_ast_identifier *) mCc_symbol_table_map_t;

// TODO: maybe extend with other information?
struct mCc_symbol_table_node {
	enum mCc_ast_data_type data_type;
};

struct mCc_symbol_table {
	mCc_symbol_table_map_t *entries;
	mCc_symbol_table_map_t *parent;
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
mCc_sym_tab_new_declaration_node(struct mCc_ast_declaration *declaration);

/**
 * Creates a new symbol-table node out of a function def
 *
 * @param function_def
 * 		The ast-element of function_def
 * @return
 * 		A new symbol-table-node element
 */
struct mCc_symbol_table_node *
mCc_sym_tab_new_function_def_node(struct mCc_ast_function_def *function_def);

/**
 * Creates a new symbol-table
 *
 * @param parent
 * 		The parent-symbol-table or NULL if it is already the top-table
 * @return
 * 		A new symbol-table
 */
struct mCc_symbol_table *
mCc_sym_tab_new_symbol_table(struct mCc_symbol_table *parent);

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
void mCc_sym_tab_insert_node(struct mCc_symbol_table *symbol_table,
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
void mCc_sym_tab_insert_var_node(struct mCc_symbol_table *symbol_table,
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
void mCc_sym_tab_insert_function_def_node(
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
mCc_sym_tab_lookup(struct mCc_symbol_table *symbol_table,
                   struct mCc_ast_identifier *identifier);

/**
 * Frees any allocated memory by the symbol-table (and its parents)
 *
 * @param symbol_table
 * 		The symbol-table
 */
void mCc_sym_tab_delete_symbol_table(struct mCc_symbol_table *symbol_table);

#ifdef __cplusplus
}
#endif

#endif
