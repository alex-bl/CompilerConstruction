#include "tac_assignment.h"

#include <assert.h>

#include "basic_tac.h"
#include "tac_expression.h"

// x:= y
struct mCc_tac_element *
mCc_tac_assignment_primitive(struct mCc_ast_assignment *assignment,
                             struct mCc_tac_element *previous_tac)
{
	assert(assignment);
	assert(assignment->assigned_expression);
	assert(previous_tac);

	struct mCc_tac_element *tac_assigned_expression =
	    helper_get_tac_of_expression(assignment->assigned_expression,
	                                 previous_tac);

	// puts scope level behind the variable name and return tac_identifier
	struct mCc_tac_identifier *name_identifier =
	    mCc_helper_concat_name_and_scope(
	        assignment->identifier->identifier_name,
	        assignment->identifier->symtab_info->scope_level);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_COPY,
	    mCc_tac_create_from_tac_identifier(tac_assigned_expression->tac_result),
	    NULL, name_identifier, MCC_TAC_TYPE_NO_TYPE, 0);

	mCc_tac_connect_tac_entry(tac_assigned_expression, tac);

	return tac;
}

// y[i]:=x
struct mCc_tac_element *
mCc_tac_assignment_array(struct mCc_ast_assignment *assignment,
                         struct mCc_tac_element *previous_tac)
{
	assert(assignment);
	assert(assignment->array_index_expression);
	assert(assignment->array_assigned_expression);
	assert(previous_tac);

	// assignment->array_assigned_expression
	// assignment->array_index_expression
	// assignment->identifier->identifier_name

	struct mCc_tac_element *tac_assigned_expression =
	    helper_get_tac_of_expression(assignment->array_assigned_expression,
	                                 previous_tac);

	struct mCc_tac_element *tac_index_expression = helper_get_tac_of_expression(
	    assignment->array_index_expression, tac_assigned_expression);

	// puts scope level behind the variable name and return tac_identifier
	struct mCc_tac_identifier *name_identifier =
	    mCc_helper_concat_name_and_scope(
	        assignment->identifier->identifier_name,
	        assignment->identifier->symtab_info->scope_level);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_INDEXING,
	    tac_new_identifier(tac_assigned_expression->tac_result->name),
	    tac_new_identifier(tac_index_expression->tac_result->name),
	    name_identifier, MCC_TAC_TYPE_NO_TYPE, 0);

	mCc_tac_connect_tac_entry(tac_index_expression, tac);

	return tac;
}
