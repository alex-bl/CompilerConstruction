#include "mCc/ast/visit/ast_visit_function.h"

#include <assert.h>

#include "mCc/ast/visit/ast_visit_declaration.h"
#include "mCc/ast/visit/ast_visit_expression.h"
#include "mCc/ast/visit/ast_visit_identifier.h"
#include "mCc/ast/visit/ast_visit_statement.h"

void mCc_ast_visit_optional_function_def(
    struct mCc_ast_function_def *function_def, struct mCc_ast_visitor *visitor)
{
	if (function_def) {
		mCc_ast_visit_function_def(function_def, visitor);
	}
}

void mCc_ast_visit_function_def(struct mCc_ast_function_def *function_def,
                                struct mCc_ast_visitor *visitor)
{
	assert(function_def);
	assert(visitor);

	// preorder
	visit_if_pre_order(function_def, visitor->function_def, visitor);

	//=========================needed for building the symbol-table
	visit_scope(visitor->function_def_enter_scope, visitor);
	//=============================================================

	mCc_ast_visit_identifier(function_def->identifier, visitor);

	mCc_ast_visit_optional_declaration(function_def->first_parameter, visitor);
	// can be empty
	mCc_ast_visit_optional_statement(function_def->first_statement, visitor);

	//=========================needed for building the symbol-table
	visit_scope(visitor->function_def_leave_scope, visitor);
	//=============================================================

	mCc_ast_visit_optional_function_def(function_def->next_function_def,
	                                    visitor);

	// postorder: here or also before visiting next function?
	visit_if_post_order(function_def, visitor->function_def, visitor);
}

void mCc_ast_visit_function_call(struct mCc_ast_function_call *function_call,
                                 struct mCc_ast_visitor *visitor)
{
	assert(function_call);
	assert(visitor);

	visit_if_pre_order(function_call, visitor->function_call, visitor);

	mCc_ast_visit_identifier(function_call->identifier, visitor);
	mCc_ast_visit_optional_expression(function_call->first_argument, visitor);

	visit_if_post_order(function_call, visitor->function_call, visitor);
}
