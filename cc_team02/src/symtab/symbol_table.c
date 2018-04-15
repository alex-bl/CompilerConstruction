#include "mCc/symtab/symbol_table.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "log.h"

static struct mCc_ast_identifier *
get_declaration_identifier(struct mCc_ast_declaration *decl)
{
	return decl->declaration_type == MCC_AST_DECLARATION_PRIMITIVE
	           ? decl->identifier
	           : decl->array_identifier;
}

struct mCc_symtab_parameter_ref *
mCc_symtab_new_parameter_ref(struct mCc_ast_identifier *identifier)
{
	assert(identifier);
	struct mCc_symtab_parameter_ref *param_ref = malloc(sizeof(*param_ref));
	if (!param_ref) {
		log_error("Malloc failed: Could not aquire heap-space for "
		          "'mCc_symbol_table_node'.");
		return NULL;
	}
	param_ref->identifier = identifier;
	param_ref->next_parameter = NULL;
	return param_ref;
}

// TODO: review
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
	node->next_parameter = NULL;

	return node;
}

struct mCc_symbol_table_node *mCc_symtab_new_parameter_declaration_node(
    struct mCc_ast_declaration *declaration)
{
	struct mCc_symbol_table_node *param_node =
	    mCc_symtab_new_declaration_node(declaration);

	param_node->entry_type = MCC_SYM_TAB_IDENTIFIER_FUNCTION_PARAMETER;
	param_node->data_type = declaration->data_type;
	param_node->next_parameter = NULL;

	return param_node;
}

/**
 * TODO: identifier vs array-identifier!
 *
 * @param function_def
 * @return
 */
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
	node->data_type = function_def->return_type;
	// has params?
	struct mCc_ast_declaration *parameter = function_def->first_parameter;

	if (parameter) {
		struct mCc_symtab_parameter_ref *first_param_node =
		    mCc_symtab_new_parameter_ref(get_declaration_identifier(parameter));

		first_param_node->next_parameter = NULL;
		struct mCc_symtab_parameter_ref *next_param_node = first_param_node;

		struct mCc_ast_declaration *next_param = parameter->next_declaration;

		while (next_param) {
			next_param_node->next_parameter = mCc_symtab_new_parameter_ref(
			    get_declaration_identifier(next_param));

			next_param_node = next_param_node->next_parameter;
			next_param = next_param->next_declaration;
		}
		// concatenation
		node->next_parameter = first_param_node;
	} else {
		node->next_parameter = NULL;
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

	mCc_symtab_insert_node(symbol_table,
	                       get_declaration_identifier(declaration), to_insert);
}

void mCc_symtab_insert_param_node(struct mCc_symbol_table *symbol_table,
                                  struct mCc_ast_declaration *declaration)
{
	assert(symbol_table);
	assert(declaration);

	struct mCc_symbol_table_node *to_insert =
	    mCc_symtab_new_declaration_node(declaration);
	to_insert->entry_type = MCC_SYM_TAB_IDENTIFIER_FUNCTION_PARAMETER;

	mCc_symtab_insert_node(symbol_table,
	                       get_declaration_identifier(declaration), to_insert);
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

	// insert parameters also
	struct mCc_ast_declaration *next_param = function_def->first_parameter;
	while (next_param) {
		mCc_symtab_insert_param_node(symbol_table, next_param);
		next_param = next_param->next_declaration;
	}
}

struct mCc_symbol_table_node *
mCc_symtab_lookup(struct mCc_symbol_table *symbol_table,
                  struct mCc_ast_identifier *identifier)
{
	assert(symbol_table);
	assert(identifier);

	// map_get gives a pointer to the result => dereference it once to get the
	// pointer to the symbol-table
	struct mCc_symbol_table_node **result_from_current_node =
	    map_get(&(symbol_table->table), identifier->identifier_name);

	// hit at current scope
	if (result_from_current_node) {
		return *result_from_current_node;
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
