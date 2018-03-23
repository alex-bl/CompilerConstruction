#include <assert.h>
#include <stdlib.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_program.h"
#include "mCc/ast/visit/ast_visit_program.h"

static void mCc_print_dot_program(struct mCc_ast_program *program, void *data)
{
	assert(program);
	assert(data);

	FILE *out = data;
	print_dot_node(out, program, "program");
	print_dot_edge(out, program, program->first_function_def, "first function");
}

static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,
		.userdata = out,

		.program = mCc_print_dot_program
	};
}


void mCc_ast_print_dot_program(FILE *out, struct mCc_ast_program *program)
{
	assert(out);
	assert(program);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_program(program, &visitor);

	print_dot_end(out);
}
