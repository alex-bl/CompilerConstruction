#include "symtab_handle_program.h"

#include <assert.h>
#include <stdbool.h>
#include <string.h>

#include "ast_program.h"
#include "config.h"
#include "log.h"
#include "symbol_table.h"
#include "validator.h"

static void
handle_function_def(struct mCc_ast_function_def *function_def,
                    struct mCc_symtab_and_validation_holder *info_holder)
{
	struct mCc_ast_identifier *identifier = function_def->identifier;
	int scope_level = info_holder->symbol_table->scope_level;
	struct mCc_symbol_table_node *symtab_info =
	    mCc_symtab_lookup(info_holder->symbol_table, identifier, true);

	// already existing
	if (symtab_info) {
		symtab_info->already_defined = true;
		log_debug("Identifier '%s' already defined",
		          identifier->identifier_name);
		// other error handling done at identifier-level
	} else {
		mCc_symtab_insert_function_def_node(info_holder->symbol_table,
		                                    function_def);
		// linking is done at function-level
		log_debug("New function declaration inserted to symbol-table scope %d",
		          scope_level);
	}
}

static void append_error_to_pgrogram(struct mCc_ast_program *program,
                                     struct mCc_validation_status_result *error)
{
	if (!program->semantic_error) {
		program->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(program->semantic_error, error);
	}
}

static struct mCc_ast_function_def *find_main(struct mCc_ast_program *prog)
{
	assert(prog);

	struct mCc_ast_function_def *next_function_def = prog->first_function_def;

	while (next_function_def) {
		if (strcmp(next_function_def->identifier->identifier_name, "main") ==
		    0) {
			return next_function_def;
		}
		next_function_def = next_function_def->next_function_def;
	}
	return NULL;
}

static bool has_valid_signature(struct mCc_ast_function_def *main_function)
{
	return main_function->return_type == MCC_AST_DATA_TYPE_VOID &&
	       main_function->first_parameter == NULL;
}

static void
handle_main_presence(struct mCc_ast_program *program,
                     struct mCc_symtab_and_validation_holder *info_holder)
{
	assert(program);

	struct mCc_ast_function_def *main_function = find_main(program);

	char error_msg[ERROR_MSG_BUF_SIZE];
	enum mCc_validation_status_type validation_error;
	if (!main_function) {
		snprintf(error_msg, ERROR_MSG_BUF_SIZE,
		         "Expected function 'main' but not found");
		validation_error = MCC_VALIDATION_STATUS_NO_MAIN;
	} else if (!has_valid_signature(main_function)) {
		snprintf(error_msg, ERROR_MSG_BUF_SIZE,
		         "Invalid signature for function 'main': Expected 'void "
		         "main(void)'");
		validation_error = MCC_VALIDATION_STATUS_INVALID_SIGNATURE;
	} else {
		return;
	}

	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        validation_error, strndup(error_msg, strlen(error_msg)));
	append_error_to_pgrogram(program, error);
	info_holder->error_count++;
}

void mCc_symtab_handle_program_post_order(struct mCc_ast_program *program,
                                          void *data)
{
	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	// do the main-check
	handle_main_presence(program, info_holder);
}

void mCc_symtab_handle_program_pre_order(struct mCc_ast_program *program,
                                         void *data)
{
	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	struct mCc_ast_function_def *next_function_def =
	    program->first_function_def;

	while (next_function_def) {
		// make sure that function-identifiers are in symtab at this stage
		handle_function_def(next_function_def, info_holder);

		next_function_def = next_function_def->next_function_def;
	}
}
