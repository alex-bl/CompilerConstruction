#ifndef MCC_VALIDATOR_H
#define MCC_VALIDATOR_H

#ifdef __cplusplus
extern "C" {
#endif

//TODO: add implementation!

enum mCc_validation_status_type {
	MCC_VALIDATION_STATUS_VALID,
	MCC_VALIDATION_STATUS_INVALID_TYPE,
	MCC_VALIDATION_STATUS_NO_DEF,
	MCC_VALIDATION_STATUS_NOT_UNIQUE,
	MCC_VALIDATION_STATUS_INVALID_SIGNATURE,
	MCC_VALIDATION_STATUS_NO_MAIN
};

struct mCc_validation_status_result {
	enum mCc_validation_status_type validation_status;
	const char *error_msg;
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
    enum mCc_validation_status_type validation_status, const char *error_msg);

/**
 * Append an error to an existing error-status (is linked-list)
 *
 * @param parent
 * @param to_append
 */
void *mCc_validator_append_semantic_error(
    struct mCc_validation_status_result *target,
    struct mCc_validation_status_result *to_append);

#ifdef __cplusplus
}
#endif

#endif
