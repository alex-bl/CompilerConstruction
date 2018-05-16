#include "tac_function.h"
#include "tac_declaration.h"
#include "tac_statement.h"

#include <assert.h>
#include <stdlib.h>

#include "basic_tac.h"

struct mCc_tac_element *
mCc_tac_function_def(struct mCc_ast_function_def *def,
                     struct mCc_tac_element *previous_tac)
{
	assert(def);
	assert(previous_tac);

	// stores parameter into tac table
	// not needed in the function def?
	struct mCc_ast_declaration *parameter = def->first_parameter;
	while (parameter != NULL) {
		struct mCc_tac_element *parameter_tac;
		if (parameter->declaration_type == MCC_AST_DECLARATION_PRIMITIVE) {
			parameter_tac =
			    mCc_tac_declaration_primitive(parameter, previous_tac);
		} else if (parameter->declaration_type == MCC_AST_DECLARATION_ARRAY) {
			parameter_tac = mCc_tac_declaration_array(parameter, previous_tac);
		}
		mCc_tac_connect_tac_entry(previous_tac, parameter_tac);

		struct mCc_tac_element *tac = tac_new_element(
		    MCC_TAC_OPARATION_LABLE, parameter_tac->tac_result, NULL,
		    tac_new_identifier(def->identifier->identifier_name));
		mCc_tac_connect_tac_entry(parameter_tac, tac);
		previous_tac = tac;
		parameter = parameter->next_declaration;
	}

	// TODO auslagern -> available from statements
	// tac table creation for statements:
	struct mCc_ast_statement *statement = def->first_statement;
	while (statement != NULL) {
		/* Statement-Types:
		    MCC_AST_STATEMENT_IF,
		    MCC_AST_STATEMENT_WHILE,
		    MCC_AST_STATEMENT_RETURN,

		    MCC_AST_STATEMENT_DECLARATION,
		    MCC_AST_STATEMENT_ASSIGNMENT,
		    MCC_AST_STATEMENT_EXPRESSION
		 */
		/*struct mCc_tac_element *statement_tac;
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
		    statement_tac =
		        mCc_tac_statement_declaration(statement, previous_tac);
		    break;
		case MCC_AST_STATEMENT_ASSIGNMENT:
		    statement_tac =
		        mCc_tac_statement_assignment(statement, previous_tac);
		    break;
		case MCC_AST_STATEMENT_EXPRESSION:
		    statement_tac =
		        mCc_tac_statement_expression(statement, previous_tac);
		    break;
		}
		mCc_tac_connect_tac_entry(previous_tac, statement_tac);*/
		struct mCc_tac_element *statement_tac =
		    helper_get_tac_of_statement(statement, previous_tac);
		// Has a statement to be in the tac table?
		struct mCc_tac_element *tac = tac_new_element(
		    MCC_TAC_OPARATION_LABLE, statement_tac->tac_result, NULL,
		    tac_new_identifier(def->identifier->identifier_name));
		mCc_tac_connect_tac_entry(statement_tac, tac);
		previous_tac = tac;
		statement = statement->next_statement;
	}

	/*struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_LABLE, NULL, parameter_tac->,
	                    tac_new_identifier(def->identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);*/
	return previous_tac;
}

// TODO recursive structure
struct mCc_tac_element *
mCc_tac_function_call(struct mCc_ast_function_call *call,
                      struct mCc_tac_element *previous_tac)
{
	assert(call);
	assert(previous_tac);

	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_PROCEDURAL_CALL,
	                    tac_new_identifier(call->identifier->identifier_name),
	                    tac_new_identifier((char *)call->first_argument), NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
