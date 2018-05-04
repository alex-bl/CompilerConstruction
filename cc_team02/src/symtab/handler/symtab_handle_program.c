#include "mCc/symtab/handler/symtab_handle_program.h"

#include <assert.h>
#include <string.h>

#include "config.h"
#include "mCc/ast/basis/ast_program.h"
#include "mCc/symtab/validator/validator.h"

static void append_error_to_pgrogram(struct mCc_ast_program *program,
                                     struct mCc_validation_status_result *error)
{
	if (!program->semantic_error) {
		program->semantic_error = error;
	} else {
		mCc_validator_append_semantic_error(program->semantic_error, error);
	}
}

static void handle_main_presence(struct mCc_ast_program *program)
{
	assert(program);

	struct mCc_ast_function_def *next_function_def =
	    program->first_function_def;

	while (next_function_def) {
		if (strcmp(next_function_def->identifier->identifier_name, "main") ==
		    0) {
			return;
		}
		next_function_def = next_function_def->next_function_def;
	}

	char error_msg[ERROR_MSG_BUF_SIZE];
	snprintf(error_msg, ERROR_MSG_BUF_SIZE,
	         "Expected 'main' function but not found");
	struct mCc_validation_status_result *error =
	    mCc_validator_new_validation_result(
	        MCC_VALIDATION_STATUS_NO_MAIN,
	        strndup(error_msg, strlen(error_msg)));
	append_error_to_pgrogram(program, error);
}

void mCc_symtab_handle_program_post_order(struct mCc_ast_program *program,
                                          void *data)
{
	// do the main-check
	handle_main_presence(program);
}
