#include "mCc/symtab/validator/error_printer.h"
#include "mCc/general/print_helper.h"
#include <assert.h>
#include <stdio.h>

static int get_expected_arg_count(struct mCc_ast_identifier *identifier)
{
	assert(identifier);
	assert(identifier->symtab_info->next_parameter);

	// is a function-identifier
	struct mCc_symtab_parameter_ref *next_param =
	    identifier->symtab_info->next_parameter;
	int counter = 0;

	while (next_param) {
		counter++;
		next_param = next_param->next_parameter;
	}
	return counter;
}

static int get_actual_arg_count(struct mCc_ast_function_call *function_call)
{
	assert(function_call);
	struct mCc_ast_expression *next_expr = function_call->first_argument;
	int counter = 0;

	while (next_expr) {
		counter++;
		next_expr = next_expr->next_expr;
	}
	return counter;
}

void mCc_validator_print_error_no_def(char *error_buffer, size_t size,
                                      void *data)
{
	struct mCc_ast_identifier *identifier = (struct mCc_ast_identifier *)data;
	snprintf(error_buffer, size, "Implicit declaration of '%s'",
	         identifier->identifier_name);
}

void mCc_validator_print_error_not_unique(char *error_buffer, size_t size,
                                          void *data)
{
	struct mCc_ast_identifier *identifier = (struct mCc_ast_identifier *)data;
	snprintf(error_buffer, size, "'%s' already defined",
	         identifier->identifier_name);
}

void mCc_validator_print_error_no_return(char *error_buffer, size_t size,
                                         void *data)
{
	struct mCc_ast_function_def *function_def =
	    (struct mCc_ast_function_def *)data;
	snprintf(error_buffer, size,
	         "No return for function '%s' (non-void-function)",
	         function_def->identifier->identifier_name);
}

void mCc_validator_print_error_return_on_void(char *error_buffer, size_t size,
                                              void *data)
{
	struct mCc_ast_function_def *function_def =
	    (struct mCc_ast_function_def *)data;
	snprintf(error_buffer, size,
	         "Function '%s': not expected return on void-function",
	         function_def->identifier->identifier_name);
}

void mCc_validator_print_error_no_main(char *error_buffer, size_t size,
                                       void *data)
{
	snprintf(error_buffer, size, "Function 'main' expected but not found");
}

void mCc_validator_print_error_invalid_signature(char *error_buffer,
                                                 size_t size, void *data)
{
	struct mCc_ast_function_call *function_call =
	    (struct mCc_ast_function_call *)data;
	int expected_arg_counter =
	    get_expected_arg_count(function_call->identifier);
	int actual_arg_counter = get_actual_arg_count(function_call);
	snprintf(error_buffer, size,
	         "Function '%s': Expected %d argument(s), but have %d",
	         function_call->identifier->identifier_name, expected_arg_counter,
	         actual_arg_counter);
}

void mCc_validator_print_error_inconsistent_type(char *error_buffer,
                                                 size_t size, void *data)
{
	struct mCc_ast_assignment *assignment = (struct mCc_ast_assignment *)data;
	// info is available at this stage
	snprintf(error_buffer, size,
	         "Invalid type for assignment '%s': Expected '%s'",
	         assignment->identifier->identifier_name,
	         print_data_type(assignment->identifier->symtab_info->data_type));
}

struct mCc_error_print_holder mCc_validator_setup_error_printer_holder()
{
	return (struct mCc_error_print_holder){
		.no_def_printer = mCc_validator_print_error_no_def,
		.not_unique_printer = mCc_validator_print_error_not_unique,
		.no_return_printer = mCc_validator_print_error_no_return,
		.return_on_void_printer = mCc_validator_print_error_return_on_void,
		.no_main_printer = mCc_validator_print_error_no_main,
		.invalid_signature_printer =
		    mCc_validator_print_error_invalid_signature,
		.inconsistent_type_printer = mCc_validator_print_error_inconsistent_type
	};
}
