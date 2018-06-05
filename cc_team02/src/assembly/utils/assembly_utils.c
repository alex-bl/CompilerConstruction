/**
 * Contains basic utils needed for assembly-generation
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic_tac.h"
#include "config.h"
#include "assembly_data.h"

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
	// TODO: required?
	return strlen(string);
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

int mCc_assembly_calc_stack_position(struct mCc_tac_identifier *identifier,
                                     int current_stack_ptr_pos)
{
	assert(identifier);
	return identifier->stack_offset - current_stack_ptr_pos;
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
	data->current_stack_pos -= offset;
}
