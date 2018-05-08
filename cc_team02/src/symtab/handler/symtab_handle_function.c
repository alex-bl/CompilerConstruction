#include "mCc/symtab/handler/symtab_handle_function.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "log.h"
#include "mCc/general/print_helper.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validation_status.h"
#include "mCc/symtab/validator/validator.h"
#include "mCc/symtab/validator/validator_helper.h"

#include "config.h"

/*
 * TODO:
 * - check for main
 * - check if has a return
 */
// is done preorder => needs symtab_info
static int get_expected_arg_count(struct mCc_symbol_table_node *symtab_info) {
	assert(symtab_info);

	// is a function-identifier
	struct mCc_symtab_parameter_ref *next_param = symtab_info->next_parameter;
	int counter = 0;

	while (next_param) {
		counter++;
		next_param = next_param->next_parameter;
	}
	return counter;
}

static int get_actual_arg_count(struct mCc_ast_function_call *function_call) {
	assert(function_call);
	struct mCc_ast_expression *next_expr = function_call->first_argument;
	int counter = 0;

	while (next_expr) {
		counter++;
		next_expr = next_expr->next_expr;
	}
	return counter;
}

static void append_error_to_function_def(
		struct mCc_ast_function_def *function_def,
		struct mCc_validation_status_result *error) {
	if (!function_def->semantic_error) {
		function_def->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(function_def->semantic_error,
				error);
	}
}

static void append_error_to_function_call(
		struct mCc_ast_function_call *function_call,
		struct mCc_validation_status_result *error) {
	if (!function_call->semantic_error) {
		function_call->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(function_call->semantic_error,
				error);
	}
}

static void handle_invalid_param_count(struct mCc_ast_function_call *call,
		int expected, int actual,
		struct mCc_symtab_and_validation_holder *info_holder) {

	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
			"Function '%s': Expected %d argument(s), but have %d",
			call->identifier->identifier_name, expected, actual);
	struct mCc_validation_status_result *error =
			mCc_validator_new_validation_result(
					MCC_VALIDATION_STATUS_INVALID_SIGNATURE,
					strndup(error_msg, strlen(error_msg)));

	append_error_to_function_call(call, error);
	info_holder->error_occurred = true;
}

static void handle_function_def(struct mCc_ast_function_def *function_def,
		struct mCc_symtab_and_validation_holder *info_holder) {
	struct mCc_ast_identifier *identifier = function_def->identifier;
	int scope_level = info_holder->symbol_table->scope_level;
	struct mCc_symbol_table_node *symtab_info = mCc_symtab_lookup(
			info_holder->symbol_table->parent, identifier, true);

	// already existing
	if (symtab_info) {
		symtab_info->already_defined = true;
		log_debug("Identifier '%s' already defined",
				identifier->identifier_name);
		// other error handling done at identifier-level
	} else {
		mCc_symtab_insert_function_def_node(info_holder->symbol_table->parent,
				function_def);
		log_debug("New function declaration inserted to symbol-table scope %d",
				scope_level);
	}
}
// do this preorder
void mCc_symtab_handle_function_def_pre_order(struct mCc_ast_function_def *def,
		void *data) {
	assert(def);
	assert(data);

	log_debug("Processing function-def '%s'...",
			def->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
			(struct mCc_symtab_and_validation_holder *) data;

	handle_function_def(def, info_holder);

	log_debug("Function-def checking completed");
}

// TODO: refactor => duplicate to symtab_handle_statement except return
static void handle_expected_type(struct mCc_ast_function_def *def,
		enum mCc_ast_data_type expected, enum mCc_ast_data_type actual,
		struct mCc_symtab_and_validation_holder *info_holder) {
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
			"Incompatible return type: Expected '%s' but have '%s'",
			print_data_type(expected), print_data_type(actual));
	struct mCc_validation_status_result *error =
			mCc_validator_new_validation_result(
					MCC_VALIDATION_STATUS_INVALID_RETURN,
					strndup(error_msg, strlen(error_msg)));
	append_error_to_function_def(def, error);
	info_holder->error_occurred = true;
}

static void handle_expected_type_function_call(
		struct mCc_ast_function_call *call, enum mCc_ast_data_type expected,
		enum mCc_ast_data_type actual, int arg_nr,
		struct mCc_symtab_and_validation_holder *info_holder) {
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
			"Incompatible types at argument %d: Expected '%s' but have '%s'",
			arg_nr, print_data_type(expected), print_data_type(actual));
	struct mCc_validation_status_result *error =
			mCc_validator_new_validation_result(
					MCC_VALIDATION_STATUS_INVALID_PARAMETER,
					strndup(error_msg, strlen(error_msg)));
	append_error_to_function_call(call, error);
	info_holder->error_occurred = true;
}

