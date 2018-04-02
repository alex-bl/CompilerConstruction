#include "mCc/ast/visit/ast_visit_program.h"

#include <assert.h>

#include "mCc/ast/visit/ast_visit_function.h"

void mCc_ast_visit_program(struct mCc_ast_program *program,
                           struct mCc_ast_visitor *visitor)
{
	assert(program);
	assert(visitor);

	visit_if_pre_order(program, visitor->program, visitor);

	mCc_ast_visit_function_def(program->first_function_def, visitor);

	visit_if_post_order(program, visitor->program, visitor);
}
