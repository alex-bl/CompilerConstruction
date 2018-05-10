#include "mCc/tac/basis/tac_assignment.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                                  void *data)
{
	assert(assignment);
	assert(data);

	// FILE *out = data;
	// fprintf(out, "operation: empty - argument1: %p - argument2: %p - result:
	// %p\n", assignment, assignment->identifier,
	// assignment->assigned_expression);
}

void mCc_tac_assignment_array(struct mCc_ast_assignment *assignment, void *data)
{
	assert(assignment);
	assert(data);
}
