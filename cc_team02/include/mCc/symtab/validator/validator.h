#ifndef MCC_VALIDATOR_H
#define MCC_VALIDATOR_H

#ifdef __cplusplus
extern "C" {
#endif

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

struct mCc_validation_status_result *mCc_validator_new_validation_result(
    enum mCc_validation_status_type validation_status, const char *error_msg);

#ifdef __cplusplus
}
#endif

#endif
