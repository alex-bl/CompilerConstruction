#include "mCc/symtab/validator/validator.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "log.h"

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
	assert(to_append);

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
	// iterate through list
	while (next_validation_result) {
		fprintf(out, "Error %d: %s\n", i, next_validation_result->error_msg);
		next_validation_result = next_validation_result->next;
		i++;
	}
}
