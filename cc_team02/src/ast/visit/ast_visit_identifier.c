#include "mCc/ast/visit/ast_visit_identifier.h"
#include <assert.h>

void mCc_ast_visit_identifier(struct mCc_ast_identifier *identifier,
                              struct mCc_ast_visitor *visitor)
{
	assert(identifier);
	assert(visitor);

	visit_if_pre_order(identifier, visitor->identifier, visitor);
	// TODO: correct?
	visit(identifier, visitor->identifier, visitor);
	visit_if_post_order(identifier, visitor->identifier, visitor);
}
