#include "mCc/ast/print/ast_print_program.h"
#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/visit/ast_visit_program.h"
#include <assert.h>
#include <stdlib.h>

void mCc_print_dot_program(struct mCc_ast_program *program, void *data)
{
	assert(program);
	assert(data);

	FILE *out = data;
	print_dot_node(out, program, "program");
	print_dot_edge(out, program, program->first_function_def, "first function");
}
