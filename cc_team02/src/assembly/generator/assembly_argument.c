#include "assembly_general.h"
#include "assembly_argument.h"
#include "assembly_utils.h"

static struct mCc_tac_identifier *
get_argument_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

void mCc_assembly_argument_int_primitive(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *argument_identifier =
	    get_argument_identifier(tac_elem);
	int argument_offset = mCc_assembly_calc_stack_position(
	    argument_identifier, data->current_stack_pos);
	mCc_assembly_add_argument_int(out, argument_offset);
}

void mCc_assembly_argument_float_primitive(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *argument_identifier =
	    get_argument_identifier(tac_elem);
	int argument_offset = mCc_assembly_calc_stack_position(
	    argument_identifier, data->current_stack_pos);
	mCc_assembly_add_argument_float(out, argument_offset);
}

void mCc_assembly_argument_bool_primitive(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *argument_identifier =
	    get_argument_identifier(tac_elem);
	int argument_offset = mCc_assembly_calc_stack_position(
	    argument_identifier, data->current_stack_pos);
	mCc_assembly_add_argument_bool(out, argument_offset);
}

void mCc_assembly_argument_string_primitive(FILE *out,
                                            struct mCc_assembly_data *data,
                                            struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *argument_identifier =
	    get_argument_identifier(tac_elem);
	mCc_assembly_add_argument_string(out, argument_identifier->name);
}

void mCc_assembly_argument_int_array(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *argument_identifier =
	    get_argument_identifier(tac_elem);
	int argument_offset = mCc_assembly_calc_stack_position(
	    argument_identifier, data->current_stack_pos);

	mCc_assembly_load_ptr(out, argument_offset, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_push_int_reg_on_stack(out, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_argument_float_array(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment here?*/
	mCc_assembly_argument_int_array(out, data, tac_elem);
}

void mCc_assembly_argument_bool_array(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment here?*/
	mCc_assembly_argument_int_array(out, data, tac_elem);
}

void mCc_assembly_argument_string_array(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment here?*/
	mCc_assembly_argument_int_array(out, data, tac_elem);
}
