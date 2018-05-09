#ifndef MCC_SYMBOL_TABLE_H
#define MCC_SYMBOL_TABLE_H

#include "symtab_node.h"
#include "symtab_types.h"
#include "symtab_node_types.h"

#include <stdbool.h>

#include "map.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates and initializes a scope-holder struct
 *
 * @return
 * 		The scope-holder-struct or NULL in error-case
 */
struct mCc_ast_scope_holder *mCc_symtab_create_and_init_scope_holder();

/**
 * Creates a new symbol-table
 *
 * @param parent
 * 		The parent-symbol-table or NULL if it is already the top-table
 * @param scope_level
 * 		The scope level
 * @return
 * 		A new symbol-table
 */
struct mCc_symbol_table *
mCc_symtab_new_symbol_table(struct mCc_symbol_table *parent, int scope_level);

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
                                void *declaration);

/**
 * Inserts a node into the symbol-table. More convenient if adding an
 * ast-function-def
 *
 * @param symbol_table
 * 		The symbol-table
 * @param function_def
 * 		The function-definition (ast-element)
 */
void mCc_symtab_insert_function_def_node(struct mCc_symbol_table *symbol_table,
                                         void *function_def);

/**
 * Searches the node with the corresponding identifier within a symbol-table
 * (and its parents)
 *
 * @param symbol_table
 * 		The symbol-table where to search
 * @param identifier
 * 		The identifier (key)
 * 	@param current_scope_only
 * 		Only look at the current scope
 * @return
 * 		The corresponding node or NULL if identifier is not contained within the
 * symbol-table (and its parents)
 */
struct mCc_symbol_table_node *
mCc_symtab_lookup(struct mCc_symbol_table *symbol_table,
                  struct mCc_ast_identifier *identifier,
                  bool current_scope_only);

/**
 * Frees any allocated memory by the symbol-table (and its parents)
 *
 * @param symbol_table
 * 		The symbol-table
 */
void mCc_symtab_delete_symbol_table(struct mCc_symbol_table *symbol_table);

/**
 * Creates a new symbol-table and sets the actual symbol table to the newly
 * created (used by symtab-hanlders).
 *
 * @param data
 * 		The userdata passed within the visitor-callbacks
 */
void mCc_symtab_enter_scope(void *data);

/**
 * Deletes the actual symbol table and sets its parent as actual (used by
 * symtab-hanlders).
 *
 * @param data
 * 		The userdata passed within the visitor-callbacks
 */
void mCc_symtab_leave_scope(void *data);

#ifdef __cplusplus
}
#endif

#endif
