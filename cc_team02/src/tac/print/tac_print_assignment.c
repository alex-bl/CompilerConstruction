#include "mCc/tac/basis/tac_assignment.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                                        void *data)
{
	assert(assignment);
	assert(data);

	//struct mCc_tac_element elment=tac_new_element(MCC_TAC_OPERATION_EMPTY, tac_new_identifier(assignment->assigned_expression), NULL, tac_new_identifier(assignment->identifier));

	//tac_print(elment, *data);

	//FILE *out = data;
	//fprintf(out, "operation: empty - argument1: %p - argument2: %p - result: %p\n", assignment, assignment->identifier, assignment->assigned_expression);
}

void mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                                    void *data)
{
	assert(assignment);
	assert(data);

	//array_index_expression->array_identifier
	//array_index_expression->array_index_expression
	//array_assigned_expression

	//tac_new_element(MCC_TAC_OPARATION_INDEXING, tac_new_identifier(assignment->array_index_expression->array_index_expression),
			//tac_new_identifier(assignment->array_assigned_expression->identifier->identifier_name), tac_new_identifier(assignment->identifier));

	//tac_elmenet(assignment->assigned_expression, assignment->identifier, '');
}

