#include "assembly_arithmetic_op.h"

#include <assert.h>

#include "assembly_general.h"
#include "assembly_template.h"
#include "assembly_utils.h"
#include "config.h"

void mCc_assembly_generate_add_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	// Allocate space for the result
	mCc_assembly_allocate_int_on_stack(out, data, 1);
	// Current stack-position
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	// Load the 2nd operant into %eax
	mCc_assembly_load_int(out, arg_2, DEFAULT_ACCUMULATOR_OPERAND);
	// Do addition
	mCc_assembly_add_int(out, arg_1);
	// Push the result
	mCc_assembly_push_int(out, data->current_stack_pos,
	                      DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_generate_add_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	//	handle_assembly_float_arithmetic_op(out, tac_elem, "add");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_sub_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	// handle_assembly_int_op_add_sub_mul(out, tac_elem, "sub");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_sub_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	// handle_assembly_float_arithmetic_op(out, tac_elem, "sub");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_mul_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	// handle_assembly_int_op_add_sub_mul(out, tac_elem, "mul");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_mul_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	// handle_assembly_float_arithmetic_op(out, tac_elem, "mul");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_div_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	//	assert(out);
	//	assert(tac_elem);
	//	// divident needs to be %eax?
	//	load_from_int_tac_identifier(out, tac_elem->tac_argument1, "%eax");
	//	// is this correct this way?
	//	fprintf(out, "\tcltd\n");
	//	// divisor
	//	load_from_int_tac_identifier(out, tac_elem->tac_argument2, "%ecx");
	//	fprintf(out, "\tidivl %%ecx\n");
	//	mCc_assembly_push_int_on_stack(out, tac_elem->tac_result->stack_offset,
	//	                               "%ecx");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_div_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	// handle_assembly_float_arithmetic_op(out, tac_elem, "div");
	/*
	 * TODO: redo that thing
	 */
}
