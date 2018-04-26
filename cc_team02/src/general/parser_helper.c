#include "mCc/general/parser_helper.h"

#include <assert.h>
#include <stdio.h>

static struct mCc_ast_function_def *
get_last_function_def(struct mCc_ast_program *buildins)
{
	assert(buildins);
	struct mCc_ast_function_def *first_function_def =
	    buildins->first_function_def;
	while (first_function_def->next_function_def) {
		first_function_def = first_function_def->next_function_def;
	}
	return first_function_def;
}

void mCc_parser_include_functions(struct mCc_ast_program *to_include,
                                  struct mCc_ast_program *prog)
{
	struct mCc_ast_function_def *last_function_def_buildins =
	    get_last_function_def(to_include);
	// prepend
	last_function_def_buildins->next_function_def = prog->first_function_def;
	prog->first_function_def = to_include->first_function_def;
}
