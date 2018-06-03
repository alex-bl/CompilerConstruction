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
	fprintf(out, "movl %d(%s), %s", tac_offset, DEFAULT_DATA_STACK_POINTER,
	        dest);
	mCc_assembly_print_nl(out);
}

// pops actual float-val from stack to dest
void mCc_assembly_load_float(FILE *out, int tac_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "flds\t%d(%s)", tac_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

// stack_offset needs to be negative?
void mCc_assembly_push_int(FILE *out, int tac_offset, const char *ret_to_push)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "movl %s, %d(%s)", ret_to_push, tac_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

// pushes float on floating-point-stack
void mCc_assembly_push_float(FILE *out, int tac_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "fstps %d(%s)", tac_offset, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

/*============================================================= allocation */
void mCc_assembly_allocate_int_on_stack(FILE *out, int nr_of)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "subl $%zu, %s", mCc_assembly_calc_int_space(nr_of),
	        DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_allocate_float_on_stack(FILE *out, int nr_of)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "subl $%zu, %s", mCc_assembly_calc_float_space(nr_of),
	        DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_allocate_bool_on_stack(FILE *out, int nr_of)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "subl $%zu, %s", mCc_assembly_calc_bool_space(nr_of),
	        DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_allocate_string_on_stack(FILE *out, const char *str)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "subl $%zu, %s", mCc_assembly_calc_string_space(str),
	        DEFAULT_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

/*============================================================= return */

void mCc_assembly_prepare_return(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	/*
	 * TODO:
	 * - use DEFAULT_RETURN_REG, DEFAULT_STACK_POINTER
	 * - use movl	<offset>(%ebp), (%eax)
	 */
	fprintf(out, "movl\t%d(%s), (%s)", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER, DEFAULT_RETURN_REG);
	mCc_assembly_print_nl(out);
}

/*============================================================= arithmetics */
/*
 * TODO:
 * - CHANGED: left operant is always pointer to value on the stack
 */

static void add_sub_mul_int_op(FILE *out, int calculated_offset, const char *op)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "%sl\t%d(%s),%s", op, calculated_offset,
	        DEFAULT_DATA_STACK_POINTER, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_add_int(FILE *out, int calculated_offset)
{
	add_sub_mul_int_op(out, calculated_offset, "add");
}

void mCc_assembly_add_float(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "fadds\t%d(%s)", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_sub_int(FILE *out, int calculated_offset)
{
	add_sub_mul_int_op(out, calculated_offset, "sub");
}

void mCc_assembly_sub_float(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "fsubs\t%d(%s)", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_mul_int(FILE *out, int calculated_offset)
{
	add_sub_mul_int_op(out, calculated_offset, "mul");
}

void mCc_assembly_mul_float(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "fmuls\t%d(%s)", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_div_int(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "idivl\t%d(%s)", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_div_float(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "fdivs\t%d(%s)", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

/*============================================================= assignment */

void mCc_assembly_assign_int(FILE *out, int int_val, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	// simply load value at stack-location
	fprintf(out, "movl\t $%d, %d(%s)", int_val, calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_assign_float(FILE *out, float float_val)
{
	mCc_assembly_print_shift(out);
	// TODO: is there anything required?
	mCc_assembly_print_nl(out);
}

void mCc_assembly_assign_bool(FILE *out, bool bool_val, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	int int_val = (bool_val ? 1 : 0);
	fprintf(out, "movl\t $%d, %d(%s)", int_val, calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_assign_string(FILE *out, const char *string_val)
{
	mCc_assembly_print_shift(out);
	// TODO: is there anything required?
	mCc_assembly_print_nl(out);
}

// TODO: what about arrays?

/*=============================================================
 * logical-binary-ops */
/*
 * TODO:
 * - values are already loaded to the registers which are compared
 * - cmp-result is stored into cmp-reg
 */

void mCc_assembly_compare_int(FILE *out, int calculated_offset_op_1,
                              int calculated_offset_op_2)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "cmpl %d(%s),%d(%s)", calculated_offset_op_1,
	        DEFAULT_DATA_STACK_POINTER, calculated_offset_op_2,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

// Maybe the same?
void mCc_assembly_compare_float(FILE *out, int calculated_offset_op)
{
	/*
	 * TODO:
	 * - check float-compairison
	 * - fcomi (should) compare the actual float-val on stack with value?
	 * - is this correct???
	 */
	mCc_assembly_print_shift(out);
	fprintf(out, "fcom %d(%s)", calculated_offset_op,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

// TODO: andl and orl enough or just simply use cmpl?
void mCc_assembly_and(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "andl\t%d(%s),%s", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_or(FILE *out, int calculated_offset)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "andl\t%d(%s),%s", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

/*============================================================= unary-ops */

/*TODO:
 * - values are already stored to the registers
 */
void mCc_assembly_unary_minus_int(FILE *out)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "negl\t%s", DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_unary_minus_float(FILE *out)
{
	mCc_assembly_print_shift(out);
	// do with top on float-stack
	fprintf(out, "fchs");
	mCc_assembly_print_nl(out);
}

void mCc_assembly_unary_negation(FILE *out)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "xorl\t$1, %s", DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);
}

/*============================================================= jumps */
/*
 * TODO: reads the value from the cmp-reg
 */

static void jump_to(FILE *out, const char *dest_label, const char *jump_op)
{
	mCc_assembly_print_shift(out);
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
	mCc_assembly_print_shift(out);
	fprintf(out, "pushl\t%d(%s)", calculated_offset,
	        DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_add_param_float(FILE *out, int calculated_offset)
{
	// same treatment as int?
	mCc_assembly_add_param_int(out, calculated_offset);
}

void mCc_assembly_add_param_bool(FILE *out, int calculated_offset)
{
	// same treatment as int
	mCc_assembly_add_param_int(out, calculated_offset);
}

void mCc_assembly_add_param_string(FILE *out, const char *string_label)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "pushl\t.%s", string_label);
	mCc_assembly_print_nl(out);
}

/*============================================================= call */

void mCc_assembly_call_function(FILE *out, const char *function_label)
{
	mCc_assembly_print_shift(out);
	fprintf(out, "call %s", function_label);
	mCc_assembly_print_nl(out);
}

/*============================================================= if/while */
/*
 * TODO:
 * - is compound (cmp/jump-combo) => do at handler
 */
