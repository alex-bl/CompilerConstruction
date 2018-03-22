#include <stdlib.h>
#include <assert.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_function.h"
#include "mCc/ast/visit/ast_visit_function.h"

void mCc_ast_print_dot_function_def(FILE *out,
                                    struct mCc_ast_function_def *function_def)
{
	/*TODO*/
}

void mCc_ast_print_dot_function_call(
    FILE *out, struct mCc_ast_function_call *function_call)
{
	/*TODO*/
}

static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

	};
}
