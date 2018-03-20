#include <stddef.h>

#include "mCc/ast/basis/ast_function.h"

/*---------------------------------------------------------------- function
 * definition*/
struct mCc_ast_function_def *
mCc_ast_new_void_function_def(const char *identifier)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_function_def *mCc_ast_new_int_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt)
{
	/* TODO */
	return NULL;
}
struct mCc_ast_function_def *mCc_ast_new_float_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_function_def *mCc_ast_new_bool_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_function_def *mCc_ast_new_string_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_void_function_def(struct mCc_ast_function_def *function_def)
{
	/* TODO */
}

void mCc_ast_delete_int_function_def(struct mCc_ast_function_def *function_def)
{
	/* TODO */
}

void mCc_ast_delete_float_function_def(
    struct mCc_ast_function_def *function_def)
{
	/* TODO */
}

void mCc_ast_delete_bool_function_def(struct mCc_ast_function_def *function_def)
{
	/* TODO */
}

void mCc_ast_delete_string_function_def(
    struct mCc_ast_function_def *function_def)
{
	/* TODO */
}

/*---------------------------------------------------------------------function
 * call*/
struct mCc_ast_function_call *
mCc_ast_new_int_function_call(const char *identifier,
                              struct mCc_ast_expression *args, long nr_args)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_function_call(struct mCc_ast_function_call *function_call)
{
	/* TODO */
}
