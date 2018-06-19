#include "assembly_param.h"

#include "stddef.h"

#include "assembly_general.h"
#include "assembly_utils.h"

/*
 * TODO:
 * - gibts hier überhaupt was zu tun?
 * - wird bei einem argument nicht bloß stack-speier reserviert?
 */

static struct mCc_tac_identifier *
get_param_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

void mCc_assembly_param_int_primitive(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem)
{
	mCc_assembly_allocate_int_on_stack(out, data, 1);
}

void mCc_assembly_param_float_primitive(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	mCc_assembly_allocate_float_on_stack(out, data, 1);
}

void mCc_assembly_param_bool_primitive(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	mCc_assembly_allocate_bool_on_stack(out, data, 1);
}

void mCc_assembly_param_string_primitive(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem)
{
	mCc_assembly_allocate_string_on_stack(out, data, NULL);
}

static struct mCc_tac_identifier *
get_size_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument2;
}

void mCc_assembly_param_int_array(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *size_identifier = get_size_identifier(tac_elem);
	mCc_assembly_allocate_int_on_stack(out, data, size_identifier->i_val);
}

void mCc_assembly_param_float_array(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *size_identifier = get_size_identifier(tac_elem);
	mCc_assembly_allocate_float_on_stack(out, data, size_identifier->i_val);
}

void mCc_assembly_param_bool_array(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *size_identifier = get_size_identifier(tac_elem);
	mCc_assembly_allocate_bool_on_stack(out, data, size_identifier->i_val);
}

void mCc_assembly_param_string_array(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *size_identifier = get_size_identifier(tac_elem);
	mCc_assembly_allocate_string_array_on_stack(out, data,
	                                            size_identifier->i_val);
}
