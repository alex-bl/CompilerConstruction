#include "mCc/ast/visit/ast_visit_identifier.h"

#include <assert.h>

void mCc_ast_visit_identifier(struct mCc_ast_identifier *identifier,
                              struct mCc_ast_visitor *visitor)
{
	assert(identifier);
	assert(visitor);

	// is always executed, no matter if preorder or postorder
	visit(identifier, visitor->identifier, visitor);
}
