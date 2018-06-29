#include <assert.h>
#include <stdio.h>

#include "assembly_general.h"
#include "assembly_template.h"
#include "assembly_utils.h"
#include "config.h"

static struct mCc_tac_identifier *
get_literal_val(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

static struct mCc_tac_identifier *
get_assign_dest(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

static struct mCc_tac_identifier *
get_assign_dest_var(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

static struct mCc_tac_identifier *
get_pseudo_var(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

void mCc_assembly_assign_primitive_int(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_identifier *pseudo_var = get_pseudo_var(tac_elem);
	struct mCc_tac_identifier *dest_var = get_assign_dest_var(tac_elem);
	int pseudo_var_offset =
	    mCc_assembly_calc_stack_position(pseudo_var, data->current_stack_pos);
	int dest_var_offset =
	    mCc_assembly_calc_stack_position(dest_var, data->current_stack_pos);
	// is the "new" assignment => from var to var
	mCc_assembly_move_int(out, pseudo_var_offset, dest_var_offset);
}

void mCc_assembly_pseudo_assign_int_literal(FILE *out,
                                            struct mCc_assembly_data *data,
                                            struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_identifier *var = get_assign_dest(tac_elem);
	struct mCc_tac_identifier *int_val = get_literal_val(tac_elem);

	// space for the tmp-variable
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_int(out, int_val->i_val, calculated_offset);
}

void mCc_assembly_assign_function_call_int(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_identifier *dest_var = get_assign_dest_var(tac_elem);
	int dest_var_offset =
	    mCc_assembly_calc_stack_position(dest_var, data->current_stack_pos);
	mCc_assembly_push_int(out, dest_var_offset, DEFAULT_RETURN_REG);
}

// TODO
void mCc_assembly_assign_primitive_float(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *pseudo_var = get_pseudo_var(tac_elem);
	struct mCc_tac_identifier *dest_var = get_assign_dest_var(tac_elem);
	int pseudo_var_offset =
	    mCc_assembly_calc_stack_position(pseudo_var, data->current_stack_pos);
	int dest_var_offset =
	    mCc_assembly_calc_stack_position(dest_var, data->current_stack_pos);

	// is the "new" assignment => from var to var
	mCc_assembly_move_float(out, pseudo_var_offset, dest_var_offset);
}

// TODO: needed?
void mCc_assembly_pseudo_assign_float_literal(FILE *out,
                                              struct mCc_assembly_data *data,
                                              struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_identifier *var = get_assign_dest(tac_elem);
	// no float-val-loading required => is already when converting floats +
	// strings

	// space for the tmp-variable
	mCc_assembly_allocate_float_on_stack(out, data, 1);

	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_float(out, var->name, calculated_offset);
}

void mCc_assembly_assign_function_call_float(FILE *out,
                                             struct mCc_assembly_data *data,
                                             struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_identifier *dest_var = get_assign_dest_var(tac_elem);
	struct mCc_tac_identifier *pseudo_var = get_pseudo_var(tac_elem);

	int dest_var_offset =
	    mCc_assembly_calc_stack_position(dest_var, data->current_stack_pos);
	int pseudo_var_offset =
	    mCc_assembly_calc_stack_position(pseudo_var, data->current_stack_pos);

	mCc_assembly_move_float(out, pseudo_var_offset, dest_var_offset);
	//mCc_assembly_push_int(out, dest_var_offset, DEFAULT_RETURN_REG);
}

void mCc_assembly_assign_primitive_bool(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *pseudo_var = get_pseudo_var(tac_elem);
	struct mCc_tac_identifier *dest_var = get_assign_dest_var(tac_elem);
	int pseudo_var_offset =
	    mCc_assembly_calc_stack_position(pseudo_var, data->current_stack_pos);
	int dest_var_offset =
	    mCc_assembly_calc_stack_position(dest_var, data->current_stack_pos);
	// is the "new" assignment => from var to var
	mCc_assembly_move_bool(out, pseudo_var_offset, dest_var_offset);
}

void mCc_assembly_pseudo_assign_bool_literal(FILE *out,
                                             struct mCc_assembly_data *data,
                                             struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_identifier *var = get_assign_dest(tac_elem);
	struct mCc_tac_identifier *bool_val = get_literal_val(tac_elem);

	// space for the tmp-variable
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_bool(out, bool_val->b_val, calculated_offset);
}

void mCc_assembly_assign_function_call_bool(FILE *out,
                                            struct mCc_assembly_data *data,
                                            struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	mCc_assembly_assign_function_call_int(out, data, tac_elem);
}

void mCc_assembly_assign_primitive_string(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *pseudo_var = get_pseudo_var(tac_elem);
	struct mCc_tac_identifier *dest_var = get_assign_dest_var(tac_elem);
	int pseudo_var_offset =
	    mCc_assembly_calc_stack_position(pseudo_var, data->current_stack_pos);
	int dest_var_offset =
	    mCc_assembly_calc_stack_position(dest_var, data->current_stack_pos);
	// is the "new" assignment => from var to var
	mCc_assembly_move_string(out, pseudo_var_offset, dest_var_offset);
}

void mCc_assembly_pseudo_assign_string_literal(FILE *out,
                                               struct mCc_assembly_data *data,
                                               struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_identifier *var = get_assign_dest(tac_elem);
	struct mCc_tac_identifier *string_val = get_literal_val(tac_elem);

	// space for the tmp-variable
	mCc_assembly_allocate_string_on_stack(out, data, string_val->name);

	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_string(out, var->name, calculated_offset);
}

void mCc_assembly_assign_function_call_string(FILE *out,
                                              struct mCc_assembly_data *data,
                                              struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	mCc_assembly_assign_function_call_int(out, data, tac_elem);
}

//=========================================== arrays

static struct mCc_tac_identifier *
get_arr_base_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

static struct mCc_tac_identifier *
get_arr_index_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument2;
}

static struct mCc_tac_identifier *
get_arr_dereferenced_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

void mCc_assembly_assign_array_int(FILE *out, struct mCc_assembly_data *data,
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
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	mCc_assembly_compute_index(out, INT_SIZE, offset_array_base,
	                           offset_array_index);
	mCc_assembly_store_int_val_at_index(out, offset_array_value);
}

void mCc_assembly_assign_array_float(FILE *out, struct mCc_assembly_data *data,
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
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	mCc_assembly_compute_index(out, INT_SIZE, offset_array_base,
	                           offset_array_index);
	mCc_assembly_store_float_val_at_index(out, offset_array_value);
}

void mCc_assembly_assign_array_bool(FILE *out, struct mCc_assembly_data *data,
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
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	mCc_assembly_compute_index(out, INT_SIZE, offset_array_base,
	                           offset_array_index);
	mCc_assembly_store_bool_val_at_index(out, offset_array_value);
}

void mCc_assembly_assign_array_string(FILE *out, struct mCc_assembly_data *data,
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
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	mCc_assembly_compute_index(out, INT_SIZE, offset_array_base,
	                           offset_array_index);
	mCc_assembly_store_string_val_at_index(out, offset_array_value);
}
