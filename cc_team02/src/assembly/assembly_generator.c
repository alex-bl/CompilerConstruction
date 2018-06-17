#include "assembly_generator.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "assembly_arithmetic_op.h"
#include "assembly_assignment.h"
#include "assembly_binary_op_logical.h"
#include "assembly_declaration.h"
#include "assembly_function.h"
#include "assembly_jump.h"
#include "assembly_label.h"
#include "assembly_param.h"
#include "assembly_argument.h"
#include "assembly_return.h"
#include "assembly_template.h"
#include "assembly_unary_op.h"
#include "config.h"
#include "log.h"

static void print_nl_debug(FILE *out)
{
	fprintf(out, "\n");
}

void mCc_assembly_generate_tac_elem(struct mCc_assembly_generator gen_cb,
                                    struct mCc_tac_element *tac_elem)
{
	enum mCc_tac_operation tac_op = tac_elem->tac_operation;

	// TODO: function_def + function_param handler
	switch (tac_op) {

	// arithmetics
	case MCC_TAC_OPARATION_BINARY_OP_ADD_INT:
		gen_cb.add_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_BINARY_OP_ADD_FLOAT:
		gen_cb.add_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_BINARY_OP_SUB_INT:
		gen_cb.sub_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_BINARY_OP_SUB_FLOAT:
		gen_cb.sub_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_BINARY_OP_MUL_INT:
		gen_cb.mul_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_BINARY_OP_MUL_FLOAT:
		gen_cb.mul_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_BINARY_OP_DIV_INT:
		gen_cb.div_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_BINARY_OP_DIV_FLOAT:
		gen_cb.div_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;

	// assignment
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_INT:
		gen_cb.assign_primitive_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_FLOAT:
		gen_cb.assign_primitive_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_BOOL:
		gen_cb.assign_primitive_bool(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_STRING:
		gen_cb.assign_primitive_string(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;

	// binary logical ops
	case MCC_TAC_OPARATION_EQUALS_INT:
		gen_cb.equals_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_EQUALS_FLOAT:
		gen_cb.equals_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_EQUALS_BOOL:
		gen_cb.equals_bool(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_NOT_EQUALS_INT:
		gen_cb.not_equals_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_NOT_EQUALS_FLOAT:
		gen_cb.not_equals_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_NOT_EQUALS_BOOL:
		gen_cb.not_equals_bool(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_GREATER_INT:
		gen_cb.greater_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_GREATER_FLOAT:
		gen_cb.greater_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LESS_INT:
		gen_cb.less_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LESS_FLOAT:
		gen_cb.less_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_GREATER_EQUALS_INT:
		gen_cb.greater_equals_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_GREATER_EQUALS_FLOAT:
		gen_cb.greater_equals_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LESS_EQUALS_INT:
		gen_cb.less_equals_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LESS_EQUALS_FLOAT:
		gen_cb.less_equals_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;

	// jump
	case MCC_TAC_OPARATION_JUMP_EQUALS:
		gen_cb.jump_equals(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_JUMP_NOT_EQUALS:
		gen_cb.jump_not_equals(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_JUMP_GREATER:
		gen_cb.jump_greater(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_JUMP_LESS:
		gen_cb.jump_less(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_JUMP_GRATER_EQUALS:
		gen_cb.jump_greater_equals(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_JUMP_LESS_EQUALS:
		gen_cb.jump_less_equals(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_JUMP_AND:
		gen_cb.jump_and(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_JUMP_OR:
		gen_cb.jump_or(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;

	// return
	case MCC_TAC_OPARATION_RETURN_PRIMITIVE_INT:
		gen_cb.return_primitive_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_FLOAT:
		gen_cb.return_primitive_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_BOOL:
		gen_cb.return_primitive_bool(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_STRING:
		gen_cb.return_primitive_string(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_RETURN_ARRAY_INT:
		gen_cb.return_array_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_RETURN_ARRAY_FLOAT:
		gen_cb.return_array_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_RETURN_ARRAY_BOOL:
		gen_cb.return_array_bool(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_RETURN_ARRAY_STRING:
		gen_cb.return_array_string(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;

	// parameter
	case MCC_TAC_OPARATION_PARAM_INT_PRIMITIVE:
		gen_cb.param_int_primitive(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_PARAM_FLOAT_PRIMITIVE:
		gen_cb.param_float_primitive(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_PARAM_BOOL_PRIMITIVE:
		gen_cb.param_bool_primitive(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_PARAM_STRING_PRIMITIVE:
		gen_cb.param_string_primitive(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_PARAM_INT_ARRAY:
		gen_cb.param_int_array(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_PARAM_FLOAT_ARRAY:
		gen_cb.param_float_array(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_PARAM_BOOL_ARRAY:
		gen_cb.param_bool_array(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_PARAM_STRING_ARRAY:
		gen_cb.param_string_array(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;

	// label
	case MCC_TAC_OPARATION_LABEL_FUNCTION:
		gen_cb.label_function(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LABEL_FLOAT:
		gen_cb.label_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LABEL_IF:
		gen_cb.label_if(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LABEL_ELSE:
		gen_cb.label_else(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LABEL_WHILE:
		gen_cb.label_while(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_LABEL_STRING:
		gen_cb.label_string(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	//TODO: push remains the same?
	case MCC_TAC_OPARATION_LABEL_ARGUMENT:
		gen_cb.argument_int_primitive(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;

		// "pseudo" labels => assign value to tmp-vars
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_INT:
		gen_cb.convert_int_lit(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	// TODO: what about bools, floats, strings?

		// function
	case MCC_TAC_OPARATION_START_FUNCTION_DEF:
		gen_cb.start_function_def(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_END_FUNCTION_DEF:
		gen_cb.end_function_def(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_FUNCTION_CALL:
		gen_cb.function_call(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;

	// declaration
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT:
		gen_cb.declare_primitive_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL:
		gen_cb.declare_primitive_bool(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
		// TODO: doppel-label string + float? => anderen namen dafür?

	case MCC_TAC_OPARATION_DECLARE_ARRAY_INT:
		gen_cb.declare_array_int(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_FLOAT:
		gen_cb.declare_array_float(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_BOOL:
		gen_cb.declare_array_bool(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
	case MCC_TAC_OPARATION_DECLARE_ARRAY_STRING:
		gen_cb.declare_array_string(gen_cb.out, gen_cb.data, tac_elem);
		/*print_nl_debug(gen_cb.out); */ break;
		// TODO: complete => raise warning until completed
		// default: log_error("Not handled"); /*print_nl_debug(gen_cb.out);
		// */break;
	}
}

static void
mCc_assembly_generate_from_tac(struct mCc_assembly_generator gen_cb,
                               struct mCc_tac_element *first_tac_elem)
{
	struct mCc_tac_element *next_tac_elem = first_tac_elem;

	const char *first_function_label =
	    mCc_assembly_get_next_function_label(next_tac_elem);
	mCc_assembly_new_header(gen_cb.out, GENERATED_ASSEMBLY_FILE_NAME,
	                        first_function_label);

	while (next_tac_elem) {
		mCc_assembly_generate_tac_elem(gen_cb, next_tac_elem);
		next_tac_elem = next_tac_elem->tac_next_element;
	}
}

struct mCc_assembly_generator
mcc_assembly_gen_setup(FILE *out, struct mCc_assembly_data *data)
{
	return (struct mCc_assembly_generator){
		.out = out,
		.data = data,

		.add_int = mCc_assembly_generate_add_int,
		.add_float = mCc_assembly_generate_add_float,
		.sub_int = mCc_assembly_generate_sub_int,
		.sub_float = mCc_assembly_generate_sub_float,
		.mul_int = mCc_assembly_generate_mul_int,
		.mul_float = mCc_assembly_generate_mul_float,
		.div_int = mCc_assembly_generate_div_int,
		.div_float = mCc_assembly_generate_div_float,

		// Assignment
		.assign_primitive_int = mCc_assembly_assign_primitive_int,
		.assign_primitive_float = mCc_assembly_assign_primitive_float,
		.assign_primitive_bool = mCc_assembly_assign_primitive_bool,
		.assign_primitive_string = mCc_assembly_assign_primitive_string,

		// Unary-op
		.unary_op_minus_int = mCc_assembly_generate_unary_minus_int,
		.unary_op_minus_float = mCc_assembly_generate_unary_minus_float,
		.unary_op_negation = mCc_assembly_generate_unary_negation,

		// Return
		.return_primitive_int = mCc_assembly_return_primitive_int,
		.return_primitive_float = mCc_assembly_return_primitive_float,
		.return_primitive_bool = mCc_assembly_return_primitive_bool,
		.return_primitive_string = mCc_assembly_return_primitive_string,
		.return_array_int = mCc_assembly_return_array_int,
		.return_array_float = mCc_assembly_return_array_float,
		.return_array_bool = mCc_assembly_return_array_bool,
		.return_array_string = mCc_assembly_return_array_string,

		// Param
		.param_int_primitive = mCc_assembly_param_int_primitive,
		.param_float_primitive = mCc_assembly_param_float_primitive,
		.param_bool_primitive = mCc_assembly_param_bool_primitive,
		.param_string_primitive = mCc_assembly_param_string_primitive,
		.param_int_array = mCc_assembly_param_int_array,
		.param_float_array = mCc_assembly_param_float_array,
		.param_bool_array = mCc_assembly_param_bool_array,
		.param_string_array = mCc_assembly_param_string_array,

		// Param
		.argument_int_primitive = mCc_assembly_argument_int_primitive,
		.argument_float_primitive = mCc_assembly_argument_float_primitive,
		.argument_bool_primitive = mCc_assembly_argument_bool_primitive,
		.argument_string_primitive = mCc_assembly_argument_string_primitive,
		.argument_int_array = mCc_assembly_argument_int_array,
		.argument_float_array = mCc_assembly_argument_float_array,
		.argument_bool_array = mCc_assembly_argument_bool_array,
		.argument_string_array = mCc_assembly_argument_string_array,

		// Label
		.label_function = mCc_assembly_label_function,
		.label_float = mCc_assembly_label_float,
		.label_string = mCc_assembly_label_string,
		.label_if = mCc_assembly_label_if,
		.label_else = mCc_assembly_label_else,
		.label_while = mCc_assembly_label_while,

		//"Pseudo"-label aka literal-handling
		.convert_int_lit = mCc_assembly_pseudo_assign_int_literal,

		// Jump
		.jump_equals = mCc_assembly_generate_jump_equals,
		.jump_not_equals = mCc_assembly_generate_jump_not_equals,
		.jump_greater = mCc_assembly_generate_jump_greater,
		.jump_less = mCc_assembly_generate_jump_less,
		.jump_greater_equals = mCc_assembly_generate_jump_greater_equals,
		.jump_less_equals = mCc_assembly_generate_jump_less_equals,
		.jump_and = mCc_assembly_generate_jump_and,
		.jump_or = mCc_assembly_generate_jump_or,

		// Function
		.start_function_def = mCc_assembly_start_function_def,
		.end_function_def = mCc_assembly_end_function_def,
		.function_call = mCc_assembly_function_call,

		// Declaration
		.declare_primitive_int = mCc_assembly_declare_primitive_int,
		.declare_primitive_float = mCc_assembly_declare_primitive_float,
		.declare_primitive_bool = mCc_assembly_declare_primitive_bool,
		.declare_primitive_string = mCc_assembly_declare_primitive_string,
		.declare_array_int = mCc_assembly_declare_array_int,
		.declare_array_float = mCc_assembly_declare_array_float,
		.declare_array_bool = mCc_assembly_declare_array_bool,
		.declare_array_string = mCc_assembly_declare_array_string,

		// Binary logical ops
		.equals_int = mCc_assembly_equals_int,
		.equals_float = mCc_assembly_equals_float,
		.equals_bool = mCc_assembly_equals_bool,
		.not_equals_int = mCc_assembly_not_equals_int,
		.not_equals_float = mCc_assembly_not_equals_float,
		.not_equals_bool = mCc_assembly_not_equals_bool,
		.greater_int = mCc_assembly_greater_int,
		.greater_float = mCc_assembly_greater_float,
		.less_int = mCc_assembly_less_int,
		.less_float = mCc_assembly_less_float,
		.greater_equals_int = mCc_assembly_greater_equals_int,
		.greater_equals_float = mCc_assembly_greater_equals_float,
		.less_equals_int = mCc_assembly_less_equals_int,
		.less_equals_float = mCc_assembly_less_equals_float,
		.and_op = mCc_assembly_and,
		.or_op = mCc_assembly_or,

	};
}

void mCc_assembly_generate(FILE *out, struct mCc_tac_element *first_tac_elem)
{
	struct mCc_assembly_data data;
	data.current_stack_pos = 0;
	struct mCc_assembly_generator generator_functions =
	    mcc_assembly_gen_setup(out, &data);
	mCc_assembly_generate_from_tac(generator_functions, first_tac_elem);
}
