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

	//space for the tmp-variable
	mCc_assembly_allocate_int_on_stack(out, data, 1);

	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_int(out, int_val->i_val, calculated_offset);
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

void mCc_assembly_pseudo_assign_float_literal(FILE *out,
                                              struct mCc_assembly_data *data,
                                              struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_identifier *var = get_assign_dest(tac_elem);
	struct mCc_tac_identifier *float_val = get_literal_val(tac_elem);

	//space for the tmp-variable
	mCc_assembly_allocate_float_on_stack(out, data, 1);

	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_int(out, float_val->f_val, calculated_offset);
}

void mCc_assembly_assign_primitive_bool(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	// Treat bool as int
	mCc_assembly_assign_primitive_int(out, data, tac_elem);
}

void mCc_assembly_pseudo_assign_bool_literal(FILE *out,
                                             struct mCc_assembly_data *data,
                                             struct mCc_tac_element *tac_elem)
{
	// TODO: separate handling?
	mCc_assembly_pseudo_assign_int_literal(out, data, tac_elem);
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

	//space for the tmp-variable
	mCc_assembly_allocate_string_on_stack(out, data, string_val->s_val);

	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_string(out, string_val->s_val, calculated_offset);
}
