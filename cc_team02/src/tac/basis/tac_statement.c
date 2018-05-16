#include "tac_statement.h"
#include "tac_expression.h"
#include "tac_declaration.h"

#include <assert.h>

#include "basic_tac.h"

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_statement_if(struct mCc_ast_statement *statement,
                     struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	//helper_data_type_to_char(statement->condition_expression)
	/*struct mCc_tac_element *tac_expression;
	char *return_char;
		switch (statement->condition_expression) {
		case MCC_AST_DATA_TYPE_VOID: tac_expression =
			    mCc_tac_expression(statement->condition_expression, previous_tac);; break;
		case MCC_AST_DATA_TYPE_INT: tac_expression =
			    mCc_tac_expression(statement->condition_expression, previous_tac);; break;
		case MCC_AST_DATA_TYPE_FLOAT: tac_expression =
			    mCc_tac_expression(statement->condition_expression, previous_tac);; break;
		case MCC_AST_DATA_TYPE_BOOL: tac_expression =
			    mCc_tac_expression(statement->condition_expression, previous_tac);; break;
		case MCC_AST_DATA_TYPE_STRING: tac_expression =
			    mCc_tac_expression(statement->condition_expression, previous_tac);; break;
		case MCC_AST_DATA_TYPE_INCONSISTENT: rtac_expression =
			    mCc_tac_expression(statement->condition_expression, previous_tac);; break;
		case MCC_AST_DATA_TYPE_INCOMPATIBLE: tac_expression =
			    mCc_tac_expression(statement->condition_expression, previous_tac); break;
		case MCC_AST_DATA_TYPE_UNKNOWN: tac_expression =
			    mCc_tac_expression(statement->condition_expression, previous_tac); break;
		}*/

	struct mCc_tac_element *tac =
	    tac_new_element(
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
