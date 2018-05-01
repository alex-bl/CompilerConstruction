#include "mCc/symtab/validator/validator.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "log.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/error_printer.h"

struct mCc_validation_status_result *mCc_validator_new_validation_result(
    enum mCc_validation_status_type validation_status, char *error_msg)
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
	while (next_validation_result->next) {
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
                               void *data, size_t size)
{
	struct mCc_error_print_holder error_printers =
	    mCc_validator_setup_error_printer_holder();
	char *error_msg = malloc(size);
	if (!error_msg) {
		log_error("Malloc failed: Could not build error-msg.");
		return NULL;
	}
	switch (status_code) {
	case MCC_VALIDATION_STATUS_NO_DEF:
		error_printers.no_def_printer(error_msg, size, data);
		break;
	case MCC_VALIDATION_STATUS_NOT_UNIQUE:
		error_printers.not_unique_printer(error_msg, size, data);
		break;
	case MCC_VALIDATION_STATUS_NO_RETURN:
		error_printers.no_return_printer(error_msg, size, data);
		break;
	case MCC_VALIDATION_STATUS_RETURN_ON_VOID:
		error_printers.return_on_void_printer(error_msg, size, data);
		break;
	case MCC_VALIDATION_STATUS_NO_MAIN:
		error_printers.no_main_printer(error_msg, size, data);
		break;
	case MCC_VALIDATION_STATUS_INVALID_SIGNATURE:
		error_printers.invalid_signature_printer(error_msg, size, data);
		break;
	case MCC_VALIDATION_STATUS_INVALID_TYPE:
		error_printers.inconsistent_type_printer(error_msg, size, data);
		break;
		/*TODO*/
	case MCC_VALIDATION_STATUS_VALID:
		snprintf(error_msg, size, " ");
		break;
	}
	return error_msg;
}

struct mCc_validation_status_result *
mCc_validator_create_error_status(enum mCc_validation_status_type status_code,
                                  void *data)
{

	if (status_code == MCC_VALIDATION_STATUS_VALID) {
		log_debug("Statuscode 'MCC_VALIDATION_STATUS_VALID' does not create a "
		          "status-struct");
		return NULL;
	}

	char *error_msg =
	    mCc_validator_create_error_msg(status_code, data, ERROR_MSG_BUF_SIZE);
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

enum mCc_validation_status_type
mCc_process_validation(enum mCc_validation_status_type(validator_function)(
                           struct mCc_symbol_table *, void *),
                       void(success_handler(struct mCc_symbol_table *, void *)),
                       struct mCc_symbol_table *symbol_table,
                       void *validator_input,
                       struct mCc_symtab_and_validation_holder *info_holder,
                       void *success_handler_data)
{
	// function-defs are stored at symboltable with scope lvl 0
	enum mCc_validation_status_type check_result =
	    validator_function(symbol_table, validator_input);
	// if valid and success-handler defined
	if (check_result == MCC_VALIDATION_STATUS_VALID && success_handler) {
		// function-defs are always inserted at scope-level 0 => so parent
		success_handler(symbol_table, success_handler_data);
	} else if (check_result != MCC_VALIDATION_STATUS_VALID &&
	           check_result != MCC_VALIDATION_STATUS_ERROR_REPORTED_LATER) {
		struct mCc_validation_status_result *status_result =
		    mCc_validator_create_error_status(check_result, validator_input);
		mCc_validor_store_result_to_handler(info_holder, status_result);
	}
	return check_result;
}
