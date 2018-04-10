#include "mCc/ast/visit/ast_visit_statement.h"

#include <assert.h>

#include "mCc/ast/visit/ast_visit_assignment.h"
#include "mCc/ast/visit/ast_visit_declaration.h"
#include "mCc/ast/visit/ast_visit_expression.h"

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

	switch (statement->statement_type) {
	case MCC_AST_STATEMENT_IF:
		visit_if_pre_order(statement, visitor->statement_if, visitor);

		mCc_ast_visit_expression(statement->condition_expression, visitor);

		// new major scope
		(visitor->scope_level->major_level)++;

		// if + else stmts may be empty
		mCc_ast_visit_optional_statement(statement->if_statement, visitor);

		// new minor scope: same hierarchy-level, but different scope
		(visitor->scope_level->minor_level)++;

		mCc_ast_visit_optional_statement(statement->else_statement, visitor);

		// returning to old scope: both major + minor
		(visitor->scope_level->major_level)--;
		(visitor->scope_level->minor_level)--;

		mCc_ast_visit_optional_statement(statement->next_statement, visitor);

		visit_if_post_order(statement, visitor->statement_if, visitor);
		break;
	case MCC_AST_STATEMENT_WHILE:
		visit_if_pre_order(statement, visitor->statement_while, visitor);

		mCc_ast_visit_expression(statement->loop_condition_expression, visitor);

		// new scope
		//		*(visitor->scope_level) = *(visitor->scope_level) + 1;
		// while-stmt may be empty
		mCc_ast_visit_optional_statement(statement->while_statement, visitor);
		// returning to old scope
		//		*(visitor->scope_level) = *(visitor->scope_level) - 1;

		mCc_ast_visit_optional_statement(statement->next_statement, visitor);

		visit_if_post_order(statement, visitor->statement_while, visitor);
		break;
	case MCC_AST_STATEMENT_RETURN:
		visit_if_pre_order(statement, visitor->statement_return, visitor);

		// there can also be no return type
		mCc_ast_visit_optional_expression(statement->return_expression,
		                                  visitor);

		// TODO: required here? Does dead-code after return throws an error?
		mCc_ast_visit_optional_statement(statement->next_statement, visitor);

		visit_if_post_order(statement, visitor->statement_return, visitor);

		break;

	case MCC_AST_STATEMENT_DECLARATION:
		visit_if_pre_order(statement, visitor->statement_declaration, visitor);

		mCc_ast_visit_declaration(statement->declaration, visitor);

		mCc_ast_visit_optional_statement(statement->next_statement, visitor);

		visit_if_post_order(statement, visitor->statement_declaration, visitor);

		break;
	case MCC_AST_STATEMENT_ASSIGNMENT:
		visit_if_pre_order(statement, visitor->statement_assignment, visitor);

		mCc_ast_visit_assignment(statement->assignment, visitor);

		mCc_ast_visit_optional_statement(statement->next_statement, visitor);
		visit_if_post_order(statement, visitor->statement_assignment, visitor);

		break;
	case MCC_AST_STATEMENT_EXPRESSION:
		visit_if_pre_order(statement, visitor->statement_expression, visitor);

		mCc_ast_visit_expression(statement->expression, visitor);

		mCc_ast_visit_optional_statement(statement->next_statement, visitor);

		visit_if_post_order(statement, visitor->statement_expression, visitor);

		break;
	}

	visit_if_post_order(statement, visitor->statement, visitor);
}
