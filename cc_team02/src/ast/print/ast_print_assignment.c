#include <assert.h>
#include <stdlib.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_assignment.h"
#include "mCc/ast/visit/ast_visit_assignment.h"

void mCc_print_dot_assignment_primitive(struct mCc_ast_assignment *assignment,
                                        void *data)
{
	assert(assignment);
	assert(data);

	FILE *out = data;
	print_dot_node(out, assignment, "assignment");
	print_dot_edge(out, assignment, assignment->identifier, "identifier");
	print_dot_edge(out, assignment, assignment->assigned_expression, "value");
}

void mCc_print_dot_assignment_array(struct mCc_ast_assignment *assignment,
                                    void *data)
{

	assert(assignment);
	assert(data);

	FILE *out = data;
	print_dot_node(out, assignment, "assignment arr");
	print_dot_edge(out, assignment, assignment->identifier, "identifier");
	print_dot_edge(out, assignment, assignment->array_index_expression,
	               "[index]");
	print_dot_edge(out, assignment, assignment->array_assigned_expression,
	               "value");
}
