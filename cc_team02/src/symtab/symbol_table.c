#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/symtab_node.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "log.h"

struct mCc_symbol_table *
mCc_symtab_new_symbol_table(struct mCc_symbol_table *parent, int scope_level)
{
	struct mCc_symbol_table *symbol_table = malloc(sizeof(*symbol_table));
	if (!symbol_table) {
		log_error("Malloc failed: Could not aquire heap-space for "
		          "'mCc_symbol_table'.");
		return NULL;
	}

	symbol_table->parent = parent;
	symbol_table->scope_level = scope_level;

	// init hash-map
	map_init(&(symbol_table->table));

	return symbol_table;
}

void mCc_symtab_insert_node(struct mCc_symbol_table *symbol_table,
                            struct mCc_ast_identifier *key,
                            struct mCc_symbol_table_node *value)
{
	assert(symbol_table);
	assert(key);
	assert(value);

	map_set(&(symbol_table->table), key->identifier_name, value);
	log_debug("Inserted identifier '%s' at symbol table with scope %d",
	          key->identifier_name, symbol_table->scope_level);
}

void mCc_symtab_insert_var_node(struct mCc_symbol_table *symbol_table,
                                void *data)
{
	assert(symbol_table);
	assert(data);

	struct mCc_ast_declaration *declaration =
	    (struct mCc_ast_declaration *)data;

	struct mCc_symbol_table_node *to_insert =
	    mCc_symtab_new_declaration_node(declaration);

	struct mCc_ast_identifier *identifier =
	    mCc_ast_get_declaration_identifier(declaration);
	log_debug("Variable: %s", identifier->identifier_name);

	mCc_symtab_insert_node(symbol_table, identifier, to_insert);
}

/*
 * TODO:
 * - var declaration and array declaration
 */
void mCc_symtab_insert_function_def_node(struct mCc_symbol_table *symbol_table,
                                         void *data)
{
	assert(symbol_table);
	assert(data);

	struct mCc_ast_function_def *function_def =
	    (struct mCc_ast_function_def *)data;

	struct mCc_symbol_table_node *to_insert =
	    mCc_symtab_new_function_def_node(function_def);
	mCc_symtab_insert_node(symbol_table, function_def->identifier, to_insert);
}

struct mCc_symbol_table_node *
mCc_symtab_lookup(struct mCc_symbol_table *symbol_table,
                  struct mCc_ast_identifier *identifier,
                  bool current_scope_only)
{
	assert(symbol_table);
	assert(identifier);

	// map_get gives a pointer to the result => dereference it once to get the
	// pointer to the symbol-table
	struct mCc_symbol_table_node **result_from_current_node =
	    map_get(&(symbol_table->table), identifier->identifier_name);

	// hit at current scope
	if (result_from_current_node) {
		log_debug("Identifier '%s' found at scope %d",
		          identifier->identifier_name, symbol_table->scope_level);
		return *result_from_current_node;
		// not found at current scope => search at parent-scope
	} else if (symbol_table->parent && !current_scope_only) {
		log_debug("Identifier '%s' not found at scope %d. Go to parent",
		          identifier->identifier_name, symbol_table->scope_level);
		return mCc_symtab_lookup(symbol_table->parent, identifier,
		                         current_scope_only);
	}

	// no hit
	return NULL;
}

void mCc_symtab_delete_symbol_table(struct mCc_symbol_table *symbol_table)
{
	assert(symbol_table);

	/*
	 * iterate over all nodes and free them maunally because map_deinit(..) just
	 * frees its internal structure
	 */
	mCc_symbol_table_map_t map = symbol_table->table;
	const char *key;
	map_iter_t iter = map_iter(&map);

	while ((key = map_next(&map, &iter))) {
		struct mCc_symbol_table_node **actual_node_result = map_get(&map, key);
		struct mCc_symbol_table_node *actual_node = *actual_node_result;
		// manual free because map_deinit does not touch the values
		mCc_symtab_delete_symtab_node(actual_node);
	}

	/*
	 * just free "current" symbol-table
	 * do not touch parent!
	 */
	map_deinit(&map);
	free(symbol_table);
}
