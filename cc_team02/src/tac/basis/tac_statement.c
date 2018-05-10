#include "mCc/tac/basis/tac_statement.h"

#include <assert.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_statement_if(struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, statement->if_statement, NULL,
	                NULL);
}

void mCc_tac_statement_while(struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, statement->while_statement, NULL,
	                NULL);
}

void mCc_tac_statement_return(struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	tac_new_element(MCC_TAC_OPARATION_RETURN, statement->return_expression, NULL,
	                NULL);
}

void mCc_tac_statement_declaration(struct mCc_ast_statement *statement,
                                   void *data)
{
	assert(statement);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, statement->declaration, NULL,
	                NULL);
}

void mCc_tac_statement_assignment(struct mCc_ast_statement *statement,
                                  void *data)
{
	assert(statement);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, statement->assignment, NULL,
	                NULL);
}

void mCc_tac_statement_expression(struct mCc_ast_statement *statement,
                                  void *data)
{
	assert(statement);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, statement->expression, NULL,
	                NULL);
}
