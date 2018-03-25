#include "mCc/ast/basis/ast_program.h"
#include <stddef.h>
#include <stdlib.h>

struct mCc_ast_program *
mCc_ast_new_program(struct mCc_ast_function_def *function_defs)
{
	struct mCc_ast_program *program = malloc(sizeof(*program));
	if (!program) {
		return NULL;
	}

	program->first_function_def = function_defs;
	return program;
}

void mCc_ast_delete_program(struct mCc_ast_program *program)
{
	mCc_ast_delete_function_def(program->first_function_def);
	free(program);
}
