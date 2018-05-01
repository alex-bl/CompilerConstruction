#include "mCc/ast/basis/ast_assignment.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct mCc_ast_assignment *mCc_ast_new_primitive_assignment(
    struct mCc_ast_identifier *identifier,
    struct mCc_ast_expression *assigned_expresion_value)
{
	struct mCc_ast_assignment *assignment = malloc(sizeof(*assignment));
	if (!assignment) {
		return NULL;
	}

	assignment->identifier = identifier;
	assignment->assignment_type = MCC_AST_ASSIGNMENT_PRIMITIVE;
	assignment->assigned_expression = assigned_expresion_value;
	return assignment;
}

struct mCc_ast_assignment *
mCc_ast_new_array_assignment(struct mCc_ast_identifier *identifier,
                             struct mCc_ast_expression *index,
                             struct mCc_ast_expression *value)
{
	struct mCc_ast_assignment *assignment = malloc(sizeof(*assignment));
	if (!assignment) {
		return NULL;
	}

	assignment->identifier = identifier;
	assignment->assignment_type = MCC_AST_ASSIGNMENT_ARRAY;
	assignment->array_index_expression = index;
	assignment->array_assigned_expression = value;
	return assignment;
}

void mCc_ast_delete_assignment(struct mCc_ast_assignment *assignment)
{
	assert(assignment);

	mCc_ast_delete_identifier(assignment->identifier);
	if (assignment->assignment_type == MCC_AST_ASSIGNMENT_PRIMITIVE) {
		mCc_ast_delete_expression(assignment->assigned_expression);
	} else if (assignment->assignment_type == MCC_AST_ASSIGNMENT_ARRAY) {
		mCc_ast_delete_expression(assignment->array_index_expression);
		mCc_ast_delete_expression(assignment->array_assigned_expression);
	}
	free(assignment);
}

struct mCc_ast_expression *
mCc_ast_get_expression(struct mCc_ast_assignment *assignment){
	assert(assignment);
	if(assignment->assignment_type==MCC_AST_ASSIGNMENT_PRIMITIVE){
		return assignment->assigned_expression;
	}
	return assignment->array_assigned_expression;
}
