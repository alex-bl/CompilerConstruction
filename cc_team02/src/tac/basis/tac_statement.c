#include "mCc/tac/basis/tac_statement.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_statement_if(struct mCc_ast_statement *statement,
                          struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, statement->if_statement, NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_statement_while(struct mCc_ast_statement *statement,
                             struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, statement->while_statement, NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_statement_return(struct mCc_ast_statement *statement,
                              struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_RETURN, statement->return_expression, NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_statement_declaration(struct mCc_ast_statement *statement,
                                   struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, statement->declaration, NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_statement_assignment(struct mCc_ast_statement *statement,
                                  struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, statement->assignment, NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}

void mCc_tac_statement_expression(struct mCc_ast_statement *statement,
                                  struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, statement->expression, NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
}
