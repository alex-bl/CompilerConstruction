#include <assert.h>
#include <stdio.h>

#include "assembly_general.h"
#include "assembly_template.h"
#include "assembly_utils.h"
#include "config.h"

void mCc_assembly_assign_primitive_int(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	// TODO: on assignment => where is the variable?
	struct mCc_tac_identifier *var = tac_elem->tac_argument1;
	// TODO: on assignment => where is the int-val?
	struct mCc_tac_identifier *int_val = tac_elem->tac_argument2;
	// allocate space
	mCc_assembly_allocate_int_on_stack(out, data, 1);
	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_int(out, int_val->i_val, calculated_offset);
}

void mCc_assembly_assign_primitive_float(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	// TODO: on assignment => where is the variable?
	struct mCc_tac_identifier *var = tac_elem->tac_argument1;
	// TODO: on assignment => where is the int-val?
	struct mCc_tac_identifier *float_val = tac_elem->tac_argument2;
	// allocate space => required?
	mCc_assembly_allocate_float_on_stack(out, data, 1);
	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	mCc_assembly_assign_float(out, float_val->f_val, calculated_offset);
}

void mCc_assembly_assign_primitive_bool(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	// Treat bool as int
	mCc_assembly_assign_primitive_int(out, data, tac_elem);
}

void mCc_assembly_assign_primitive_string(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	// TODO: on assignment => where is the variable?
	struct mCc_tac_identifier *var = tac_elem->tac_argument1;
	// TODO: on assignment => where is the int-val?
	struct mCc_tac_identifier *string_val = tac_elem->tac_argument2;
	// TODO: keep string as param for compatability
	mCc_assembly_allocate_string_on_stack(out, data, NULL);
	int calculated_offset =
	    mCc_assembly_calc_stack_position(var, data->current_stack_pos);
	//TODO: string-val?
	mCc_assembly_assign_string(out, string_val->name, calculated_offset);
}
