#include "mCc/ast/tac/ast_tac_assignment.h"

#include <assert.h>

#include "mCc/ast/tac/ast_basic_tac.h"

void mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                                        void *data)
{
	assert(assignment);
	assert(data);

	FILE *out = data;
	fprintf(out, "assignment: %p - identifier: %p - expression: %p", assignment, assignment->identifier, assignment->assigned_expression);
}

void mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                                    void *data)
{
	assert(assignment);
	assert(data);

}
