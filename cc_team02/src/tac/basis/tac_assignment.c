#include "tac_assignment.h"
#include "tac_expression.h"

#include <assert.h>

#include "basic_tac.h"

// x:= y
struct mCc_tac_element *
mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                             struct mCc_tac_element *previous_tac)
{
	assert(assignment);
	assert(previous_tac);

	struct mCc_tac_identifier *argument1 =
	    mCc_tac_expression_literal(assignment->assigned_expression,
	                               previous_tac)
	        ->tac_result;

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_COPY, argument1, NULL,
	    tac_new_identifier(assignment->identifier->identifier_name));
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
	return tac;
}

struct mCc_tac_element *
mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                         struct mCc_tac_element *previous_tac)
{
	assert(assignment);
	assert(previous_tac);

	struct mCc_tac_identifier *argument1 =
	    mCc_tac_expression_identifier_array(assignment->array_index_expression,
	                                        previous_tac)
	        ->tac_result;

	struct mCc_tac_identifier *argument2 =
	    mCc_tac_expression_identifier_array(
	        assignment->array_assigned_expression, previous_tac)
	        ->tac_result;

	// y[i]:=x
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_INDEXING, argument1, argument2,
	    tac_new_identifier(assignment->identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
