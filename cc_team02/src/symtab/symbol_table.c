#include "mCc/symtab/symbol_table.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "log.h"

struct mCc_symbol_table_node *
mCc_symtab_new_declaration_node(struct mCc_ast_declaration *declaration)
{
	assert(declaration);

	struct mCc_symbol_table_node *node = malloc(sizeof(*node));
	if (!node) {
		log_error("Malloc failed: Could not aquire heap-space for "
		          "'mCc_symbol_table_node'.");
		return NULL;
	}

	node->entry_type = MCC_SYM_TAB_IDENTIFIER_VARIABLE;
	node->data_type = declaration->data_type;

	return node;
}

struct mCc_symbol_table_node *mCc_symtab_new_parameter_declaration_node(
    struct mCc_ast_declaration *declaration)
{
	struct mCc_symbol_table_node *param_node =
	    mCc_symtab_new_declaration_node(declaration);

	param_node->entry_type = MCC_SYM_TAB_IDENTIFIER_FUNCTION_PARAMETER;
	param_node->next_parameter = NULL;

	return param_node;
}

struct mCc_symbol_table_node *
mCc_symtab_new_function_def_node(struct mCc_ast_function_def *function_def)
{
	assert(function_def);

	struct mCc_symbol_table_node *node = malloc(sizeof(*node));
	if (!node) {
		log_error("Malloc failed: Could not aquire heap-space for "
		          "'mCc_symbol_table_node'.");
		return NULL;
	}

	node->entry_type = MCC_SYM_TAB_IDENTIFIER_FUNCTION;
	node->return_type = function_def->return_type;
	// has params?
	struct mCc_ast_declaration *parameter = function_def->first_parameter;

	if (parameter) {
		struct mCc_symbol_table_node *first_param_node =
		    mCc_symtab_new_parameter_declaration_node(parameter);

		first_param_node->next_parameter = NULL;

		struct mCc_ast_declaration *next_param = parameter->next_declaration;
		struct mCc_symbol_table_node *next_param_node = first_param_node;

		while (next_param) {
			next_param_node->next_parameter =
			    mCc_symtab_new_parameter_declaration_node(next_param);
			next_param_node = next_param_node->next_parameter;

			next_param = next_param->next_declaration;
		}
		// concatenate all
		first_param_node->next_parameter = next_param_node;
	}

	return node;
}

struct mCc_symbol_table *
mCc_symtab_new_symbol_table(struct mCc_symbol_table *parent)
{
	struct mCc_symbol_table *symbol_table = malloc(sizeof(*symbol_table));
	if (!symbol_table) {
		log_error("Malloc failed: Could not aquire heap-space for "
		          "'mCc_symbol_table'.");
		return NULL;
	}

	symbol_table->parent = parent;
	// new table means new scope => increment level
	if (parent) {
		symbol_table->scope_level = parent->scope_level + 1;
	} else {
		//"global" symtab
		symbol_table->scope_level = 0;
	}
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
}

void mCc_symtab_insert_var_node(struct mCc_symbol_table *symbol_table,
                                struct mCc_ast_declaration *declaration)
{
	assert(symbol_table);
	assert(declaration);

	struct mCc_symbol_table_node *to_insert =
	    mCc_symtab_new_declaration_node(declaration);
	struct mCc_ast_identifier *identifier;

	if (declaration->declaration_type == MCC_AST_DECLARATION_PRIMITIVE) {
		identifier = declaration->identifier;
	} else {
		identifier = declaration->array_identifier;
	}

	mCc_symtab_insert_node(symbol_table, identifier, to_insert);
}

void mCc_symtab_insert_function_def_node(
    struct mCc_symbol_table *symbol_table,
    struct mCc_ast_function_def *function_def)
{
	assert(symbol_table);
	assert(function_def);

	struct mCc_symbol_table_node *to_insert =
	    mCc_symtab_new_function_def_node(function_def);
	mCc_symtab_insert_node(symbol_table, function_def->identifier, to_insert);
}

struct mCc_symbol_table_node *
mCc_symtab_lookup(struct mCc_symbol_table *symbol_table,
                  struct mCc_ast_identifier *identifier)
{
	assert(symbol_table);
	assert(identifier);

	// map_get gives a pointer to the result => dereference it once to get the
	// pointer to the symbol-table
	struct mCc_symbol_table_node *result_from_current_node =
	    *(map_get(&(symbol_table->table), identifier->identifier_name));

	// hit at current scope
	if (result_from_current_node) {
		return result_from_current_node;
		// not found at current scope => search at parent-scope
	} else if (symbol_table->parent) {
		return mCc_symtab_lookup(symbol_table->parent, identifier);
	}

	// no hit
	return NULL;
}

void mCc_symtab_delete_symbol_table(struct mCc_symbol_table *symbol_table)
{
	assert(symbol_table);
	/*
	 * TODO: free all nodes
	 * Is it already done by map_deinit? => check this also
	 *
	 */

	/*
	 * just free "current" symbol-table
	 * do not touch parent!
	 */
	map_deinit(&(symbol_table->table));
}
