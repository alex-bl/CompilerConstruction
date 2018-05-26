#include "tac_statement.h"

#include <assert.h>

#include "ast_expression.h"
#include "basic_tac.h"
#include "tac_assignment.h"
#include "tac_declaration.h"
#include "tac_expression.h"

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
	//mCc_tac_connect_tac_entry(previous_tac, statement_tac);
	return statement_tac;
}

struct mCc_tac_element *
mCc_tac_statement_if(struct mCc_ast_statement *statement,
                     struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(statement->condition_expression);
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
	    MCC_TAC_OPARATION_CONDITIONAL_JUMP,
	    tac_new_identifier(tac_statement->tac_result->name),
	    tac_new_identifier(tac_else_statement->tac_result->name),
	    tac_new_identifier(tac_if_statement->tac_result->name),
	    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(tac_statement, tac_if_condition);
	mCc_tac_connect_tac_entry(tac_if_condition, tac_if_statement);
	mCc_tac_connect_tac_entry(tac_if_statement, tac_else_statement);

	return tac_else_statement;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_while(struct mCc_ast_statement *statement,
                        struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(statement->loop_condition_expression);
	assert(previous_tac);

	struct mCc_tac_element *tac_while_expression = helper_get_tac_of_expression(
	    statement->loop_condition_expression, previous_tac);

	struct mCc_tac_element *tac_while_statement =
	    helper_get_tac_of_statement(statement, tac_while_expression);

	// TODO add label where to jump, if while is false
	// struct mCc_tac_element *tac_while_false_statement = tac_new_element(
	//    MCC_TAC_OPARATION_LABLE, NULL, NULL, NULL /*add label*/);

	struct mCc_tac_element *tac_while_condition = tac_new_element(
	    MCC_TAC_OPARATION_CONDITIONAL_JUMP,
	    tac_new_identifier(tac_while_statement->tac_result->name), NULL,
	    tac_new_identifier(tac_while_statement->tac_result->name),
	    MCC_TAC_TYPE_NO_TYPE, 0);

	mCc_tac_connect_tac_entry(previous_tac, tac_while_expression);
	mCc_tac_connect_tac_entry(tac_while_expression, tac_while_condition);
	mCc_tac_connect_tac_entry(tac_while_condition, tac_while_statement);
	return tac_while_statement;
}

struct mCc_tac_element *
mCc_tac_statement_return(struct mCc_ast_statement *statement,
                         struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	if (statement->return_expression!=NULL) {
		struct mCc_tac_element *tac_return_expression =
			helper_get_tac_of_expression(statement->return_expression,
										 previous_tac);
assert(tac_return_expression->tac_result->name);
		struct mCc_tac_element *tac = tac_new_element(
			MCC_TAC_OPARATION_RETURN, NULL, NULL,
			tac_new_identifier(tac_return_expression->tac_result->name),
			MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(tac_return_expression, tac);
		return tac;
	} else {
		return previous_tac;
	}
}

struct mCc_tac_element *
mCc_tac_statement_declaration(struct mCc_ast_statement *statement,
                              struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac_declaration;
	if (statement->declaration->declaration_type ==
	    MCC_AST_DECLARATION_PRIMITIVE) {
		tac_declaration =
		    mCc_tac_declaration_primitive(statement->declaration, previous_tac);
	} else if (statement->declaration->declaration_type ==
	           MCC_AST_DECLARATION_ARRAY) {
		tac_declaration =
		    mCc_tac_declaration_array(statement->declaration, previous_tac);
	}
	return tac_declaration;
}

struct mCc_tac_element *
mCc_tac_statement_assignment(struct mCc_ast_statement *statement,
                             struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac_assignment;
	if (statement->assignment->assignment_type ==
	    MCC_AST_ASSIGNMENT_PRIMITIVE) {
		tac_assignment =
		    mCc_tac_assignment_primitive(statement->assignment, previous_tac);
	} else if (statement->assignment->assignment_type ==
	           MCC_AST_ASSIGNMENT_ARRAY) {
		tac_assignment =
		    mCc_tac_assignment_array(statement->assignment, previous_tac);
	}
	return tac_assignment;
}

struct mCc_tac_element *
mCc_tac_statement_expression(struct mCc_ast_statement *statement,
                             struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(statement->expression);
	assert(previous_tac);

	struct mCc_tac_element *tac_expression =
	    helper_get_tac_of_expression(statement->expression, previous_tac);

	return tac_expression;
}
