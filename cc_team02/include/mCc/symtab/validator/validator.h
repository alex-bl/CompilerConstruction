#ifndef MCC_VALIDATOR_H
#define MCC_VALIDATOR_H

#include <stdio.h>

#include "config.h"
#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/symtab_types.h"
#include "mCc/symtab/validator/validation_status.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: add implementation!

struct mCc_validation_status_result {
	enum mCc_validation_status_type validation_status;
	char *error_msg;
	struct mCc_validation_status_result *next;
};

/**
 * Create a new validation-status
 *
 * @param validation_status
 * @param error_msg
 * @return
 */
struct mCc_validation_status_result *mCc_validator_new_validation_result(
    enum mCc_validation_status_type validation_status, char *error_msg);

/**
 * Append an error to an existing error-status (is linked-list)
 *
 * @param parent
 * @param to_append
 */
void mCc_validator_append_semantic_error(
    struct mCc_validation_status_result *target,
    struct mCc_validation_status_result *to_append);

/**
 * Frees the whole error-report
 *
 * @param first_result
 * 		The first node.
 */
void mCc_validator_delete_validation_result(
    struct mCc_validation_status_result *first_result);

#ifdef __cplusplus
}
#endif

#endif
