/**
 * Contains basic utils needed for assembly-generation
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembly_data.h"
#include "basic_tac.h"
#include "config.h"

size_t mCc_assembly_calc_int_space(int nr_of)
{
	return nr_of * INT_SIZE;
}

size_t mCc_assembly_calc_bool_space(int nr_of)
{
	// bool is treated as integer
	return mCc_assembly_calc_int_space(nr_of);
}

size_t mCc_assembly_calc_float_space(int nr_of)
{
	return nr_of * FLOAT_SIZE;
}

size_t mCc_assembly_calc_string_space(const char *string)
{
	// TODO: required? => always 8?
	return STRING_SIZE;
}

size_t mCc_assembly_calc_param_space(struct mCc_tac_element *function_def)
{
	/*
	 * TODO:
	 * - use INT_SIZE
	 * - use FLOAT_SIZE
	 * - consider string
	 * - consider arrays
	 * - what about string-arrays?
	 *
	 * => requires changes on tac!
	 */
	return 0;
}

int mCc_assembly_calc_stack_pos_param(struct mCc_tac_identifier *identifier)
{
	//+4 is return address
	return identifier->stack_offset + BASE_OFFSET_PARAMS;
}

int mCc_assembly_calc_stack_position(struct mCc_tac_identifier *identifier,
                                     int current_stack_ptr_pos)
{
	assert(identifier);
	if (identifier->is_param) {
		return mCc_assembly_calc_stack_pos_param(identifier);
	}
	return current_stack_ptr_pos - identifier->stack_offset;
}

const char *
mCc_assembly_get_next_function_label(struct mCc_tac_identifier *identifier)
{
	assert(identifier);
	/*
	 * TODO:
	 * - Store next-function-label somewhere in tac-elem
	 * - Iterate through it
	 *
	 * => requires changes on tac!
	 */
	return "";
}

void mCc_assembly_adjust_stack_pointer(int offset,
                                       struct mCc_assembly_data *data)
{
	// TODO: check this
	data->current_stack_pos += offset;
}
