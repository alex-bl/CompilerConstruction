#include "assembly_param.h"
#include "assembly_utils.h"

static struct mCc_tac_identifier *
get_param_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

void mCc_assembly_param_int_primitive(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *param_identifier =
	    get_param_identifier(tac_elem);
	int param_offset = mCc_assembly_calc_stack_position(
	    param_identifier, data->current_stack_pos);
	mCc_assembly_add_param_int(out, param_offset);
}

void mCc_assembly_param_float_primitive(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *param_identifier =
	    get_param_identifier(tac_elem);
	int param_offset = mCc_assembly_calc_stack_position(
	    param_identifier, data->current_stack_pos);
	mCc_assembly_add_param_float(out, param_offset);
}

void mCc_assembly_param_bool_primitive(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *param_identifier =
	    get_param_identifier(tac_elem);
	int param_offset = mCc_assembly_calc_stack_position(
	    param_identifier, data->current_stack_pos);
	mCc_assembly_add_param_bool(out, param_offset);
}

void mCc_assembly_param_string_primitive(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *param_identifier =
	    get_param_identifier(tac_elem);
	mCc_assembly_add_param_int(out, param_identifier->name);
}

void mCc_assembly_param_int_array(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment here?*/
	mCc_assembly_param_int_primitive(out, data, tac_elem);
}

void mCc_assembly_param_float_array(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment here?*/
	mCc_assembly_param_float_primitive(out, data, tac_elem);
}

void mCc_assembly_param_bool_array(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment here?*/
	mCc_assembly_param_bool_primitive(out, data, tac_elem);
}

void mCc_assembly_param_string_array(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment here?*/
	mCc_assembly_param_string_primitive(out, data, tac_elem);
}
