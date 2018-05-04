#include "mCc/ast/basis/ast_statement.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct mCc_ast_statement *
mCc_ast_new_if_statement(struct mCc_ast_expression *condition_expr,
                         struct mCc_ast_statement *if_stmt,
                         struct mCc_ast_statement *else_stmt)
{
	struct mCc_ast_statement *statement = malloc(sizeof(*statement));
	if (!statement) {
		return NULL;
	}

	// set explicitly to null
	statement->next_statement = NULL;
	statement->statement_type = MCC_AST_STATEMENT_IF;
	statement->condition_expression = condition_expr;
	statement->if_statement = if_stmt;
	statement->else_statement = else_stmt;
	statement->semantic_error = NULL;

	return statement;
}

struct mCc_ast_statement *
mCc_ast_new_while_statement(struct mCc_ast_expression *loop_expr,
                            struct mCc_ast_statement *while_stmt)
{
	struct mCc_ast_statement *statement = malloc(sizeof(*statement));
	if (!statement) {
		return NULL;
	}

	// set explicitly to null
	statement->next_statement = NULL;
	statement->statement_type = MCC_AST_STATEMENT_WHILE;
	statement->loop_condition_expression = loop_expr;
	statement->while_statement = while_stmt;
	statement->semantic_error = NULL;

	return statement;
}
struct mCc_ast_statement *
mCc_ast_new_return_statement(struct mCc_ast_expression *return_expression)
{
	struct mCc_ast_statement *statement = malloc(sizeof(*statement));
	if (!statement) {
		return NULL;
	}

	// set explicitly to null
	statement->next_statement = NULL;
	statement->statement_type = MCC_AST_STATEMENT_RETURN;
	statement->return_expression = return_expression;
	statement->semantic_error = NULL;

	return statement;
}

struct mCc_ast_statement *
mCc_ast_new_expression_statement(struct mCc_ast_expression *expression_stmt)
{
	struct mCc_ast_statement *statement = malloc(sizeof(*statement));
	if (!statement) {
		return NULL;
	}

	// set explicitly to null
	statement->next_statement = NULL;
	statement->statement_type = MCC_AST_STATEMENT_EXPRESSION;
	statement->expression = expression_stmt;
	statement->semantic_error = NULL;

	return statement;
}

struct mCc_ast_statement *
mCc_ast_new_declaration_statement(struct mCc_ast_declaration *declaration)
{
	struct mCc_ast_statement *statement = malloc(sizeof(*statement));
	if (!statement) {
		return NULL;
	}

	// set explicitly to null
	statement->next_statement = NULL;
	statement->statement_type = MCC_AST_STATEMENT_DECLARATION;
	statement->declaration = declaration;
	statement->semantic_error = NULL;

	return statement;
}

struct mCc_ast_statement *
mCc_ast_new_assign_statement(struct mCc_ast_assignment *assignment)
{
	struct mCc_ast_statement *statement = malloc(sizeof(*statement));
	if (!statement) {
		return NULL;
	}

	// set explicitly to null
	statement->next_statement = NULL;
	statement->statement_type = MCC_AST_STATEMENT_ASSIGNMENT;
	statement->assignment = assignment;
	statement->semantic_error = NULL;

	return statement;
}

void mCc_ast_delete_statement(struct mCc_ast_statement *stmt)
{
	assert(stmt);
	mCc_validator_delete_validation_result(stmt->semantic_error);

	switch (stmt->statement_type) {
	case MCC_AST_STATEMENT_IF:
		mCc_ast_delete_expression(stmt->condition_expression);

		if (stmt->if_statement) {
			mCc_ast_delete_statement(stmt->if_statement);
		}
		if (stmt->else_statement) {
			mCc_ast_delete_statement(stmt->else_statement);
		}
		break;

	case MCC_AST_STATEMENT_WHILE:
		mCc_ast_delete_expression(stmt->loop_condition_expression);
		if (stmt->while_statement) {
			mCc_ast_delete_statement(stmt->while_statement);
		}
		break;

	case MCC_AST_STATEMENT_RETURN:
		if (stmt->return_expression) {
			mCc_ast_delete_expression(stmt->return_expression);
		}
		break;

	case MCC_AST_STATEMENT_EXPRESSION:
		mCc_ast_delete_expression(stmt->expression);
		break;

	case MCC_AST_STATEMENT_DECLARATION:
		mCc_ast_delete_declaration(stmt->declaration);
		break;

	case MCC_AST_STATEMENT_ASSIGNMENT:
		mCc_ast_delete_assignment(stmt->assignment);
		break;
	}

	if (stmt->next_statement) {
		mCc_ast_delete_statement(stmt->next_statement);
	}

	free(stmt);
}
