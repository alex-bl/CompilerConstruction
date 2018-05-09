#include "mCc/tac/basis/tac_assignment.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                                        void *data)
{
	assert(assignment);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, tac_new_identifier(assignment->assigned_expression), NULL, tac_new_identifier(assignment->identifier));

	//FILE *out = data;
	//fprintf(out, "assignment: %p - identifier: %p - expression: %p", assignment, assignment->identifier, assignment->assigned_expression);
}

void mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                                    void *data)
{
	assert(assignment);
	assert(data);

	//array_index_expression->array_identifier
	//array_index_expression->array_index_expression
	//array_assigned_expression
	tac_new_element(MCC_TAC_OPARATION_INDEXING, tac_new_identifier(assignment->array_index_expression->array_index_expression),
			tac_new_identifier(assignment->array_assigned_expression->identifier->identifier_name), tac_new_identifier(assignment->identifier));

	//tac_elmenet(assignment->assigned_expression, assignment->identifier, '');
}

