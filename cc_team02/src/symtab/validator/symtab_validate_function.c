#include "mCc/symtab/validator/symtab_validate_function.h"

#include <assert.h>
#include <stddef.h>

struct mCc_validation_status_result *
mCc_symtab_validate_main_presence(struct mCc_symbol_table *symbol_table)
{
	/*TODO*/
	return NULL;
}

struct mCc_validation_status_result *mCc_symtab_validate_unknown_function(
    struct mCc_ast_function_call *function_call,
    struct mCc_symbol_table *symbol_table)
{
	/*TODO*/
	return NULL;
}

struct mCc_validation_status_result *mCc_symtab_validate_duplicate_function(
    struct mCc_ast_function_call *function_call,
    struct mCc_symbol_table *symbol_table)
{
	/*TODO*/
	return NULL;
}

struct mCc_validation_status_result *mCc_symtab_validate_function_return_type(
    struct mCc_ast_function_def *function_def,
    struct mCc_symbol_table *symbol_table)
{
	/*TODO*/
	return NULL;
}
