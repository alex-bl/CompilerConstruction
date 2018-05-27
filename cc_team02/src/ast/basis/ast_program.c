#include "ast_program.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "validator.h"

struct mCc_ast_program *
mCc_ast_new_program(struct mCc_ast_function_def *function_defs)
{
	struct mCc_ast_program *program = malloc(sizeof(*program));
	if (!program) {
		return NULL;
	}

	program->first_function_def = function_defs;
	program->is_library = false;
	program->semantic_error = NULL;

	return program;
}

void mCc_ast_delete_program(struct mCc_ast_program *program)
{
	assert(program);

	mCc_validator_delete_validation_result(program->semantic_error);

	/* Delete AST only if it is the "real" program*/
	if (program->first_function_def && !program->is_library) {
		mCc_ast_delete_function_def(program->first_function_def);
	}
	free(program);
}
