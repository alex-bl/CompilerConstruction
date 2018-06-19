#include "tac_function.h"

#include <assert.h>
#include <stdlib.h>

#include "basic_tac.h"
#include "tac_declaration.h"
#include "tac_expression.h"
#include "tac_statement.h"
#include "tac_utils.h"

enum mCc_tac_operation tac_helper_get_tac_oparation_for_parameter_type(
    enum mCc_tac_operation operation)
{
	switch (operation) {
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT:
		return MCC_TAC_OPARATION_PARAM_INT_PRIMITIVE;
		break;
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_FLOAT:
		return MCC_TAC_OPARATION_PARAM_FLOAT_PRIMITIVE;
		break;
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL:
		return MCC_TAC_OPARATION_PARAM_BOOL_PRIMITIVE;
		break;
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_STRING:
		return MCC_TAC_OPARATION_PARAM_STRING_PRIMITIVE;
		break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_INT:
		return MCC_TAC_OPARATION_PARAM_INT_ARRAY;
		break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_FLOAT:
		return MCC_TAC_OPARATION_PARAM_FLOAT_ARRAY;
		break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_BOOL:
		return MCC_TAC_OPARATION_PARAM_BOOL_ARRAY;
		break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_STRING:
		return MCC_TAC_OPARATION_PARAM_STRING_ARRAY;
		break;
	default: return MCC_TAC_OPARATION_EMPTY; break;
	}
}

static enum mCc_tac_operation
map_return_type(enum mCc_ast_data_type ast_data_type)
{
	switch (ast_data_type) {
	case MCC_AST_DATA_TYPE_INT:
		return MCC_TAC_OPARATION_INTERMEDIATE_RETURN_INT;
	case MCC_AST_DATA_TYPE_FLOAT:
		return MCC_TAC_OPARATION_INTERMEDIATE_RETURN_FLOAT;
	case MCC_AST_DATA_TYPE_BOOL:
		return MCC_TAC_OPARATION_INTERMEDIATE_RETURN_BOOL;
	case MCC_AST_DATA_TYPE_STRING:
		return MCC_TAC_OPARATION_INTERMEDIATE_RETURN_STRING;
	default: return MCC_TAC_OPARATION_INTERMEDIATE_RETURN_INT;
	}
	return MCC_TAC_OPARATION_INTERMEDIATE_RETURN_INT;
}

struct mCc_tac_element *
mCc_tac_function_def(struct mCc_ast_function_def *def,
                     struct mCc_tac_element *previous_tac)
{
	assert(def);
	assert(previous_tac);

	// adds label for the start of the function
	// next function as first argument in tac element
	struct mCc_tac_identifier *next_function_def;
	if (def->next_function_def != NULL) {
		next_function_def = tac_new_identifier(
		    def->next_function_def->identifier->identifier_name);
	} else {
		next_function_def = NULL;
	}
	struct mCc_tac_element *tac_function_label = tac_new_element(
	    MCC_TAC_OPARATION_LABEL_FUNCTION, next_function_def, NULL,
	    tac_new_identifier(def->identifier->identifier_name),
	    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_function_label);
	previous_tac = tac_function_label;

	// started function def:
	struct mCc_tac_element *tac_function_def_start =
	    tac_new_element(MCC_TAC_OPARATION_START_FUNCTION_DEF, NULL, NULL,
	                    tac_new_identifier(def->identifier->identifier_name),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_function_def_start);
	previous_tac = tac_function_def_start;

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

		// hacky -.-
		parameter_tac->tac_result->is_param = true;
		struct mCc_tac_identifier *param_identifier =
		    mCc_tac_create_from_tac_identifier(parameter_tac->tac_result);

		enum mCc_ast_data_type ast_data_type = parameter->data_type;

		struct mCc_tac_identifier *def_identifier =
		    tac_new_identifier(def->identifier->identifier_name);
		def_identifier->type = MCC_IDENTIFIER_TAC_TYPE_FUNCTION_DEF;

