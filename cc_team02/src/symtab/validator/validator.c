#include "mCc/symtab/validator/validator.h"

#include <stddef.h>

struct mCc_validation_status_result *mCc_validator_new_validation_result(
    enum mCc_validation_status_type validation_status, const char *error_msg)
{
	/*
	 * TODO:
	 * - creator
	 */
	return NULL;
}

void mCc_validator_append_semantic_error(
    struct mCc_validation_status_result *target,
    struct mCc_validation_status_result *to_append)
{
	/*
	 * TODO:
	 * - iterate until next is null + append
	 */
}
