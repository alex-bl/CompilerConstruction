#include <assert.h>
#include <stdlib.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_assignment.h"
#include "mCc/ast/visit/ast_visit_assignment.h"

void mCc_ast_print_dot_assignment(FILE *out,
                                  struct mCc_ast_assignment *assignment)
{
	assert(out);
	assert(assignment);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_assignment(assignment, &visitor);

	print_dot_end(out);
}

static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){
		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,
		.userdata = out,

		.assignment_primitive = mCc_print_dot_assignment_primitive,
		.assignment_array = mCc_print_dot_assignment_array
	};
}

static void
mCc_print_dot_assignment_primitive(struct mCc_ast_assignment *assignment,
                                   void *data)
{
	assert(assignment);
	assert(data);

	FILE *out = data;
	print_dot_node(out, assignment, "assignment");
	print_dot_edge(out, assignment, assignment->identifier,
	               "assignment: identifier");
	print_dot_edge(out, assignment, assignment->assigned_expression,
	               "assignment: expr");
}

static void
mCc_print_dot_assignment_array(struct mCc_ast_assignment *assignment,
                               void *data)
{

	assert(assignment);
	assert(data);

	FILE *out = data;
	print_dot_node(out, assignment, "assignment arr");
	print_dot_edge(out, assignment, assignment->identifier,
	               "assignment: identifier");
	print_dot_edge(out, assignment, assignment->array_assigned_expression,
	               "assignment: expr");
	print_dot_edge(out, assignment, assignment->array_index_expression,
	               "assignment: arr-expr");
}
