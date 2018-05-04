#include "mCc/ast/visit/ast_visit_literal.h"

#include <assert.h>

void mCc_ast_visit_literal(struct mCc_ast_literal *literal,
                           struct mCc_ast_visitor *visitor)
{
	assert(literal);
	assert(visitor);

	visit_if_pre_order(literal, visitor->literal, visitor);
	visit_if_both_order(literal, visitor->literal, visitor);

	switch (literal->type) {
	case MCC_AST_DATA_TYPE_INT:
		visit(literal, visitor->literal_int, visitor);
		break;

	case MCC_AST_DATA_TYPE_FLOAT:
		visit(literal, visitor->literal_float, visitor);
		break;

	case MCC_AST_DATA_TYPE_BOOL:
		visit(literal, visitor->literal_bool, visitor);
		break;

	case MCC_AST_DATA_TYPE_STRING:
		visit(literal, visitor->literal_string, visitor);
		break;
	case MCC_AST_DATA_TYPE_VOID:
		// a literal having a void-type should never happen
	case MCC_AST_DATA_TYPE_INCONSISTENT:
	case MCC_AST_DATA_TYPE_UNKNOWN:
	case MCC_AST_DATA_TYPE_INCOMPATIBLE:
		assert(false);
		break;
	}

	visit_if_post_order(literal, visitor->literal, visitor);
	visit_if_pre_order(literal, visitor->literal_post_order, visitor);

}
