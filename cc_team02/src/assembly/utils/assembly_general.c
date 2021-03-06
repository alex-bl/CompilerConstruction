#include "assembly_general.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "assembly_formatter.h"
#include "assembly_utils.h"
#include "config.h"

/*=========================================================== stack ops*/
/*
 * All literals are treated as variables (get their own tmp-label)
 */
void mCc_assembly_load_int(FILE *out, int tac_offset, const char *dest)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "%d(%s), %s", tac_offset, DEFAULT_DATA_STACK_POINTER, dest);
	mCc_assembly_print_nl(out);
}

// pops actual float-val from stack to dest
void mCc_assembly_load_float(FILE *out, int tac_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "flds");
	fprintf(out, "%d(%s)", tac_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_load_int_as_float(FILE *out, int tac_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "filds");
	fprintf(out, "%d(%s)", tac_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_push_int(FILE *out, int tac_offset, const char *ret_to_push)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "%s, %d(%s)", ret_to_push, tac_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

// pushes float on floating-point-stack
void mCc_assembly_push_float(FILE *out, int tac_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fstps");
	fprintf(out, "%d(%s)", tac_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

// is not working
void mCc_assembly_push_string(FILE *out, const char *label, int tac_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, ".%s, %d(%s)", label, tac_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_push_int_reg_on_stack(FILE *out, const char *reg)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "pushl");
	fprintf(out, "%s", reg);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_push_bool_reg_on_stack(FILE *out, const char *reg)
{
	mCc_assembly_push_int_reg_on_stack(out, reg);
}

void mCc_assembly_move_int(FILE *out, int tac_offset_src, int tac_offset_dest)
{
	/*movl with addresses on both operands not allowed => do intermediate step*/
	mCc_assembly_load_int(out, tac_offset_src, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_push_int(out, tac_offset_dest, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_move_bool(FILE *out, int tac_offset_src, int tac_offset_dest)
{
	mCc_assembly_move_int(out, tac_offset_src, tac_offset_dest);
}

void mCc_assembly_move_float(FILE *out, int tac_offset_src, int tac_offset_dest)
{
	mCc_assembly_move_int(out, tac_offset_src, tac_offset_dest);
}

void mCc_assembly_move_string(FILE *out, int tac_offset_src,
                              int tac_offset_dest)
{
	mCc_assembly_move_int(out, tac_offset_src, tac_offset_dest);
}

/*============================================================= allocation */
void mCc_assembly_allocate_local_stack(FILE *out,
                                       struct mCc_assembly_data *data,
                                       long amount)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "subl");
	fprintf(out, "$%ld, %s", amount, DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
	// NOTE: seems to be useless ;)
	mCc_assembly_adjust_stack_pointer(amount, data);
}

void mCc_assembly_allocate_int_on_stack(FILE *out,
                                        struct mCc_assembly_data *data,
                                        int nr_of)
{
	mCc_assembly_print_shift(out);
	size_t required_space = mCc_assembly_calc_int_space(nr_of);
	mCc_assembly_print_op(out, "subl");
	fprintf(out, "$%zu, %s", required_space, DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
	// NOTE: seems to be useless ;)
	mCc_assembly_adjust_stack_pointer(required_space, data);
}

void mCc_assembly_allocate_float_on_stack(FILE *out,
                                          struct mCc_assembly_data *data,
                                          int nr_of)
{
	mCc_assembly_print_shift(out);
	size_t required_space = mCc_assembly_calc_float_space(nr_of);
	mCc_assembly_print_op(out, "subl");
	fprintf(out, "$%zu, %s", required_space, DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
	mCc_assembly_adjust_stack_pointer(required_space, data);
}

void mCc_assembly_allocate_bool_on_stack(FILE *out,
                                         struct mCc_assembly_data *data,
                                         int nr_of)
{
	mCc_assembly_print_shift(out);
	size_t required_space = mCc_assembly_calc_bool_space(nr_of);
	mCc_assembly_print_op(out, "subl");
	fprintf(out, "$%zu, %s", required_space, DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
	mCc_assembly_adjust_stack_pointer(required_space, data);
}

void mCc_assembly_allocate_string_on_stack(FILE *out,
                                           struct mCc_assembly_data *data,
                                           const char *str)
{
	mCc_assembly_print_shift(out);
	size_t required_space = mCc_assembly_calc_string_space(str);
	mCc_assembly_print_op(out, "subl");
	fprintf(out, "$%zu, %s", required_space, DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
	mCc_assembly_adjust_stack_pointer(required_space, data);
}

void mCc_assembly_allocate_string_array_on_stack(FILE *out,
                                                 struct mCc_assembly_data *data,
                                                 int nr_of)
{
	mCc_assembly_print_shift(out);
	size_t required_space = mCc_assembly_calc_string_space(NULL) * nr_of;
	mCc_assembly_print_op(out, "subl");
	fprintf(out, "$%zu, %s", required_space, DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
	mCc_assembly_adjust_stack_pointer(required_space, data);
}

/*============================================================= return */

void mCc_assembly_prepare_return(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "%d(%s), %s", calculated_offset, DEFAULT_DATA_STACK_POINTER,
	        DEFAULT_RETURN_REG);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_prepare_return_string(FILE *out, const char *label)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, ".%s, %s", label, DEFAULT_RETURN_REG);
	mCc_assembly_print_nl(out);
}

/*============================================================= arithmetics */
/*
 * NOTE:
 * - CHANGED: left operant is always pointer to value on the stack
 */

static void add_sub_mul_int_op(FILE *out, int calculated_offset, const char *op)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, op);
	fprintf(out, "%d(%s), %s", calculated_offset, DEFAULT_DATA_STACK_POINTER,
	        DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_add_int(FILE *out, int calculated_offset)
{
	add_sub_mul_int_op(out, calculated_offset, "addl");
}

void mCc_assembly_add_float(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fadds");
	fprintf(out, "%d(%s)", calculated_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_sub_int(FILE *out, int calculated_offset)
{
	add_sub_mul_int_op(out, calculated_offset, "subl");
}

void mCc_assembly_sub_float(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fsubs");
	fprintf(out, "%d(%s)", calculated_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_mul_int(FILE *out, int calculated_offset)
{
	add_sub_mul_int_op(out, calculated_offset, "imull");
}

void mCc_assembly_mul_float(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fmuls");
	fprintf(out, "%d(%s)", calculated_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_div_int(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "cltd");
	mCc_assembly_print_nl(out);
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "idivl");
	fprintf(out, "%d(%s)", calculated_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_div_float(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fdivs");
	fprintf(out, "%d(%s)", calculated_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

/*============================================================= assignment */

void mCc_assembly_assign_int(FILE *out, int int_val, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	// simply load value at stack-location
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "$%d, %d(%s)", int_val, calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_assign_float(FILE *out, char *float_label,
                               int calculated_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, ".%s, %s", float_label, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "%s, %d(%s)", DEFAULT_ACCUMULATOR_OPERAND, calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_assign_bool(FILE *out, bool bool_val, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	int int_val = (bool_val ? 1 : 0);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "$%d, %d(%s)", int_val, calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_assign_string(FILE *out, const char *label,
                                int calculated_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "$.%s, %d(%s)", label, calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

/*=============================================================
 * logical-binary-ops */
/*
 * NOTE:
 * - values are already loaded to the registers which are compared
 * - cmp-result is stored into cmp-reg
 */

void mCc_assembly_compare_int(FILE *out, int calculated_offset_op_1,
                              int calculated_offset_op_2)
{
	mCc_assembly_load_int(out, calculated_offset_op_1,
	                      DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "cmpl");

	fprintf(out, "%d(%s), %s ", calculated_offset_op_2,
	        DEFAULT_DATA_STACK_POINTER, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_compare_bool(FILE *out, int calculated_offset_op_1,
                               bool to_compare)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "cmpl");

	int bool_val = (to_compare ? 1 : 0);

	fprintf(out, "$%d, %d(%s)", bool_val, calculated_offset_op_1,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

// Maybe the same?
void mCc_assembly_compare_float(FILE *out)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fcomip");
	fprintf(out, "%s, %s", FLOAT_STACK_SEC_REG, FLOAT_STACK_TOP_REG);
	mCc_assembly_print_nl(out);
	// clear also the floating-point stack
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fstp");
	fprintf(out, "%s", FLOAT_STACK_TOP_REG);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_and_op(FILE *out, int calculated_offset_op_1,
                         int calculated_offset_op_2)
{
	mCc_assembly_load_int(out, calculated_offset_op_1,
	                      DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "andl");
	fprintf(out, "%d(%s),%s", calculated_offset_op_2,
	        DEFAULT_DATA_STACK_POINTER, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_or_op(FILE *out, int calculated_offset_op_1,
                        int calculated_offset_op_2)
{
	mCc_assembly_load_int(out, calculated_offset_op_1,
	                      DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "orl");
	fprintf(out, "%d(%s),%s", calculated_offset_op_2,
	        DEFAULT_DATA_STACK_POINTER, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_convert_float_to_int(FILE *out, int offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fistp");
	fprintf(out, "%d(%s)", offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

/*============================================================= unary-ops */

/*NOTE:
 * - values are already stored to the registers
 */
void mCc_assembly_unary_minus_int(FILE *out)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "negl");
	fprintf(out, "%s", DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_unary_minus_float(FILE *out)
{
	mCc_assembly_print_shift(out);
	// do with top on float-stack
	mCc_assembly_print_op(out, "fchs");
	mCc_assembly_print_nl(out);
}

void mCc_assembly_unary_negation(FILE *out)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "xorl");
	fprintf(out, "$1, %s", DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

/*============================================================= jumps */
/*
 * NOTE: reads the value from the cmp-reg
 */

static void jump_to(FILE *out, const char *dest_label, const char *jump_op)
{
	mCc_assembly_print_op(out, "");
	fprintf(out, "%s .%s", jump_op, dest_label);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_jump_equals(FILE *out, const char *dest_label)
{
	jump_to(out, dest_label, "je");
}

void mCc_assembly_jump_not_equals(FILE *out, const char *dest_label)
{
	jump_to(out, dest_label, "jne");
}

void mCc_assembly_jump(FILE *out, const char *dest_label)
{
	jump_to(out, dest_label, "jmp");
}

void mCc_assembly_jump_to_return(FILE *out, int func_scope_counter)
{
	mCc_assembly_print_op(out, "");
	fprintf(out, "%s .%s%d", "jmp", DEFAULT_RETURN_LABEL, func_scope_counter);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_jump_greater(FILE *out, const char *dest_label)
{
	jump_to(out, dest_label, "jg");
}

void mCc_assembly_jump_less(FILE *out, const char *dest_label)
{
	jump_to(out, dest_label, "jl");
}

void mCc_assembly_jump_greater_equals(FILE *out, const char *dest_label)
{
	jump_to(out, dest_label, "jge");
}

void mCc_assembly_jump_less_equals(FILE *out, const char *dest_label)
{
	jump_to(out, dest_label, "jle");
}
/*============================================================= params */

void mCc_assembly_add_param_int(FILE *out, int calculated_offset)
{
	/*NOTE: actually not used. Maybe usefull sometimes?*/
}

void mCc_assembly_add_param_float(FILE *out, int calculated_offset)
{
	/*NOTE: actually not used. Maybe usefull sometimes?*/
}

void mCc_assembly_add_param_bool(FILE *out, int calculated_offset)
{
	/*NOTE: actually not used. Maybe usefull sometimes?*/
}

void mCc_assembly_add_param_string(FILE *out, const char *string_label)
{
	/*NOTE: actually not used. Maybe usefull sometimes?*/
}

/*============================================================= arguments */

void mCc_assembly_add_argument_int(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "pushl");
	fprintf(out, "%d(%s)", calculated_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_add_argument_float(FILE *out, int calculated_offset)
{
	// same treatment as int
	mCc_assembly_add_argument_int(out, calculated_offset);
}

void mCc_assembly_add_argument_bool(FILE *out, int calculated_offset)
{
	// same treatment as int
	mCc_assembly_add_argument_int(out, calculated_offset);
}

void mCc_assembly_add_argument_string(FILE *out, const char *string_label)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "pushl");
	fprintf(out, ".%s", string_label);
	mCc_assembly_print_nl(out);
}

/*============================================================= call */

void mCc_assembly_call_function(FILE *out, const char *function_label)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "call");
	fprintf(out, "%s", function_label);
	mCc_assembly_print_nl(out);
}

/*============================================================= special */

static void do_set_cc_op(FILE *out, const char *op)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, op);
	fprintf(out, "%s", CONDITION_FLAG_REG);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_set_equals(FILE *out)
{
	do_set_cc_op(out, "sete");
}

void mCc_assembly_set_equals_float(FILE *out)
{
	do_set_cc_op(out, "sete");
}

void mCc_assembly_set_not_equals(FILE *out)
{
	do_set_cc_op(out, "setne");
}

void mCc_assembly_set_not_equals_float(FILE *out)
{
	do_set_cc_op(out, "setne");
}

void mCc_assembly_set_greater(FILE *out)
{
	do_set_cc_op(out, "setg");
}

void mCc_assembly_set_greater_float(FILE *out)
{
	do_set_cc_op(out, "seta");
}

void mCc_assembly_set_less(FILE *out)
{
	do_set_cc_op(out, "setl");
}

void mCc_assembly_set_less_float(FILE *out)
{
	do_set_cc_op(out, "setb");
}

void mCc_assembly_set_greater_equals(FILE *out)
{
	do_set_cc_op(out, "setge");
}

void mCc_assembly_set_greater_equals_float(FILE *out)
{
	do_set_cc_op(out, "setae");
}

void mCc_assembly_set_less_equals(FILE *out)
{
	do_set_cc_op(out, "setle");
}

void mCc_assembly_set_less_equals_float(FILE *out)
{
	do_set_cc_op(out, "setbe");
}

void mCc_assembly_extract_condition_flag(FILE *out, const char *reg_dest)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movzbl");
	fprintf(out, "%s, %s", CONDITION_FLAG_REG, reg_dest);
	mCc_assembly_print_nl(out);
}

/*============================================================= if/while */
/*
 * NOTE:
 * - is compound (cmp/jump-combo) => do at handler
 */

/*============================================================= array */

static void mCc_assembly_compute_index_local(FILE *out, int base_size,
                                             int offset_array_base,
                                             int offset_array_index)
{
	mCc_assembly_load_int(out, offset_array_index, EDX_REG);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "leal");
	fprintf(out, "%d(%s,%s,%d), %s", offset_array_base,
	        DEFAULT_DATA_STACK_POINTER, EDX_REG, base_size, ECX_REG);
	mCc_assembly_print_nl(out);
}

static void mCc_assembly_compute_index_param(FILE *out, int base_size,
                                             int offset_array_base,
                                             int offset_array_index)
{
	mCc_assembly_load_int(out, offset_array_index, EDX_REG);
	mCc_assembly_load_int(out, offset_array_base, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "leal");
	fprintf(out, "%d(%s,%s,%d), %s", 0, DEFAULT_ACCUMULATOR_OPERAND, EDX_REG,
	        base_size, ECX_REG);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_compute_index(FILE *out, int base_size, int offset_array_base,
                                int offset_array_index, bool is_param)
{
	if (is_param) {
		mCc_assembly_compute_index_param(out, base_size, offset_array_base,
		                                 offset_array_index);
	} else {
		mCc_assembly_compute_index_local(out, base_size, offset_array_base,
		                                 offset_array_index);
	}
}

void mCc_assembly_move_index_val_to_eax(FILE *out)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "(%s), %s", ECX_REG, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

static void move_to_ecx_reg(FILE *out)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "movl");
	fprintf(out, "%s, (%s)", DEFAULT_ACCUMULATOR_OPERAND, ECX_REG);
	mCc_assembly_print_nl(out);
}

static void move_float_to_ecx_reg(FILE *out)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "fstps");
	fprintf(out, "(%s)", ECX_REG);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_load_float_at_ecx(FILE *out)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "flds");
	fprintf(out, "(%s)", ECX_REG);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_store_int_val_at_index(FILE *out, int calc_offset)
{
	mCc_assembly_load_int(out, calc_offset, DEFAULT_ACCUMULATOR_OPERAND);
	move_to_ecx_reg(out);
}

void mCc_assembly_store_float_val_at_index(FILE *out, int calc_offset)
{
	mCc_assembly_load_float(out, calc_offset);
	move_float_to_ecx_reg(out);
}

void mCc_assembly_store_bool_val_at_index(FILE *out, int calc_offset)
{
	mCc_assembly_load_int(out, calc_offset, DEFAULT_ACCUMULATOR_OPERAND);
	move_to_ecx_reg(out);
}

void mCc_assembly_store_string_val_at_index(FILE *out, int calc_offset)
{
	mCc_assembly_load_int(out, calc_offset, DEFAULT_ACCUMULATOR_OPERAND);
	move_to_ecx_reg(out);
}

void mCc_assembly_load_ptr(FILE *out, int calc_offset, const char *dest)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "leal");
	fprintf(out, "%d(%s), %s", calc_offset, DEFAULT_DATA_STACK_POINTER, dest);
	mCc_assembly_print_nl(out);
}
