#include <assert.h>

#include "mCc/ast/visit/ast_visit_assignment.h"
#include "mCc/ast/visit/ast_visit_expression.h"
#include "mCc/ast/visit/ast_visit_identifier.h"

void mCc_ast_visit_assignment(struct mCc_ast_assignment *assignment,
                              struct mCc_ast_visitor *visitor)
{
	assert(assignment);
	assert(visitor);

	visit_if_pre_order(assignment, visitor->assignment, visitor);

	switch (assignment->assignment_type) {
	case MCC_AST_ASSIGNMENT_PRIMITIVE:
		visit_if_pre_order(assignment, visitor->assignment_primitive, visitor);

		mCc_ast_visit_identifier(assignment->identifier, visitor);
		mCc_ast_visit_expression(assignment->assigned_expression, visitor);

		visit_if_post_order(assignment, visitor->assignment_primitive, visitor);
		break;
	case MCC_AST_ASSIGNMENT_ARRAY:
		visit_if_pre_order(assignment, visitor->assignment_array, visitor);

		mCc_ast_visit_identifier(assignment->identifier, visitor);
		mCc_ast_visit_expression(assignment->array_index_expression, visitor);
		mCc_ast_visit_expression(assignment->array_assigned_expression,
		                         visitor);

		visit_if_post_order(assignment, visitor->assignment_array, visitor);
		break;
	}

	visit_if_post_order(assignment, visitor->assignment, visitor);
}
