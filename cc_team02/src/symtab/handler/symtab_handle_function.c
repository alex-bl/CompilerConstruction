#include "mCc/symtab/handler/symtab_handle_function.h"

#include <assert.h>
#include <stddef.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/base_validator.h"
#include "mCc/symtab/validator/typecheck.h"
#include "mCc/symtab/validator/validation_status.h"

/*
 * TODO:
 * - check for main
 * - check if has a return
 */

static void
append_error_to_function_def(struct mCc_ast_function_def *function_def,
                             struct mCc_validation_status_result *error)
{
	if (!function_def->semantic_error) {
		function_def->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(function_def->semantic_error,
		                                    error);
	}
}

static void
handle_function_def(struct mCc_symtab_and_validation_holder *info_holder,
                    struct mCc_ast_function_def *function_def)
{
	struct mCc_ast_identifier *identifier = function_def->identifier;
	int scope_level = info_holder->symbol_table->scope_level;
	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(info_holder->symbol_table->parent, identifier, true);
	bool error_occurred = false;

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
                                              void *data)
{
	assert(def);
	assert(data);

	struct mCc_ast_identifier *identifier = def->identifier;

	log_debug("Processing function-def '%s'...",
	          def->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	handle_function_def(info_holder, def);
	// TODO: integrate these
	//	// check for return-types
	//	mCc_process_validation_without_call_back(mCc_validator_check_return_type,
	//	                                         info_holder->symbol_table->parent,
	//	                                         def, info_holder);

	log_debug("Function-def checking completed");
}

// TODO: refactor => duplicate to symtab_handle_statement except return
static void handle_expected_type(struct mCc_ast_function_def *def,
                                 struct mCc_ast_statement *statement,
                                 enum mCc_ast_data_type expected,
                                 enum mCc_ast_data_type actual)
{
	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, "Incompatible types: Expected '%s' but have %s",
	         ERROR_MSG_BUF_SIZE, print_data_type(expected),
	         print_data_type(actual));
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_INVALID_RETURN, error_msg);
	append_error_to_function_def(def, error);
}

// check for return-type
void mCc_symtab_handle_function_def_post_order(struct mCc_ast_function_def *def,
                                               void *data)
{
	assert(def);
	assert(data);

	struct mCc_ast_identifier *identifier = def->identifier;

	log_debug("Processing type-checking on function return '%s'...",
	          def->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	// error detected previously
	if (def->semantic_error) {
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
		if (return_type != MCC_AST_DATA_TYPE_INCONSISTENT &&
		    return_type != MCC_AST_DATA_TYPE_UNKNOWN &&
		    return_type != function_type) {
			handle_expected_type(def, return_statement, function_type,
			                     return_type);
		}
	}
	log_debug("Function-def return-type-checking completed");
}



void mCc_symtab_handle_function_call(struct mCc_ast_function_call *call,
                                     void *data)
{
	assert(call);
	assert(data);

	log_debug("Checking function-call-signature '%s'...",
	          call->identifier->identifier_name);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_symbol_table_node *identifier_info =
	    mCc_symtab_lookup(info_holder->symbol_table, call->identifier, false);
	// identifier-checker are usually called after function_calls
	if (!identifier_info) {
		log_debug("Function '%s' not found. Error will be reported later",
		          call->identifier->identifier_name);
	} else {
		/*
		 * this info is needed here to build the error-message
		 * it is just temporary because the subsequent identifier-handler will
		 * overwrite it (memcpy)
		 */
		call->identifier->symtab_info = identifier_info;

		mCc_process_validation_without_call_back(mCc_validator_check_signature,
		                                         info_holder->symbol_table,
		                                         call, info_holder);
	}
	log_debug("Signature checking completed");
}

void mCc_symtab_handle_function_call_post_order(
    struct mCc_ast_function_call *call, void *data)
{
	assert(call);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_identifier *identifier = call->identifier;

	if (!call->identifier->symtab_info) {
		log_debug("No symtab info associated with '%s'. It does not exist. No "
		          "check required",
		          identifier->identifier_name);
	} else {
		log_debug("Type checking on function-call-signature '%s'...",
		          identifier->identifier_name);

		mCc_process_validation_without_call_back(
		    mCc_typecheck_validate_function_call, info_holder->symbol_table,
		    call, info_holder);
		log_debug("Type checking completed");
	}
}
