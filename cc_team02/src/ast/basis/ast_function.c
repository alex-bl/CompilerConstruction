#include <stddef.h>

#include "mCc/ast/basis/ast_function.h"

/*---------------------------------------------------------------- function
 * definition*/
struct mCc_ast_function_def *mCc_ast_new_non_parameterized_function_def(
    struct mCc_ast_identifier *identifier,
    enum mCc_ast_function_return_type return_type,
    struct mCc_ast_statement *stmts)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_function_def *mCc_ast_new_parameterized_function_def(
    struct mCc_ast_identifier *identifier,
    enum mCc_ast_function_return_type return_type,
    struct mCc_ast_declaration *params, struct mCc_ast_statement *stmts)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_function_def(struct mCc_ast_function_def *function_def)
{
	/*TODO*/
}

/*---------------------------------------------------------------------function
 * call*/
struct mCc_ast_function_call *
mCc_ast_new_parameterized_function_call(struct mCc_ast_identifier *identifier,
                                        struct mCc_ast_expression *args)
{
	/* TODO */
	return NULL;
}

struct mCc_ast_function_call *mCc_ast_new_non_parameterized_function_call(
    struct mCc_ast_identifier *identifier)
{
	/* TODO */
	return NULL;
}

void mCc_ast_delete_function_call(struct mCc_ast_function_call *function_call)
{
	/* TODO */
}
