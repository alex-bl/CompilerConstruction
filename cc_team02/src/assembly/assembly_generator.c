#include "assembly_generator.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "assembly_argument.h"
#include "assembly_arithmetic_op.h"
#include "assembly_array.h"
#include "assembly_assignment.h"
#include "assembly_binary_op_logical.h"
#include "assembly_declaration.h"
#include "assembly_function.h"
#include "assembly_jump.h"
#include "assembly_label.h"
#include "assembly_param.h"
#include "assembly_return.h"
#include "assembly_template.h"
#include "assembly_unary_op.h"
#include "assembly_utils.h"
#include "config.h"
#include "log.h"

static void print_nl_debug(FILE *out)
{
	fprintf(out, "\n");
}

static bool skip_generation(enum mCc_tac_operation tac_op)
{

	switch (tac_op) {
	case MCC_TAC_OPARATION_LABEL_STRING:
	case MCC_TAC_OPARATION_LABEL_FLOAT: return true;
	}

	return false;
}

static void prepend_arg(struct mCc_assembly_generator gen_cb,
                        struct mCc_tac_element *tac_elem, int scope)
{
	struct mCc_assembly_argument_list *new_head =
	    mCc_assembly_prepend_arg_list_elem(gen_cb.data->arg_list, tac_elem, scope);
	gen_cb.data->arg_list = new_head;
}

static void
mCc_assembly_generate_arg_list_elem(struct mCc_assembly_generator gen_cb,
                                    struct mCc_tac_element *tac_elem)
{
	//TODO: should be sufficent hence all primitives/arrays are treated equally
	if(tac_elem->tac_operation==MCC_TAC_OPARATION_LABEL_ARGUMENT){
		gen_cb.argument_int_primitive(gen_cb.out, gen_cb.data, tac_elem);
	}else{
		gen_cb.argument_int_array(gen_cb.out, gen_cb.data, tac_elem);
	}
}

static void mCc_assembly_generate_arg_list(struct mCc_assembly_generator gen_cb)
{
	struct mCc_assembly_argument_list *next_arg = gen_cb.data->arg_list;
	int actual_arg_scope = gen_cb.data->arg_scope_counter;
	bool has_params = false;

	while (next_arg && actual_arg_scope == next_arg->open_scope) {
		struct mCc_assembly_argument_list *actual = next_arg;
		mCc_assembly_generate_arg_list_elem(gen_cb, actual->argument);
		next_arg = next_arg->next;
		mCc_assembly_free_arg_list_elem(actual);
		has_params=true;
	}
	// handle parameterless functions
	if(has_params){
		gen_cb.data->arg_scope_counter--;
	}

	// set new head
	if(!next_arg){
		gen_cb.data->arg_list = NULL;
	}else{
		gen_cb.data->arg_list=next_arg;
	}
}

void mCc_assembly_generate_tac_elem(struct mCc_assembly_generator gen_cb,
                                    struct mCc_tac_element *tac_elem)
{
	enum mCc_tac_operation tac_op = tac_elem->tac_operation;

