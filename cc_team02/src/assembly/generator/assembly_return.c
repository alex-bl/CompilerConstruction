#include "assembly_return.h"

#include "assembly_utils.h"
#include "assembly_general.h"

static struct mCc_tac_identifier *
get_return_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

void mCc_assembly_return_primitive_int(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *identifier = get_return_identifier(tac_elem);
	int result_offset =
	    mCc_assembly_calc_stack_position(identifier, data->current_stack_pos);
	mCc_assembly_prepare_return(out, result_offset);
}

void mCc_assembly_return_primitive_float(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment?*/
	mCc_assembly_return_primitive_int(out, data, tac_elem);
}

void mCc_assembly_return_primitive_bool(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment?*/
	mCc_assembly_return_primitive_int(out, data, tac_elem);
}

void mCc_assembly_return_primitive_string(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *identifier = get_return_identifier(tac_elem);
	mCc_assembly_prepare_return_string(out, identifier->name);
}

void mCc_assembly_return_array_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment?*/
	mCc_assembly_return_primitive_int(out, data, tac_elem);
}

void mCc_assembly_return_array_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment?*/
	mCc_assembly_return_primitive_float(out, data, tac_elem);
}

void mCc_assembly_return_array_bool(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment?*/
	mCc_assembly_return_primitive_bool(out, data, tac_elem);
}

void mCc_assembly_return_array_string(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem)
{
	/*TODO: special treatment?*/
	mCc_assembly_return_primitive_string(out, data, tac_elem);
}
