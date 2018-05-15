#include "tac_statement.h"

#include <assert.h>

#include "basic_tac.h"

void mCc_tac_statement_if(struct mCc_ast_statement *statement,
                          struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->if_statement->condition_expression
	                           ->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_statement_while(struct mCc_ast_statement *statement,
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
}

void mCc_tac_statement_return(struct mCc_ast_statement *statement,
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
}

void mCc_tac_statement_declaration(struct mCc_ast_statement *statement,
                                   struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->declaration->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_statement_assignment(struct mCc_ast_statement *statement,
                                  struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->assignment->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_statement_expression(struct mCc_ast_statement *statement,
                                  struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY,
	    tac_new_identifier(statement->expression->identifier->identifier_name),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}