		struct mCc_tac_element *tac =
		    tac_new_element(tac_helper_get_tac_oparation_for_parameter_type(
		                        parameter_tac->tac_operation),
		                    param_identifier, NULL, def_identifier,
		                    mCc_tac_map_from_ast_data_type(ast_data_type), 0);

		// TODO: not needed here => param already available
		mCc_tac_delete(parameter_tac);

		mCc_tac_connect_tac_entry(previous_tac, tac);
		previous_tac = tac;
		parameter = parameter->next_declaration;
	}

	// tac table creation for statements:
	struct mCc_ast_statement *statement = def->first_statement;
	while (statement != NULL) {
		struct mCc_tac_element *statement_tac =
		    helper_get_tac_of_statement(statement, previous_tac);
		// Has a statement to be in the tac table?
		/*struct mCc_tac_element *tac = tac_new_element(
		    MCC_TAC_OPARATION_LABLE,
		    mCc_tac_create_from_tac_identifier(statement_tac->tac_result),
		NULL, tac_new_identifier(def->identifier->identifier_name),
		    MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(statement_tac, tac);
		previous_tac = tac;*/
		previous_tac = statement_tac;
		statement = statement->next_statement;
	}

	struct mCc_tac_element *tac_function_def_end =
	    tac_new_element(MCC_TAC_OPARATION_END_FUNCTION_DEF, NULL, NULL,
	                    tac_new_identifier(def->identifier->identifier_name),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_function_def_end);

	return tac_function_def_end;
}

struct mCc_tac_element *
mCc_tac_function_call(struct mCc_ast_function_call *call,
                      struct mCc_tac_element *previous_tac)
{
	assert(call);
	assert(previous_tac);

	// introduces arguments of a function:
	struct mCc_tac_element *tac_starting_arguments =
	    tac_new_element(MCC_TAC_OPARATION_ARGUMENT_LIST_START, NULL, NULL,
	                    tac_new_identifier(call->identifier->identifier_name),
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_starting_arguments);
	previous_tac = tac_starting_arguments;

	// call->first_argument
	// stores arguments into tac table
	struct mCc_ast_expression *argument = call->first_argument;
	while (argument != NULL) {
		struct mCc_tac_element *tac_argument =
		    helper_get_tac_of_expression(argument, previous_tac);

		enum mCc_ast_data_type ast_data_type = argument->data_type;

		struct mCc_tac_identifier *call_identifier =
		    tac_new_identifier(call->identifier->identifier_name);
		call_identifier->type = MCC_IDENTIFIER_TAC_TYPE_FUNCTION_CALL;

		struct mCc_tac_element *tac = tac_new_element(
		    MCC_TAC_OPARATION_LABEL_ARGUMENT,
		    mCc_tac_create_from_tac_identifier(tac_argument->tac_result), NULL,
		    call_identifier, mCc_tac_map_from_ast_data_type(ast_data_type), 0);
		mCc_tac_connect_tac_entry(tac_argument, tac);
		previous_tac = tac;
		argument = argument->next_expr;
	}

	enum mCc_ast_data_type ast_data_type =
	    call->identifier->symtab_info->data_type;

	// stores call into tac table
	struct mCc_tac_element *tac_function_call =
	    tac_new_element(MCC_TAC_OPARATION_FUNCTION_CALL, NULL, NULL,
	                    tac_new_identifier(call->identifier->identifier_name),
	                    mCc_tac_map_from_ast_data_type(ast_data_type), 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_function_call);

	struct mCc_tac_identifier *tmp = mCc_tac_create_new_lable_identifier();
	tmp->type = MCC_IDENTIFIER_TAC_TYPE_VAR;

	if (ast_data_type != MCC_AST_DATA_TYPE_VOID) {
		struct mCc_tac_element *tac_intermediate_return = tac_new_element(
		    map_return_type(ast_data_type), tmp,
		    tac_new_identifier(call->identifier->identifier_name), tmp,
		    mCc_tac_map_from_ast_data_type(ast_data_type), 0);

		mCc_tac_connect_tac_entry(tac_function_call, tac_intermediate_return);

		return tac_intermediate_return;
	}
	return tac_function_call;
}
