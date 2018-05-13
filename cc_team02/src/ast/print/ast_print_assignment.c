#include "ast_print_assignment.h"

#include <assert.h>

#include "ast_basic_printing.h"

void mCc_print_dot_assignment_primitive(struct mCc_ast_assignment *assignment,
                                        void *data)
{
	assert(assignment);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, assignment, "assignment");
	mCc_ast_print_dot_edge(out, assignment, assignment->identifier, "identifier");
	mCc_ast_print_dot_edge(out, assignment, assignment->assigned_expression, "value");
}

void mCc_print_dot_assignment_array(struct mCc_ast_assignment *assignment,
                                    void *data)
{

	assert(assignment);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, assignment, "assignment arr");
	mCc_ast_print_dot_edge(out, assignment, assignment->identifier, "identifier");
	mCc_ast_print_dot_edge(out, assignment, assignment->array_index_expression,
	               "[index]");
	mCc_ast_print_dot_edge(out, assignment, assignment->array_assigned_expression,
	               "value");
}
