#ifndef MCC_ASSEMBLY_GENERATOR_H
#define MCC_ASSEMBLY_GENERATOR_H

#include <stdio.h>

#include "assembly_data.h"
#include "basic_tac.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mCc_generate_assembly_cb)(FILE *, struct mCc_assembly_data *data,
                                         struct mCc_tac_element *);

struct mCc_assembly_generator {
	FILE *out;
	struct mCc_assembly_data *data;
	// Arithmetics
	mCc_generate_assembly_cb add_int;
	mCc_generate_assembly_cb add_float;
	mCc_generate_assembly_cb sub_int;
	mCc_generate_assembly_cb sub_float;
	mCc_generate_assembly_cb mul_int;
	mCc_generate_assembly_cb mul_float;
	mCc_generate_assembly_cb div_int;
	mCc_generate_assembly_cb div_float;

	// Assignment
	mCc_generate_assembly_cb assign_primitive_int;
	mCc_generate_assembly_cb assign_primitive_float;
	mCc_generate_assembly_cb assign_primitive_bool;
	mCc_generate_assembly_cb assign_primitive_string;

	// Unary-op
	mCc_generate_assembly_cb unary_op_minus_int;
	mCc_generate_assembly_cb unary_op_minus_float;
	mCc_generate_assembly_cb unary_op_negation;

	// Return
	mCc_generate_assembly_cb return_primitive_int;
	mCc_generate_assembly_cb return_primitive_float;
	mCc_generate_assembly_cb return_primitive_bool;
	mCc_generate_assembly_cb return_primitive_string;
	mCc_generate_assembly_cb return_array_int;
	mCc_generate_assembly_cb return_array_float;
	mCc_generate_assembly_cb return_array_bool;
	mCc_generate_assembly_cb return_array_string;

	// Param
	mCc_generate_assembly_cb param_int_primitive;
	mCc_generate_assembly_cb param_float_primitive;
	mCc_generate_assembly_cb param_bool_primitive;
	mCc_generate_assembly_cb param_string_primitive;
	mCc_generate_assembly_cb param_int_array;
	mCc_generate_assembly_cb param_float_array;
	mCc_generate_assembly_cb param_bool_array;
	mCc_generate_assembly_cb param_string_array;

	// Argument
	mCc_generate_assembly_cb argument_int_primitive;
	mCc_generate_assembly_cb argument_float_primitive;
	mCc_generate_assembly_cb argument_bool_primitive;
	mCc_generate_assembly_cb argument_string_primitive;
	mCc_generate_assembly_cb argument_int_array;
	mCc_generate_assembly_cb argument_float_array;
	mCc_generate_assembly_cb argument_bool_array;
	mCc_generate_assembly_cb argument_string_array;


	// Label
	mCc_generate_assembly_cb label_function;
	mCc_generate_assembly_cb label_float;
	mCc_generate_assembly_cb label_string;
	mCc_generate_assembly_cb label_if;
	mCc_generate_assembly_cb label_else;
	mCc_generate_assembly_cb label_while;

	// "Pseudo-labels" aka literal-assignment
	mCc_generate_assembly_cb convert_int_lit;
	mCc_generate_assembly_cb convert_float_lit;
	mCc_generate_assembly_cb convert_bool_lit;
	mCc_generate_assembly_cb convert_string_lit;

	// Jump
	mCc_generate_assembly_cb jump_equals;
	mCc_generate_assembly_cb jump_not_equals;
	mCc_generate_assembly_cb jump_greater;
	mCc_generate_assembly_cb jump_less;
	mCc_generate_assembly_cb jump_greater_equals;
	mCc_generate_assembly_cb jump_less_equals;
	mCc_generate_assembly_cb jump_and;
	mCc_generate_assembly_cb jump_or;

	// Function
	mCc_generate_assembly_cb start_function_def;
	mCc_generate_assembly_cb end_function_def;
	mCc_generate_assembly_cb function_call;

	// Declaration
	mCc_generate_assembly_cb declare_primitive_int;
	mCc_generate_assembly_cb declare_primitive_float;
	mCc_generate_assembly_cb declare_primitive_bool;
	mCc_generate_assembly_cb declare_primitive_string;
	mCc_generate_assembly_cb declare_array_int;
	mCc_generate_assembly_cb declare_array_float;
	mCc_generate_assembly_cb declare_array_bool;
	mCc_generate_assembly_cb declare_array_string;

	// Binary logical ops
	mCc_generate_assembly_cb equals_int;
	mCc_generate_assembly_cb equals_float;
	mCc_generate_assembly_cb equals_bool;
	mCc_generate_assembly_cb not_equals_int;
	mCc_generate_assembly_cb not_equals_float;
	mCc_generate_assembly_cb not_equals_bool;
	mCc_generate_assembly_cb greater_int;
	mCc_generate_assembly_cb greater_float;
	mCc_generate_assembly_cb less_int;
	mCc_generate_assembly_cb less_float;
	mCc_generate_assembly_cb greater_equals_int;
	mCc_generate_assembly_cb greater_equals_float;
	mCc_generate_assembly_cb less_equals_int;
	mCc_generate_assembly_cb less_equals_float;
	mCc_generate_assembly_cb and_op;
	mCc_generate_assembly_cb or_op;
};

void mCc_assembly_generate_tac_elem(struct mCc_assembly_generator gen_cb,
                                    struct mCc_tac_element *tac_elem);
void mCc_assembly_generate(FILE *out, struct mCc_tac_element *first_tac_elem);
struct mCc_assembly_generator
mcc_assembly_gen_setup(FILE *out, struct mCc_assembly_data *data);

#ifdef __cplusplus
}
#endif

#endif
