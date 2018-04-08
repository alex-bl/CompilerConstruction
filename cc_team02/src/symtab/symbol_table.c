#include "mCc/symtab/symbol_table.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct mCc_symbol_table_node *
mCc_symtab_new_declaration_node(struct mCc_ast_declaration *declaration)
{
	/*TODO*/
	return NULL;
}

struct mCc_symbol_table_node *
mCc_symtab_new_function_def_node(struct mCc_ast_function_def *function_def)
{
	/*TODO*/
	return NULL;
}

struct mCc_symbol_table *
mCc_symtab_new_symbol_table(struct mCc_symbol_table *parent)
{
	/*TODO*/
	return NULL;
}

void mCc_symtab_insert_node(struct mCc_symbol_table *symbol_table,
                            struct mCc_ast_identifier *key,
                            struct mCc_symbol_table_node *value)
{
	/*TODO*/
}

void mCc_symtab_insert_var_node(struct mCc_symbol_table *symbol_table,
                                struct mCc_ast_declaration *declaration)
{
	/*TODO*/
}

void mCc_symtab_insert_function_def_node(
    struct mCc_symbol_table *symbol_table,
    struct mCc_ast_function_def *function_def)
{
	/*TODO*/
}

struct mCc_symbol_table_node *
mCc_symtab_lookup(struct mCc_symbol_table *symbol_table,
                  struct mCc_ast_identifier *identifier)
{
	/*TODO*/
	return NULL;
}

void mCc_symtab_delete_symbol_table(struct mCc_symbol_table *symbol_table)
{
	/*TODO*/
}
