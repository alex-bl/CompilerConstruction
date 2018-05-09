#include "mCc/tac/basis/tac_assignment.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                                        void *data)
{
	assert(assignment);
	assert(data);

	//tac_elmenet(assignment->assigned_expression, assignment->identifier, '');

	FILE *out = data;
	fprintf(out, "assignment: %p - identifier: %p - expression: %p", assignment, assignment->identifier, assignment->assigned_expression);
}

void mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                                    void *data)
{
	assert(assignment);
	assert(data);

	//tac_elmenet(assignment->assigned_expression, assignment->identifier, '');
}

