#include "assembly_return.h"

#include <stdbool.h>
#include <string.h>

#include "assembly_general.h"
#include "assembly_utils.h"
#include "config.h"

static struct mCc_tac_identifier *
get_return_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

static struct mCc_tac_identifier *
get_function_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument2;
}

static bool is_read_float(struct mCc_tac_identifier *function_call)
{
	return strcmp(function_call->name, "read_float") == 0;
}

void mCc_assembly_intermediate_return_int(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *identifier = get_return_identifier(tac_elem);
	int result_offset =
	    mCc_assembly_calc_stack_position(identifier, data->current_stack_pos);

	mCc_assembly_push_int(out, result_offset, DEFAULT_RETURN_REG);
}

void mCc_assembly_intermediate_return_float(FILE *out,
                                            struct mCc_assembly_data *data,
                                            struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *identifier = get_return_identifier(tac_elem);
	struct mCc_tac_identifier *call_identifier =
	    get_function_identifier(tac_elem);

	int result_offset =
	    mCc_assembly_calc_stack_position(identifier, data->current_stack_pos);

	// read float stores value on floating-point-stack
	if (is_read_float(call_identifier)) {
		mCc_assembly_push_float(out, result_offset);
	} else {
		mCc_assembly_push_int(out, result_offset, DEFAULT_RETURN_REG);
	}
}

void mCc_assembly_intermediate_return_bool(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *identifier = get_return_identifier(tac_elem);
	int result_offset =
	    mCc_assembly_calc_stack_position(identifier, data->current_stack_pos);

	mCc_assembly_push_int(out, result_offset, DEFAULT_RETURN_REG);
}

void mCc_assembly_intermediate_return_string(FILE *out,
                                             struct mCc_assembly_data *data,
                                             struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *identifier = get_return_identifier(tac_elem);
	int result_offset =
	    mCc_assembly_calc_stack_position(identifier, data->current_stack_pos);

	mCc_assembly_push_int(out, result_offset, DEFAULT_RETURN_REG);
}

void mCc_assembly_return_primitive_int(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *identifier = get_return_identifier(tac_elem);
	int result_offset =
	    mCc_assembly_calc_stack_position(identifier, data->current_stack_pos);
	mCc_assembly_prepare_return(out, result_offset);
	mCc_assembly_jump_to_return(out, data->func_scope_counter);
}

void mCc_assembly_return_primitive_float(FILE *out,
                                         struct mCc_assembly_data *data,
                                         struct mCc_tac_element *tac_elem)
{
	mCc_assembly_return_primitive_int(out, data, tac_elem);
}

void mCc_assembly_return_primitive_bool(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	mCc_assembly_return_primitive_int(out, data, tac_elem);
}

void mCc_assembly_return_primitive_string(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem)
{
//	struct mCc_tac_identifier *identifier = get_return_identifier(tac_elem);
//	mCc_assembly_prepare_return_string(out, identifier->name);
	mCc_assembly_return_primitive_int(out,data,tac_elem);
}

void mCc_assembly_return_array_int(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	mCc_assembly_return_primitive_int(out, data, tac_elem);
}

void mCc_assembly_return_array_float(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	mCc_assembly_return_primitive_float(out, data, tac_elem);
}

void mCc_assembly_return_array_bool(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
	mCc_assembly_return_primitive_bool(out, data, tac_elem);
}

void mCc_assembly_return_array_string(FILE *out, struct mCc_assembly_data *data,
                                      struct mCc_tac_element *tac_elem)
{
	mCc_assembly_return_primitive_string(out, data, tac_elem);
}
