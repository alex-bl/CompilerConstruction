#include "mCc/symtab/validator/base_validator.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"

static struct mCc_ast_statement *
find_return_statement(struct mCc_ast_function_def *function_def)
{
	assert(function_def);
	struct mCc_ast_statement *next_statement = function_def->first_statement;
	if (!next_statement) {
		log_debug("Function '%s' has no statements",
		          function_def->identifier->identifier_name);
	}
	while (next_statement) {
		if (next_statement->statement_type == MCC_AST_STATEMENT_RETURN) {
			return next_statement;
		}
		next_statement = next_statement->next_statement;
	}
	return NULL;
}

enum mCc_validation_status_type
mCc_validator_check_definition(struct mCc_symbol_table *symbol_table,
                               void *validator_input)
{
	assert(symbol_table);
	assert(validator_input);
	struct mCc_ast_identifier *identifier =
	    (struct mCc_ast_identifier *)validator_input;

	// only look at current scope
	if (!mCc_symtab_lookup(symbol_table, identifier, true)) {
		return MCC_VALIDATION_STATUS_NO_DEF;
	}
	return MCC_VALIDATION_STATUS_VALID;
}

enum mCc_validation_status_type
mCc_validator_check_duplicates(struct mCc_symbol_table *symbol_table,
                               void *validator_input)
{
	assert(symbol_table);
	assert(validator_input);
	struct mCc_ast_identifier *identifier =
	    (struct mCc_ast_identifier *)validator_input;
	// only look at current scope
	if (mCc_symtab_lookup(symbol_table, identifier, true)) {
		return MCC_VALIDATION_STATUS_NOT_UNIQUE;
	}
	return MCC_VALIDATION_STATUS_VALID;
}

enum mCc_validation_status_type
mCc_validator_check_main_presence(struct mCc_symbol_table *symbol_table,
                                  void *validator_input)
{
	assert(symbol_table);
	assert(validator_input);
	// avoid unused-warning :D
	log_debug("No need to look at symbol-table with scope %d",
	          symbol_table->scope_level);

	struct mCc_ast_function_def *function_def =
	    (struct mCc_ast_function_def *)validator_input;

	struct mCc_ast_function_def *next_function_def = function_def;

	while (next_function_def) {
		if (strcmp(next_function_def->identifier->identifier_name, "main") ==
		    0) {
			return MCC_VALIDATION_STATUS_VALID;
		}
		function_def = function_def->next_function_def;
	}
	return MCC_VALIDATION_STATUS_NO_MAIN;
}

enum mCc_validation_status_type
mCc_validator_check_return_type(struct mCc_symbol_table *symbol_table,
                                void *validator_input)
{
	assert(symbol_table);
	assert(validator_input);
	// avoid unused-warning :D
	log_debug("No need to look at symbol-table with scope %d",
	          symbol_table->scope_level);

	struct mCc_ast_function_def *function_def =
	    (struct mCc_ast_function_def *)validator_input;

	enum mCc_ast_data_type return_type = function_def->return_type;
	struct mCc_ast_statement *return_statement =
	    find_return_statement(function_def);

	if (return_type == MCC_AST_DATA_TYPE_VOID) {
		// if no statement or an empty return statement => valid
		if (!return_statement || !return_statement->expression) {
			return MCC_VALIDATION_STATUS_VALID;
		}
		return MCC_VALIDATION_STATUS_RETURN_ON_VOID;
	} else if (return_statement) {
		return MCC_VALIDATION_STATUS_VALID;
	}

	// no return-statement
	return MCC_VALIDATION_STATUS_NO_RETURN;
}

enum mCc_validation_status_type
mCc_validator_check_signature(struct mCc_symbol_table *symbol_table,
                              void *validator_input)
{

	assert(symbol_table);
	assert(validator_input);

	struct mCc_ast_function_call *function_call =
	    (struct mCc_ast_function_call *)validator_input;

	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(symbol_table, function_call->identifier, false);

	// TODO: use a custom "unknown error"?
	if (!symtab_info) {
		log_error("Not found in symbol-table. This should not happen.");
		return MCC_VALIDATION_STATUS_INVALID_SIGNATURE;
	}

	struct mCc_symtab_parameter_ref *first_param_info =
	    symtab_info->next_parameter;
	struct mCc_ast_expression *first_param = function_call->first_argument;

	// iterate through the end
	while (first_param_info) {
		first_param_info = first_param_info->next_parameter;
		if (!first_param_info) {
			return MCC_VALIDATION_STATUS_INVALID_SIGNATURE;
		}
		first_param = first_param->next_expr;
	}

	return first_param ? MCC_VALIDATION_STATUS_INVALID_SIGNATURE
	                   : MCC_VALIDATION_STATUS_VALID;
}
