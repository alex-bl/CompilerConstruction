#include "assembly_array.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "assembly_general.h"
#include "assembly_utils.h"
#include "config.h"

static struct mCc_tac_identifier *
get_arr_base_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

static struct mCc_tac_identifier *
get_arr_index_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument2;
}

static struct mCc_tac_identifier *
get_arr_dereferenced_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

void mCc_assembly_index_acc_arr_int(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
	assert(data);
	assert(tac_elem);

	struct mCc_tac_identifier *array_base = get_arr_base_identifier(tac_elem);
	struct mCc_tac_identifier *array_index = get_arr_index_identifier(tac_elem);
	struct mCc_tac_identifier *array_value =
	    get_arr_dereferenced_identifier(tac_elem);

	int offset_array_base =
	    mCc_assembly_calc_stack_position(array_base, data->current_stack_pos);
	int offset_array_index =
	    mCc_assembly_calc_stack_position(array_index, data->current_stack_pos);
	int offset_array_value =
	    mCc_assembly_calc_stack_position(array_value, data->current_stack_pos);

	//mCc_assembly_allocate_int_on_stack(out, data, 1);

	mCc_assembly_compute_index(out, INT_SIZE, offset_array_base,
	                           offset_array_index);
	mCc_assembly_move_index_val_to_eax(out);
	mCc_assembly_push_int(out, offset_array_value, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_index_acc_arr_float(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem)
{
	assert(data);
	assert(tac_elem);

	struct mCc_tac_identifier *array_base = get_arr_base_identifier(tac_elem);
	struct mCc_tac_identifier *array_index = get_arr_index_identifier(tac_elem);
	struct mCc_tac_identifier *array_value =
	    get_arr_dereferenced_identifier(tac_elem);

	int offset_array_base =
	    mCc_assembly_calc_stack_position(array_base, data->current_stack_pos);
	int offset_array_index =
	    mCc_assembly_calc_stack_position(array_index, data->current_stack_pos);
	int offset_array_value =
	    mCc_assembly_calc_stack_position(array_value, data->current_stack_pos);

	//mCc_assembly_allocate_float_on_stack(out, data, 1);

	mCc_assembly_compute_index(out, INT_SIZE, offset_array_base,
	                           offset_array_index);

	mCc_assembly_load_float_at_ecx(out);
	mCc_assembly_push_float(out, offset_array_value);
}

void mCc_assembly_index_acc_arr_bool(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	assert(data);
	assert(tac_elem);

	struct mCc_tac_identifier *array_base = get_arr_base_identifier(tac_elem);
	struct mCc_tac_identifier *array_index = get_arr_index_identifier(tac_elem);
	struct mCc_tac_identifier *array_value =
	    get_arr_dereferenced_identifier(tac_elem);

	int offset_array_base =
	    mCc_assembly_calc_stack_position(array_base, data->current_stack_pos);
	int offset_array_index =
	    mCc_assembly_calc_stack_position(array_index, data->current_stack_pos);
	int offset_array_value =
	    mCc_assembly_calc_stack_position(array_value, data->current_stack_pos);

	//mCc_assembly_allocate_bool_on_stack(out, data, 1);

	mCc_assembly_compute_index(out, INT_SIZE, offset_array_base,
	                           offset_array_index);
	mCc_assembly_move_index_val_to_eax(out);
	mCc_assembly_push_int(out, offset_array_value, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_index_acc_arr_string(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	assert(data);
	assert(tac_elem);

	struct mCc_tac_identifier *array_base = get_arr_base_identifier(tac_elem);
	struct mCc_tac_identifier *array_index = get_arr_index_identifier(tac_elem);
	struct mCc_tac_identifier *array_value =
	    get_arr_dereferenced_identifier(tac_elem);

	int offset_array_base =
	    mCc_assembly_calc_stack_position(array_base, data->current_stack_pos);
	int offset_array_index =
	    mCc_assembly_calc_stack_position(array_index, data->current_stack_pos);
	int offset_array_value =
	    mCc_assembly_calc_stack_position(array_value, data->current_stack_pos);

	//mCc_assembly_allocate_string_on_stack(out, data, NULL);

	mCc_assembly_compute_index(out, INT_SIZE, offset_array_base,
	                           offset_array_index);

	mCc_assembly_move_index_val_to_eax(out);
	mCc_assembly_push_int(out, offset_array_value, DEFAULT_ACCUMULATOR_OPERAND);
}
