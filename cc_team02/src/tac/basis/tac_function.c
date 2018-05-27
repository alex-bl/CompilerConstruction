#include "tac_function.h"

#include <assert.h>
#include <stdlib.h>

#include "basic_tac.h"
#include "tac_declaration.h"
#include "tac_expression.h"
#include "tac_statement.h"

struct mCc_tac_element *
mCc_tac_function_def(struct mCc_ast_function_def *def,
                     struct mCc_tac_element *previous_tac)
{
	assert(def);
	assert(previous_tac);

	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_LABLE, NULL, NULL,
	                    tac_new_identifier(def->identifier->identifier_name),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	previous_tac = tac;

	// stores parameter into tac table
	struct mCc_ast_declaration *parameter = def->first_parameter;
	while (parameter != NULL) {
		struct mCc_tac_element *parameter_tac;
		if (parameter->declaration_type == MCC_AST_DECLARATION_PRIMITIVE) {
			parameter_tac =
			    mCc_tac_declaration_primitive(parameter, previous_tac);
		} else if (parameter->declaration_type == MCC_AST_DECLARATION_ARRAY) {
			parameter_tac = mCc_tac_declaration_array(parameter, previous_tac);
		}
		//mCc_tac_connect_tac_entry(previous_tac, parameter_tac);

		struct mCc_tac_element *tac = tac_new_element(
		    MCC_TAC_OPARATION_LABLE,
		    tac_new_identifier(parameter_tac->tac_result->name), NULL,
		    tac_new_identifier(def->identifier->identifier_name),
		    MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(parameter_tac, tac);
		previous_tac = tac;
		parameter = parameter->next_declaration;
	}

	// tac table creation for statements:
	struct mCc_ast_statement *statement = def->first_statement;
	while (statement != NULL) {
		struct mCc_tac_element *statement_tac =
		    helper_get_tac_of_statement(statement, previous_tac);
		// Has a statement to be in the tac table?
		struct mCc_tac_element *tac = tac_new_element(
		    MCC_TAC_OPARATION_LABLE,
		    tac_new_identifier(statement_tac->tac_result->name), NULL,
		    tac_new_identifier(def->identifier->identifier_name),
		    MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(statement_tac, tac);
		previous_tac = tac;
		statement = statement->next_statement;
	}

	return previous_tac;
}

struct mCc_tac_element *
mCc_tac_function_call(struct mCc_ast_function_call *call,
                      struct mCc_tac_element *previous_tac)
{
	assert(call);
	assert(previous_tac);

	// call->first_argument
	// stores arguments into tac table
	struct mCc_ast_expression *argument = call->first_argument;
	while (argument != NULL) {
		struct mCc_tac_element *tac_argument =
		    helper_get_tac_of_expression(argument, previous_tac);

		struct mCc_tac_element *tac = tac_new_element(
		    MCC_TAC_OPARATION_LABLE,
		    tac_new_identifier(tac_argument->tac_result->name), NULL,
		    tac_new_identifier(call->identifier->identifier_name),
		    MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(tac_argument, tac);
		previous_tac = tac;
		argument = argument->next_expr;
	}

	// call->identifier->identifier_name
	// stores call into tac table
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_PROCEDURAL_CALL,
	    tac_new_identifier(previous_tac->tac_result->name), NULL,
	    tac_new_identifier(call->identifier->identifier_name),
	    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
