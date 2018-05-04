#include "mCc/ast/basis/ast_function.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

/*----------------- function definition-----------------*/
struct mCc_ast_function_def *mCc_ast_new_non_parameterized_function_def(
    struct mCc_ast_identifier *identifier, enum mCc_ast_data_type return_type,
    struct mCc_ast_statement *stmts)
{
	struct mCc_ast_function_def *function = malloc(sizeof(*function));
	if (!function) {
		return NULL;
	}

	function->identifier = identifier;
	function->return_type = return_type;
	function->first_statement = stmts;
	// set explicitly to null
	function->next_function_def = NULL;
	function->first_parameter = NULL;
	function->semantic_error = NULL;

	return function;
}

struct mCc_ast_function_def *mCc_ast_new_parameterized_function_def(
    struct mCc_ast_identifier *identifier, enum mCc_ast_data_type return_type,
    struct mCc_ast_declaration *params, struct mCc_ast_statement *stmts)
{
	struct mCc_ast_function_def *function =
	    mCc_ast_new_non_parameterized_function_def(identifier, return_type,
	                                               stmts);
	function->first_parameter = params;
	return function;
}

void mCc_ast_delete_function_def(struct mCc_ast_function_def *function_def)
{
	assert(function_def);
	mCc_validator_delete_validation_result(function_def->semantic_error);

	mCc_ast_delete_identifier(function_def->identifier);

	if (function_def->first_statement) {
		mCc_ast_delete_statement(function_def->first_statement);
	}
	if (function_def->first_parameter) {
		mCc_ast_delete_declaration(function_def->first_parameter);
	}
	if (function_def->next_function_def) {
		mCc_ast_delete_function_def(function_def->next_function_def);
	}
	free(function_def);
}

/*-----------------function call-----------------*/
struct mCc_ast_function_call *mCc_ast_new_non_parameterized_function_call(
    struct mCc_ast_identifier *identifier)
{
	struct mCc_ast_function_call *function = malloc(sizeof(*function));
	if (!function) {
		return NULL;
	}

	function->identifier = identifier;
	// explicitly set to null
	function->first_argument = NULL;
	function->semantic_error = NULL;

	return function;
}

struct mCc_ast_function_call *
mCc_ast_new_parameterized_function_call(struct mCc_ast_identifier *identifier,
                                        struct mCc_ast_expression *args)
{
	struct mCc_ast_function_call *function =
	    mCc_ast_new_non_parameterized_function_call(identifier);
	function->first_argument = args;

	return function;
}

void mCc_ast_delete_function_call(struct mCc_ast_function_call *function_call)
{
	assert(function_call);
	mCc_validator_delete_validation_result(function_call->semantic_error);

	mCc_ast_delete_identifier(function_call->identifier);
	if (function_call->first_argument) {
		mCc_ast_delete_expression(function_call->first_argument);
	}
	free(function_call);
}
