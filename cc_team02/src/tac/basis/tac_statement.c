#include "tac_statement.h"
#include "ast_expression.h"
#include "tac_expression.h"

#include <assert.h>

#include "basic_tac.h"

// not really used - till now?
char *helper_type_to_char(enum mCc_ast_expression_type type)
{
	/*	MCC_AST_EXPRESSION_TYPE_LITERAL,
	MCC_AST_EXPRESSION_TYPE_BINARY_OP,
	MCC_AST_EXPRESSION_TYPE_PARENTH,
	MCC_AST_EXPRESSION_TYPE_IDENTIFIER,
	MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY,
	MCC_AST_EXPRESSION_TYPE_CALL_EXPR,
	MCC_AST_EXPRESSION_TYPE_UNARY_OP */

	char *return_char;
	switch (type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL: return_char = "void"; break;
	case MCC_AST_EXPRESSION_TYPE_BINARY_OP: return_char = "int"; break;
	case MCC_AST_EXPRESSION_TYPE_PARENTH: return_char = "float"; break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER: return_char = "bool"; break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
		return_char = "string";
		break;
	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR: return_char = "inconsistent"; break;
	case MCC_AST_EXPRESSION_TYPE_UNARY_OP: return_char = "incompatible"; break;
	}
	return return_char;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_if(struct mCc_ast_statement *statement,
                     struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac_statement;

	switch (statement->condition_expression->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL:
		tac_statement = mCc_tac_expression_literal(
		    statement->condition_expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		tac_statement = mCc_tac_expression_binary_op(
		    statement->condition_expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		tac_statement = mCc_tac_expression_parenth(
		    statement->condition_expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		tac_statement = mCc_tac_expression_identifier(
		    statement->condition_expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
		tac_statement = mCc_tac_expression_identifier_array(
		    statement->condition_expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
		tac_statement = mCc_tac_expression_function_call(
		    statement->condition_expression, previous_tac);
		break;
	case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
		tac_statement = mCc_tac_expression_unary_op(
		    statement->condition_expression, previous_tac);
		break;
	}
	mCc_tac_connect_tac_entry(previous_tac, tac_statement);

	//struct mCc_tac_element *if_statement=statement->if_statement->;


	struct mCc_tac_element *tac = tac_new_element(
			MCC_TAC_OPARATION_CONDITIONAL_JUMP,
		   tac_statement->tac_result,
		    NULL/*if statement*/, NULL/*else statement*/);

	//statement->if_statement;
	//statement->else_statement;

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->if_statement->condition_expression
	                           ->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_while(struct mCc_ast_statement *statement,
                        struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

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