	// e.g. float/string labels are handled at the beginning
	if (!skip_generation(tac_op)) {

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
		case MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_INT:
			gen_cb.assign_function_call_int(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_FLOAT:
			gen_cb.assign_function_call_float(gen_cb.out, gen_cb.data,
			                                  tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_BOOL:
			gen_cb.assign_function_call_bool(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_STRING:
			gen_cb.assign_function_call_string(gen_cb.out, gen_cb.data,
			                                   tac_elem);
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
		case MCC_TAC_OPARATION_BINARY_AND:
			gen_cb.and_op(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_BINARY_OR:
			gen_cb.or_op(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;

		// unary ops
		case MCC_TAC_OPARATION_UNARY_MINUS_INT:
			gen_cb.unary_op_minus_int(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_UNARY_MINUS_FLOAT:
			gen_cb.unary_op_minus_float(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_UNARY_NEGATION:
			gen_cb.unary_op_negation(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;

		// jump
		case MCC_TAC_OPARATION_JUMP_NOT_EQUALS:
			gen_cb.jump_not_equals(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_JUMP_EQUALS:
			gen_cb.jump_equals(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_JUMP:
			gen_cb.jump(gen_cb.out, gen_cb.data, tac_elem);
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

		case MCC_TAC_OPARATION_INTERMEDIATE_RETURN_INT:
			gen_cb.intermediate_return_int(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_INTERMEDIATE_RETURN_FLOAT:
			gen_cb.intermediate_return_float(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_INTERMEDIATE_RETURN_BOOL:
			gen_cb.intermediate_return_bool(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_INTERMEDIATE_RETURN_STRING:
			gen_cb.intermediate_return_string(gen_cb.out, gen_cb.data,
			                                  tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;

		// parameter => just prepend, generate later
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
		case MCC_TAC_OPARATION_LABEL_AFTER_ELSE:
			gen_cb.label_after_else(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_LABEL_WHILE:
			gen_cb.label_while(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_LABEL_STRING:
			gen_cb.label_string(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		// TODO: arg-scope-counter increase
		case MCC_TAC_OPARATION_ARGUMENT_LIST_START:
			gen_cb.data->arg_scope_counter++;
			break;
		// TODO: push remains the same?
		case MCC_TAC_OPARATION_LABEL_ARGUMENT:
		case MCC_TAC_OPARATION_LABEL_ARGUMENT_ARRAY:
			// gen_cb.argument_int_primitive(gen_cb.out, gen_cb.data, tac_elem);
			prepend_arg(gen_cb, tac_elem,gen_cb.data->arg_scope_counter);
			/*print_nl_debug(gen_cb.out); */ break;

			// "pseudo" labels => assign value to tmp-vars
		case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_INT:
			gen_cb.convert_int_lit(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
			// "pseudo" labels => assign value to tmp-vars
		case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_FLOAT:
			gen_cb.convert_float_lit(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
			// "pseudo" labels => assign value to tmp-vars
		case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_BOOL:
			gen_cb.convert_bool_lit(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
			// "pseudo" labels => assign value to tmp-vars
		case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_STRING:
			gen_cb.convert_string_lit(gen_cb.out, gen_cb.data, tac_elem);
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
			// generate the arguments in the reverse order
			mCc_assembly_generate_arg_list(gen_cb);
			gen_cb.function_call(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;

		// declaration
		case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT:
			gen_cb.declare_primitive_int(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL:
			gen_cb.declare_primitive_bool(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_STRING:
			gen_cb.declare_primitive_string(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_FLOAT:
			gen_cb.declare_primitive_float(gen_cb.out, gen_cb.data, tac_elem);
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

		// arrays
		case MCC_TAC_OPARATION_ASSIGN_ARRAY_INT:
			gen_cb.assign_array_int(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_ASSIGN_ARRAY_FLOAT:
			gen_cb.assign_array_float(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_ASSIGN_ARRAY_BOOL:
			gen_cb.assign_array_bool(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPARATION_ASSIGN_ARRAY_STRING:
			gen_cb.assign_array_string(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;

		case MCC_TAC_OPERATION_INT_ARR_INDEX_ACCESS:
			gen_cb.index_acc_arr_int(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPERATION_FLOAT_ARR_INDEX_ACCESS:
			gen_cb.index_acc_arr_float(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPERATION_BOOL_ARR_INDEX_ACCESS:
			gen_cb.index_acc_arr_bool(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		case MCC_TAC_OPERATION_STRING_ARR_INDEX_ACCESS:
			gen_cb.index_acc_arr_string(gen_cb.out, gen_cb.data, tac_elem);
			/*print_nl_debug(gen_cb.out); */ break;
		}
	}
}

static bool mCc_assembly_handle_floats(struct mCc_tac_element *tac_elem,
                                       struct mCc_assembly_generator gen_cb)
{
	enum mCc_tac_operation tac_op = tac_elem->tac_operation;

	// TODO: function_def + function_param handler
	switch (tac_op) {
	// label
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_FLOAT:
		gen_cb.label_float(gen_cb.out, gen_cb.data, tac_elem);
		return true;
	default: return false;
	}
	return false;
}

static bool mCc_assembly_handle_strings(struct mCc_tac_element *tac_elem,
                                        struct mCc_assembly_generator gen_cb)
{
	enum mCc_tac_operation tac_op = tac_elem->tac_operation;

	// TODO: function_def + function_param handler
	switch (tac_op) {
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_STRING:
		gen_cb.label_string(gen_cb.out, gen_cb.data, tac_elem);
		return true;
	}
	return false;
}

void mCc_assembly_generate_from_tac(struct mCc_assembly_generator gen_cb,
                                    struct mCc_tac_element *first_tac_elem)
{
	struct mCc_tac_element *next_tac_elem = first_tac_elem;

	const char *first_function_label =
	    mCc_assembly_get_next_function_label(next_tac_elem);
	mCc_assembly_new_header(gen_cb.out, GENERATED_ASSEMBLY_FILE_NAME,
	                        first_function_label);

	// first handle all floats
	while (next_tac_elem) {
		mCc_assembly_handle_floats(next_tac_elem, gen_cb);
		next_tac_elem = next_tac_elem->tac_next_element;
	}

	next_tac_elem = first_tac_elem;
	bool strings_available = false;

	// then handle all strings
	while (next_tac_elem) {
		if (mCc_assembly_handle_strings(next_tac_elem, gen_cb)) {
			strings_available = true;
		}
		next_tac_elem = next_tac_elem->tac_next_element;
	}
	if (strings_available) {
		// before first function-def
		mCc_assembly_new_string_leave_with_function(gen_cb.out,
		                                            first_function_label);
	}
	// handle the rest
	next_tac_elem = first_tac_elem;

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
		.assign_function_call_int = mCc_assembly_assign_function_call_int,
		.assign_function_call_float = mCc_assembly_assign_function_call_float,
		.assign_function_call_bool = mCc_assembly_assign_function_call_bool,
		.assign_function_call_string = mCc_assembly_assign_function_call_string,

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
		.intermediate_return_int = mCc_assembly_intermediate_return_int,
		.intermediate_return_float = mCc_assembly_intermediate_return_float,
		.intermediate_return_bool = mCc_assembly_intermediate_return_bool,
		.intermediate_return_string = mCc_assembly_intermediate_return_string,

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
		.label_after_else = mCc_assembly_label_after_else,
		.label_while = mCc_assembly_label_while,

		//"Pseudo"-label aka literal-handling
		.convert_int_lit = mCc_assembly_pseudo_assign_int_literal,
		.convert_float_lit = mCc_assembly_pseudo_assign_float_literal,
		.convert_bool_lit = mCc_assembly_pseudo_assign_bool_literal,
		.convert_string_lit = mCc_assembly_pseudo_assign_string_literal,

		// Jump
		.jump_not_equals = mCc_assembly_generate_jump_not_equals,
		.jump_equals = mCc_assembly_generate_jump_equals,
		.jump = mCc_assembly_generate_jump,

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

		// arrays
		.assign_array_int = mCc_assembly_assign_array_int,
		.assign_array_float = mCc_assembly_assign_array_float,
		.assign_array_bool = mCc_assembly_assign_array_bool,
		.assign_array_string = mCc_assembly_assign_array_string,

		.index_acc_arr_int = mCc_assembly_index_acc_arr_int,
		.index_acc_arr_float = mCc_assembly_index_acc_arr_float,
		.index_acc_arr_bool = mCc_assembly_index_acc_arr_bool,
		.index_acc_arr_string = mCc_assembly_index_acc_arr_string

	};
}

void mCc_assembly_generate(FILE *out, struct mCc_tac_element *first_tac_elem)
{
	struct mCc_assembly_data data;

	data.current_stack_pos = 0;
	data.func_scope_counter = -1;
	data.arg_scope_counter = 0;
	data.arg_list = NULL;

	struct mCc_assembly_generator generator_functions =
	    mcc_assembly_gen_setup(out, &data);
	mCc_assembly_generate_from_tac(generator_functions, first_tac_elem);
}
