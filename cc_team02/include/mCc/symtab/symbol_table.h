#ifndef MCC_SYMBOL_TABLE_H
#define MCC_SYMBOL_TABLE_H

#include "mCc/ast/basis/ast_declaration.h"
#include "mCc/ast/basis/ast_function.h"
#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/symtab/symtab_node.h"
#include "mCc/symtab/validator/validator.h"

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

//is passed via userdata (visitors)
struct mCc_symtab_and_validation_holder {
	struct mCc_symbol_table *symbol_table;
	struct mCc_validation_status_result *first_semantic_error;
};

/**
 * Creates and initializes a scope-holder struct
 *
 * @return
 * 		The scope-holder-struct or NULL in error-case
 */
struct mCc_ast_scope_holder *mCc_symtab_create_and_init_scope_holder();

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
struct mCc_symbol_table_node *mCc_symtab_new_parameter_declaration_node(
    struct mCc_ast_declaration *declaration);

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
