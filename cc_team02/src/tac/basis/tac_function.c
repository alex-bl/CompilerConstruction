#include "tac_function.h"
#include "tac_declaration.h"

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
