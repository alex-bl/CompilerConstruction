#ifndef MCC_ERROR_PRINTER_H
#define MCC_ERROR_PRINTER_H

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mCc_error_print_cb)(char *error_buffer, size_t size, void *data);

struct mCc_error_print_holder {
	mCc_error_print_cb no_def_printer;
	mCc_error_print_cb not_unique_printer;
	mCc_error_print_cb no_return_printer;
	mCc_error_print_cb return_on_void_printer;
	mCc_error_print_cb no_main_printer;
	mCc_error_print_cb invalid_signature_printer;
	mCc_error_print_cb inconsistent_type_printer;

	mCc_error_print_cb invalid_type_array_printer;
	mCc_error_print_cb invalid_type_if_cond_printer;
	mCc_error_print_cb invalid_type_loop_cond_printer;
	mCc_error_print_cb invalid_type_param_printer;
	mCc_error_print_cb invalid_type_return_printer;
};

struct mCc_error_print_holder mCc_validator_setup_error_printer_holder();

void mCc_validator_print_error_no_def(char *error_buffer, size_t size,
                                      void *data);
void mCc_validator_print_error_not_unique(char *error_buffer, size_t size,
                                          void *data);
void mCc_validator_print_error_no_return(char *error_buffer, size_t size,
                                         void *data);
void mCc_validator_print_error_return_on_void(char *error_buffer, size_t size,
                                              void *data);
void mCc_validator_print_error_no_main(char *error_buffer, size_t size,
                                       void *data);
void mCc_validator_print_error_invalid_signature(char *error_buffer,
                                                 size_t size, void *data);
void mCc_validator_print_error_inconsistent_type(char *error_buffer,
                                                 size_t size, void *data);

void mCc_validator_print_error_invalid_type_array(char *error_buffer,
                                                  size_t size, void *data);

void mCc_validator_print_error_invalid_type_if(char *error_buffer, size_t size,
                                               void *data);

void mCc_validator_print_error_invalid_type_loop(char *error_buffer,
                                                 size_t size, void *data);

void mCc_validator_print_error_invalid_type_param(char *error_buffer,
                                                  size_t size, void *data);

void mCc_validator_print_error_invalid_type_return(char *error_buffer,
                                                   size_t size, void *data);

#ifdef __cplusplus
}
#endif

#endif
