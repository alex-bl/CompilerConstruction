#ifndef MCC_VALIDATOR_H
#define MCC_VALIDATOR_H

#include <stdio.h>

#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/symtab_types.h"

#define ERROR_MSG_BUF_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif

// TODO: add implementation!

enum mCc_validation_status_type {
	MCC_VALIDATION_STATUS_VALID,
	MCC_VALIDATION_STATUS_INVALID_TYPE,
	MCC_VALIDATION_STATUS_NO_DEF,
	MCC_VALIDATION_STATUS_NOT_UNIQUE,
	MCC_VALIDATION_STATUS_INVALID_SIGNATURE,
	MCC_VALIDATION_STATUS_NO_MAIN,
	MCC_VALIDATION_STATUS_NO_RETURN,
	MCC_VALIDATION_STATUS_RETURN_ON_VOID
};

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

/**
 * Prints all detected semantic errors
 *
 * @param first_result
 * 		The entry-point
 * @param out
 * 		The output-stream
 */
void mCc_validator_print_validation_result(
    struct mCc_validation_status_result *first_result, FILE *out);

/**
 *
 * @param status_code
 * @param data
 * @param size
 * @return
 */
char *
mCc_validator_create_error_msg(enum mCc_validation_status_type status_code,
                               void *data, size_t size);

/**
 *
 * @param status_code
 * @param data
 * @return
 */
struct mCc_validation_status_result *
mCc_validator_create_error_status(enum mCc_validation_status_type status_code,
                                  void *data);

/**
 *
 * @param info_holder
 * @param status_result
 */
void mCc_validor_store_result_to_handler(
    struct mCc_symtab_and_validation_holder *info_holder,
    struct mCc_validation_status_result *status_result);

/**
 *
 * @param validator_function
 * @param symbol_table
 * @param validator_input
 * @param info_holder
 * @param success_handler_data
 * @return
 */
enum mCc_validation_status_type
mCc_process_validation(enum mCc_validation_status_type(validator_function)(
                           struct mCc_symbol_table *, void *),
                       void(success_handler(struct mCc_symbol_table *, void *)),
                       struct mCc_symbol_table *symbol_table,
                       void *validator_input,
                       struct mCc_symtab_and_validation_holder *info_holder,
                       void *success_handler_data);

#ifdef __cplusplus
}
#endif

#endif
