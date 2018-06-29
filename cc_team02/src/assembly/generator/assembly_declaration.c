#include "assembly_declaration.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "assembly_general.h"

// TODO: correct?
static size_t get_array_size(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument2->i_val;
}

void mCc_assembly_declare_primitive_int(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	//mCc_assembly_allocate_int_on_stack(out, data, 1);
}

void mCc_assembly_declare_primitive_float(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem)
{
	//mCc_assembly_allocate_float_on_stack(out, data, 1);
}

void mCc_assembly_declare_primitive_bool(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem)
{
	//mCc_assembly_allocate_bool_on_stack(out, data, 1);
}

void mCc_assembly_declare_primitive_string(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem)
{
	//mCc_assembly_allocate_string_on_stack(out, data, NULL);
}

void mCc_assembly_declare_array_int(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
	//mCc_assembly_allocate_int_on_stack(out, data, get_array_size(tac_elem));
}

void mCc_assembly_declare_array_float(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem)
{
	//mCc_assembly_allocate_float_on_stack(out, data, get_array_size(tac_elem));
}

void mCc_assembly_declare_array_bool(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	//mCc_assembly_allocate_bool_on_stack(out, data, get_array_size(tac_elem));
}

void mCc_assembly_declare_array_string(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	//TODO: how to deal with string-arrays?
	//mCc_assembly_allocate_string_on_stack(out, data, NULL);
}
