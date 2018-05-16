#include "tac_statement.h"
#include "ast_expression.h"
#include "tac_expression.h"

#include <assert.h>

#include "basic_tac.h"

struct mCc_tac_element *
helper_get_tac_of_statement(struct mCc_ast_statement *statement,
                            struct mCc_tac_element *previous_tac)
{
	struct mCc_tac_element *statement_tac;
	switch (statement->statement_type) {
	case MCC_AST_STATEMENT_IF:
		statement_tac = mCc_tac_statement_if(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_WHILE:
		statement_tac = mCc_tac_statement_while(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_RETURN:
		statement_tac = mCc_tac_statement_return(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_DECLARATION:
		statement_tac = mCc_tac_statement_declaration(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_ASSIGNMENT:
		statement_tac = mCc_tac_statement_assignment(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_EXPRESSION:
		statement_tac = mCc_tac_statement_expression(statement, previous_tac);
		break;
	}
	mCc_tac_connect_tac_entry(previous_tac, statement_tac);
	return statement_tac;
}

struct mCc_tac_element *
mCc_tac_statement_if(struct mCc_ast_statement *statement,
                     struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac_statement = helper_get_tac_of_expression(
	    statement->condition_expression, previous_tac);

	// TODO switch from tac_function.c can be used here!
	// struct mCc_tac_element *if_statement=statement->if_statement->;
	struct mCc_tac_element *tac_if_statement =
	    helper_get_tac_of_statement(statement->if_statement, tac_statement);
	struct mCc_tac_element *tac_else_statement = helper_get_tac_of_statement(
	    statement->else_statement, tac_if_statement);
	struct mCc_tac_element *tac_if_condition = tac_new_element(
	    MCC_TAC_OPARATION_CONDITIONAL_JUMP, tac_statement->tac_result,
	    tac_else_statement->tac_result, tac_if_statement->tac_result);
	mCc_tac_connect_tac_entry(tac_statement, tac_if_condition);
	mCc_tac_connect_tac_entry(tac_if_condition, tac_if_statement);
	mCc_tac_connect_tac_entry(tac_statement, tac_else_statement);

	return tac_else_statement;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_while(struct mCc_ast_statement *statement,
                        struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	// TODO next

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->while_statement->condition_expression
	                           ->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_return(struct mCc_ast_statement *statement,
                         struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_RETURN,
	    tac_new_identifier(
	        statement->return_expression->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_declaration(struct mCc_ast_statement *statement,
                              struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->declaration->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_assignment(struct mCc_ast_statement *statement,
                             struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->assignment->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_expression(struct mCc_ast_statement *statement,
                             struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->expression->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
