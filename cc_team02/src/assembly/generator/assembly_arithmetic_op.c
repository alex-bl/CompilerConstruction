#include "assembly_arithmetic_op.h"

#include <assert.h>

#include "assembly_general.h"
#include "assembly_template.h"
#include "assembly_utils.h"
#include "config.h"

void mCc_assembly_generate_add_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	// Current stack-position
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	int result_pos = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);
	// allocate result
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	// Load the 2nd operant into %eax
	mCc_assembly_load_int(out, arg_2, DEFAULT_ACCUMULATOR_OPERAND);
	// Do addition
	mCc_assembly_add_int(out, arg_1);
	// Push
	mCc_assembly_push_int(out, result_pos, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_generate_add_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	int result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                              data->current_stack_pos);

	mCc_assembly_load_float(out, arg_1);
	mCc_assembly_add_float(out, arg_2);
	mCc_assembly_push_float(out, result);
}

void mCc_assembly_generate_sub_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	// Current stack-position
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	int result_pos = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);
	// allocate result
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	// Load the 2nd operant into %eax
	mCc_assembly_load_int(out, arg_2, DEFAULT_ACCUMULATOR_OPERAND);
	// Do addition
	mCc_assembly_sub_int(out, arg_1);
	// Push
	mCc_assembly_push_int(out, result_pos, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_generate_sub_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	int result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                              data->current_stack_pos);

	mCc_assembly_load_float(out, arg_1);
	mCc_assembly_sub_float(out, arg_2);
	mCc_assembly_push_float(out, result);
}

void mCc_assembly_generate_mul_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	// Current stack-position
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	int result_pos = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);
	// allocate result
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	// Load the 2nd operant into %eax
	mCc_assembly_load_int(out, arg_2, DEFAULT_ACCUMULATOR_OPERAND);
	// Do addition
	mCc_assembly_mul_int(out, arg_1);
	// Push
	mCc_assembly_push_int(out, result_pos, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_generate_mul_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	int result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                              data->current_stack_pos);

	mCc_assembly_load_float(out, arg_1);
	mCc_assembly_mul_float(out, arg_2);
	mCc_assembly_push_float(out, result);
}

void mCc_assembly_generate_div_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	// Current stack-position
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	// Dividend
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	int result_pos = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);
	// allocate result
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	// Load the 1st operant into %eax
	mCc_assembly_load_int(out, arg_1, DEFAULT_ACCUMULATOR_OPERAND);
	// Do addition
	mCc_assembly_div_int(out, arg_2);
	// Push
	mCc_assembly_push_int(out, result_pos, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_generate_div_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	int arg_1 = mCc_assembly_calc_stack_position(tac_elem->tac_argument1,
	                                             data->current_stack_pos);
	int arg_2 = mCc_assembly_calc_stack_position(tac_elem->tac_argument2,
	                                             data->current_stack_pos);
	int result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                              data->current_stack_pos);

	mCc_assembly_load_float(out, arg_1);
	mCc_assembly_div_float(out, arg_2);
	mCc_assembly_push_float(out, result);
}
