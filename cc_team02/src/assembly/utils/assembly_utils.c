/**
 * Contains basic utils needed for assembly-generation
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

size_t mCc_assembly_calc_int_space(int nr_of)
{
	/*
	 * TODO: use INT_SIZE
	 */
	return 0;
}

size_t mCc_assembly_calc_bool_space(int nr_of)
{
	/*
	 * TODO: use INT_SIZE
	 */
	return 0;
}

size_t mCc_assembly_calc_float_space(int nr_of)
{
	/*
	 * TODO: use FLOAT_SIZE
	 */
	return 0;
}

size_t mCc_assembly_calc_string_space(const char *string)
{
	/*
	 * TODO: use strlen?
	 */
	return 0;
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
	 */
	return 0;
}

int mCc_assembly_calc_stack_position(struct mCc_tac_identifier *identifier,
                                     int current_stack_ptr_pos)
{
	/*
	 * TODO:
	 * - assertions
	 * - result = current-pos - identifier-offset
	 */

	return 0;
}

const char *
mCc_assembly_get_next_function_label(struct mCc_tac_identifier *identifier)
{
	/*
	 * TODO:
	 * - Store next-function-label somewhere in tac-elem
	 * - Iterate through it
	 */
	return "";
}
