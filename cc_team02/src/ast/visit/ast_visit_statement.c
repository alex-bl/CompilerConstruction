#include "ast_visit_statement.h"

#include <assert.h>

#include "ast_visit_assignment.h"
#include "ast_visit_declaration.h"
#include "ast_visit_expression.h"
#include "log.h"

// TODO: warning if dead-code is detected?
void mCc_ast_visit_optional_statement(struct mCc_ast_statement *statement,
                                      struct mCc_ast_visitor *visitor)
{
	if (statement) {
		mCc_ast_visit_statement(statement, visitor);
	}
}

void mCc_ast_visit_statement(struct mCc_ast_statement *statement,
                             struct mCc_ast_visitor *visitor)
{
	assert(statement);
	assert(visitor);

	visit_if_pre_order(statement, visitor->statement, visitor);
	visit_if_both_order(statement, visitor->statement, visitor);

	switch (statement->statement_type) {
	case MCC_AST_STATEMENT_IF:
		visit_if_pre_order(statement, visitor->statement_if, visitor);
		visit_if_both_order(statement, visitor->statement_if, visitor);

		mCc_ast_visit_expression(statement->condition_expression, visitor);

		//=========================needed for building the symbol-table
		visit_scope(visitor->statement_if_enter_scope, visitor);
		//=============================================================

		// if + else stmts may be empty
		mCc_ast_visit_optional_statement(statement->if_statement, visitor);

		//=========================needed for building the symbol-table
		visit_scope(visitor->statement_if_leave_scope, visitor);
		//=============================================================

		//=========================needed for building the symbol-table
		visit_if_scope(statement->else_statement,
		               visitor->statement_if_enter_scope, visitor);
		//=============================================================

		mCc_ast_visit_optional_statement(statement->else_statement, visitor);

		//=========================needed for building the symbol-table
		visit_if_scope(statement->else_statement,
		               visitor->statement_if_leave_scope, visitor);
		//=============================================================
		// post-order before next statement
		visit_if_post_order(statement, visitor->statement_if, visitor);
		visit_if_both_order(statement, visitor->statement_if_post_order,
		                    visitor);
		break;
	case MCC_AST_STATEMENT_WHILE:
		visit_if_pre_order(statement, visitor->statement_while, visitor);
		visit_if_both_order(statement, visitor->statement_while, visitor);

		mCc_ast_visit_expression(statement->loop_condition_expression, visitor);

		//=========================needed for building the symbol-table
		visit_if_scope(statement->while_statement,
		               visitor->statement_while_enter_scope, visitor);
		//=============================================================
		mCc_ast_visit_optional_statement(statement->while_statement, visitor);

		//=========================needed for building the symbol-table
		visit_if_scope(statement->while_statement,
		               visitor->statement_while_leave_scope, visitor);
		//=============================================================

		visit_if_post_order(statement, visitor->statement_while, visitor);
		visit_if_both_order(statement, visitor->statement_while_post_order,
		                    visitor);
		break;
	case MCC_AST_STATEMENT_RETURN:
		visit_if_pre_order(statement, visitor->statement_return, visitor);
		visit_if_both_order(statement, visitor->statement_return, visitor);

		// there can also be no return type
		mCc_ast_visit_optional_expression(statement->return_expression,
		                                  visitor);

		visit_if_post_order(statement, visitor->statement_return, visitor);
		visit_if_both_order(statement, visitor->statement_return_post_order,
		                    visitor);
		break;
	case MCC_AST_STATEMENT_DECLARATION:
		visit_if_pre_order(statement, visitor->statement_declaration, visitor);
		visit_if_both_order(statement, visitor->statement_declaration, visitor);

		mCc_ast_visit_declaration(statement->declaration, visitor);

		visit_if_post_order(statement, visitor->statement_declaration, visitor);
		visit_if_both_order(statement,
		                    visitor->statement_declaration_post_order, visitor);
		break;
	case MCC_AST_STATEMENT_ASSIGNMENT:
		visit_if_pre_order(statement, visitor->statement_assignment, visitor);

		mCc_ast_visit_assignment(statement->assignment, visitor);

		visit_if_post_order(statement, visitor->statement_assignment, visitor);
		break;
	case MCC_AST_STATEMENT_EXPRESSION:
		visit_if_pre_order(statement, visitor->statement_expression, visitor);
		visit_if_both_order(statement, visitor->statement_expression, visitor);

		mCc_ast_visit_expression(statement->expression, visitor);

		visit_if_post_order(statement, visitor->statement_expression, visitor);
		visit_if_both_order(statement, visitor->statement_expression_post_order,
		                    visitor);
		break;
	}

	visit_if_post_order(statement, visitor->statement, visitor);
	visit_if_both_order(statement, visitor->statement_post_order, visitor);

	// TODO: required after return? Does dead-code after return throws an error?
	if (statement->statement_type != MCC_AST_STATEMENT_RETURN) {
		mCc_ast_visit_optional_statement(statement->next_statement, visitor);
	}
}