static void handle_unknown_inconsistent_type(struct mCc_ast_function_call *call,
		int arg_nr, struct mCc_symtab_and_validation_holder *info_holder) {
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE, "Inconsistent type at argument %d",
			arg_nr);
	struct mCc_validation_status_result *error =
			mCc_validator_new_validation_result(
					MCC_VALIDATION_STATUS_INVALID_PARAMETER,
					strndup(error_msg, strlen(error_msg)));
	append_error_to_function_call(call, error);
	info_holder->error_occurred = true;
}

// check for return-type
void mCc_symtab_handle_function_def_post_order(struct mCc_ast_function_def *def,
		void *data) {
	assert(def);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
			(struct mCc_symtab_and_validation_holder *) data;

	struct mCc_ast_identifier *identifier = def->identifier;

	log_debug("Processing type-checking on function return '%s'...",
			def->identifier->identifier_name);

	// error detected previously
	if (def->semantic_error || def->identifier->semantic_error) {
		log_debug("Error already detected. Do not check return type");
	} else {
		struct mCc_ast_statement *return_statement =
				mCc_validator_find_return_statement(def);
		enum mCc_ast_data_type function_type =
				identifier->symtab_info->data_type;

		if (!return_statement && function_type == MCC_AST_DATA_TYPE_VOID) {
			// everything fine
			return;
		}

		enum mCc_ast_data_type return_type =
				return_statement->return_expression->data_type;
		// incompatible types
		if (return_type != MCC_AST_DATA_TYPE_INCONSISTENT
				&& return_type != MCC_AST_DATA_TYPE_UNKNOWN
				&& return_type != function_type) {
			handle_expected_type(def, function_type, return_type, info_holder);
		}
	}
	log_debug("Function-def return-type-checking completed");
}

void mCc_symtab_handle_function_call_pre_order(
		struct mCc_ast_function_call *call, void *data) {
	assert(call);
	assert(data);

	log_debug("Checking function-call-signature '%s'...",
			call->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
			(struct mCc_symtab_and_validation_holder *) data;

	struct mCc_symbol_table_node *identifier_info = mCc_symtab_lookup(
			info_holder->symbol_table, call->identifier, false);

	// Reported later
	if (identifier_info && !identifier_info->already_defined) {
		int expected_nr_args = get_expected_arg_count(identifier_info);
		int actual_nr_args = get_actual_arg_count(call);

		if (expected_nr_args != actual_nr_args) {
			handle_invalid_param_count(call, expected_nr_args, actual_nr_args,
					info_holder);
		}
	}

	log_debug("Signature checking completed");
}

/*
 * TODO:
 * - check argument-types => post-order
 */
void mCc_symtab_handle_function_call_post_order(
		struct mCc_ast_function_call *call, void *data) {
	assert(call);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
			(struct mCc_symtab_and_validation_holder *) data;

	struct mCc_ast_identifier *identifier = call->identifier;
	struct mCc_symbol_table_node *symtab_info = identifier->symtab_info;

	if (!symtab_info) {
		log_debug("No symtab info associated with '%s'. It does not exist. No "
				"check required", identifier->identifier_name);
	} else if (call->semantic_error) {
		log_debug("Function '%s' has already errors. Skipping parameter check",
				identifier->identifier_name);
	} else {
		// have the same size dueto previous checks
		struct mCc_symtab_parameter_ref *next_param =
				symtab_info->next_parameter;
		struct mCc_ast_expression *next_argument = call->first_argument;
		int arg_counter = 0;

		log_debug("Type checking on function-call-signature '%s'...",
				identifier->identifier_name);

		while (next_param) {

			enum mCc_ast_data_type arg_type = next_argument->data_type;
			enum mCc_ast_data_type def_type =
					next_param->identifier->symtab_info->data_type;

			// unknown or inconsistent
			if (arg_type == MCC_AST_DATA_TYPE_UNKNOWN
					|| arg_type == MCC_AST_DATA_TYPE_INCONSISTENT) {
				handle_unknown_inconsistent_type(call, arg_counter,
						info_holder);
			} // different than expected
			else if (arg_type != def_type) {
				handle_expected_type_function_call(call, def_type, arg_type,
						arg_counter, info_holder);
			}
			arg_counter++;
			next_param = next_param->next_parameter;
			next_argument = next_argument->next_expr;
		}
		log_debug("Type checking completed");
	}
}
