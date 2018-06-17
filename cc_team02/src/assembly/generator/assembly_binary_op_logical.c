#include "assembly_binary_op_logical.h"

#include "assembly_general.h"
#include "assembly_utils.h"
#include "config.h"

/*==================================== equals*/

void mCc_assembly_equals_int(FILE *out, struct mCc_assembly_data *data,
                             struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	mCc_assembly_compare_int(out, pos_operand_1, pos_operand_2);
	// compairison
	mCc_assembly_set_equals(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_equals_float(FILE *out, struct mCc_assembly_data *data,
                               struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	//push both on float-stack
	mCc_assembly_load_float(out, pos_operand_2);
	mCc_assembly_load_float(out, pos_operand_1);

	mCc_assembly_compare_float(out);

	// compairison
	mCc_assembly_set_equals_float(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_equals_bool(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem)
{
	// TODO: same as for ints?
	mCc_assembly_equals_int(out, data, tac_elem);
}

/*==================================== not equals*/

void mCc_assembly_not_equals_int(FILE *out, struct mCc_assembly_data *data,
                                 struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	mCc_assembly_compare_int(out, pos_operand_1, pos_operand_2);
	// compairison
	mCc_assembly_set_not_equals(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_not_equals_float(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	//push both on float-stack
	mCc_assembly_load_float(out, pos_operand_2);
	mCc_assembly_load_float(out, pos_operand_1);

	mCc_assembly_compare_float(out);

	// compairison
	mCc_assembly_set_not_equals_float(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_not_equals_bool(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem)
{
	// TODO: same as int?
	mCc_assembly_not_equals_int(out, data, tac_elem);
}

/*==================================== greater*/

void mCc_assembly_greater_int(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	mCc_assembly_compare_int(out, pos_operand_1, pos_operand_2);
	// compairison
	mCc_assembly_set_greater(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_greater_float(FILE *out, struct mCc_assembly_data *data,
                                struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	//push both on float-stack
	mCc_assembly_load_float(out, pos_operand_2);
	mCc_assembly_load_float(out, pos_operand_1);

	mCc_assembly_compare_float(out);

	// compairison
	mCc_assembly_set_greater_float(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

/*==================================== less*/

void mCc_assembly_less_int(FILE *out, struct mCc_assembly_data *data,
                           struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	mCc_assembly_compare_int(out, pos_operand_1, pos_operand_2);
	// compairison
	mCc_assembly_set_less(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_less_float(FILE *out, struct mCc_assembly_data *data,
                             struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	//push both on float-stack
	mCc_assembly_load_float(out, pos_operand_2);
	mCc_assembly_load_float(out, pos_operand_1);

	mCc_assembly_compare_float(out);

	// compairison
	mCc_assembly_set_less_float(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

/*==================================== greater equals*/
void mCc_assembly_greater_equals_int(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	mCc_assembly_compare_int(out, pos_operand_1, pos_operand_2);
	// compairison
	mCc_assembly_set_greater_equals(out);

	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_greater_equals_float(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	//push both on float-stack
	mCc_assembly_load_float(out, pos_operand_2);
	mCc_assembly_load_float(out, pos_operand_1);

	mCc_assembly_compare_float(out);

	// compairison
	mCc_assembly_set_greater_equals_float(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

/*==================================== less equals*/
void mCc_assembly_less_equals_int(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	mCc_assembly_compare_int(out, pos_operand_1, pos_operand_2);
	// compairison
	mCc_assembly_set_less_equals(out);

	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);

	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_less_equals_float(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	//push both on float-stack
	mCc_assembly_load_float(out, pos_operand_2);
	mCc_assembly_load_float(out, pos_operand_1);

	mCc_assembly_compare_float(out);

	// compairison
	mCc_assembly_set_less_equals_float(out);
	mCc_assembly_extract_condition_flag(out, DEFAULT_ACCUMULATOR_OPERAND);

	mCc_assembly_allocate_int_on_stack(out, data, 1);
	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);

}

/*==================================== and/or */
void mCc_assembly_and(FILE *out, struct mCc_assembly_data *data,
                      struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	mCc_assembly_and_op(out, pos_operand_1, pos_operand_2);
	mCc_assembly_allocate_bool_on_stack(out, data, 1);

	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_or(FILE *out, struct mCc_assembly_data *data,
                     struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	int pos_result = mCc_assembly_calc_stack_position(tac_elem->tac_result,
	                                                  data->current_stack_pos);

	mCc_assembly_or_op(out, pos_operand_1, pos_operand_2);
	mCc_assembly_allocate_bool_on_stack(out, data, 1);

	mCc_assembly_push_int(out, pos_result, DEFAULT_ACCUMULATOR_OPERAND);
}
