#include "mCc/symtab/validator/validator.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"

struct mCc_validation_status_result *mCc_validator_new_validation_result(
    enum mCc_validation_status_type validation_status, const char *error_msg)
{
	struct mCc_validation_status_result *validation_result =
	    malloc(sizeof(*validation_result));
	if (!validation_result) {
		log_error("Malloc failed: Could not construct a validation-result");
		return NULL;
	}
	validation_result->validation_status = validation_status;
	validation_result->error_msg = error_msg;
	validation_result->next = NULL;

	return validation_result;
}

void mCc_validator_append_semantic_error(
    struct mCc_validation_status_result *target,
    struct mCc_validation_status_result *to_append)
{
	assert(target);
	if (!to_append) {
		log_debug("No semantic-error to append");
		return;
	}

	struct mCc_validation_status_result *next_validation_result = target;
	// iterate to the end
	while (next_validation_result) {
		next_validation_result = next_validation_result->next;
	}
	// then append
	next_validation_result->next = to_append;
}

// maybe some advanced logic here if validator-result is expanded
static void
free_validator_result_simple(struct mCc_validation_status_result *result)
{
	assert(result);
	free(result->error_msg);
	free(result);
}

void mCc_validator_delete_validation_result(
    struct mCc_validation_status_result *first_result)
{
	assert(first_result);
	struct mCc_validation_status_result *next_validation_result = first_result;

	while (next_validation_result) {
		struct mCc_validation_status_result *tmp = next_validation_result;
		next_validation_result = next_validation_result->next;
		free_validator_result_simple(tmp);
	}
}

void mCc_validator_print_validation_result(
    struct mCc_validation_status_result *first_result, FILE *out)
{
	assert(first_result);
	assert(out);

	// no errors, so don't print anything
	if (first_result->validation_status == MCC_VALIDATION_STATUS_VALID) {
		return;
	}

	struct mCc_validation_status_result *next_validation_result = first_result;
	int i = 0;
	fprintf(out, "Validation-process exited with errors: \n");
	// iterate through list
	while (next_validation_result) {
		fprintf(out, "Error %d: %s\n", i, next_validation_result->error_msg);
		next_validation_result = next_validation_result->next;
		i++;
	}
}

char *
mCc_validator_create_error_msg(enum mCc_validation_status_type status_code,
                               struct mCc_ast_identifier *identifier,
                               size_t size)
{
	char *error_msg = malloc(size);
	if (!error_msg) {
		log_error("Malloc failed: Could not build error-msg.");
		return NULL;
	}
	switch (status_code) {
	case MCC_VALIDATION_STATUS_NO_DEF:
		snprintf(error_msg, size, "Implicit declaration of '%s'",
		         identifier->identifier_name);
		break;
	case MCC_VALIDATION_STATUS_NOT_UNIQUE:
		snprintf(error_msg, size, "'%s' already defined",
		         identifier->identifier_name);
		break;
		/*TODO*/
	case MCC_VALIDATION_STATUS_VALID:
	case MCC_VALIDATION_STATUS_INVALID_TYPE:
	case MCC_VALIDATION_STATUS_INVALID_SIGNATURE:
	case MCC_VALIDATION_STATUS_NO_MAIN: snprintf(error_msg, size, " "); break;
	}
	return error_msg;
}

struct mCc_validation_status_result *
mCc_validator_create_error_status(enum mCc_validation_status_type status_code,
                                  struct mCc_ast_identifier *identifier)
{

	if (status_code == MCC_VALIDATION_STATUS_VALID) {
		log_debug("Statuscode 'MCC_VALIDATION_STATUS_VALID' does not create a "
		          "status-struct");
		return NULL;
	}

	char *error_msg = mCc_validator_create_error_msg(status_code, identifier,
	                                                 ERROR_MSG_BUF_SIZE);
	return mCc_validator_new_validation_result(status_code, error_msg);
}

void mCc_validor_store_result_to_handler(
    struct mCc_symtab_and_validation_holder *info_holder,
    struct mCc_validation_status_result *status_result)
{

	if (!info_holder->first_semantic_error) {
		log_debug("First error appended to handler");
		info_holder->first_semantic_error = status_result;
	} else {
		mCc_validator_append_semantic_error(info_holder->first_semantic_error,
		                                    status_result);
		log_debug("Error appended to handler");
	}
}
