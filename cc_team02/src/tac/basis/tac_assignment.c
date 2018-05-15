#include "mCc/tac/basis/tac_assignment.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

// x:= y
void mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                                  struct mCc_tac_element *previous_tac)
{
	assert(assignment);
	assert(previous_tac);

	//TODO change s_value
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_COPY,
	    tac_new_identifier(assignment->assigned_expression->literal->s_value),
	    NULL, tac_new_identifier(assignment->identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);
	/*
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_LABLE,
	    tac_new_identifier(assignment->assigned_expression->identifier->identifier_name),
	    NULL, tac_new_identifier(assignment->identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);
	struct mCc_tac_element *tac2 = tac_new_element(
	    MCC_TAC_OPARATION_COPY,
	    tac_new_identifier(assignment->assigned_expression->literal->s_value),
	    NULL, tac_new_identifier(assignment->identifier->identifier_name));
	mCc_tac_connect_tac_entry(tac, tac2);
	 */
}

void mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                              struct mCc_tac_element *previous_tac)
{
	assert(assignment);
	assert(previous_tac);

	// y[i]:=x
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_INDEXING,
	    tac_new_identifier(assignment->array_index_expression->array_identifier
	                           ->identifier_name),
	    tac_new_identifier(
	        assignment->array_assigned_expression->identifier->identifier_name),
	    tac_new_identifier(assignment->identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);
}
