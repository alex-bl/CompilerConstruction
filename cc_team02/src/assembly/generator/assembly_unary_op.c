#include "assembly_unary_op.h"

#include "assembly_general.h"
#include "assembly_utils.h"
#include "config.h"

static struct mCc_tac_identifier *
get_unary_op_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

static struct mCc_tac_identifier *
get_unary_op_result_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

void mCc_assembly_generate_unary_minus_int(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *unary_op_identifier =
	    get_unary_op_identifier(tac_elem);
	struct mCc_tac_identifier *result_identifier =
	    get_unary_op_result_identifier(tac_elem);

	int arg_offset = mCc_assembly_calc_stack_position(unary_op_identifier,
	                                                  data->current_stack_pos);
	int result_offset = mCc_assembly_calc_stack_position(
	    result_identifier, data->current_stack_pos);

	mCc_assembly_allocate_int_on_stack(out, data, 1);

	mCc_assembly_load_int(out, arg_offset, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_unary_minus_int(out);

	mCc_assembly_push_int(out, result_offset, DEFAULT_ACCUMULATOR_OPERAND);
}

void mCc_assembly_generate_unary_minus_float(FILE *out,
                                             struct mCc_assembly_data *data,
                                             struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *unary_op_identifier =
	    get_unary_op_identifier(tac_elem);
	struct mCc_tac_identifier *result_identifier =
	    get_unary_op_result_identifier(tac_elem);

	int arg_offset = mCc_assembly_calc_stack_position(unary_op_identifier,
	                                                  data->current_stack_pos);
	int result_offset = mCc_assembly_calc_stack_position(
	    result_identifier, data->current_stack_pos);

	mCc_assembly_allocate_float_on_stack(out, data, 1);

	mCc_assembly_load_float(out, arg_offset);
	mCc_assembly_unary_minus_float(out);

	mCc_assembly_push_float(out, result_offset);
}

void mCc_assembly_generate_unary_negation(FILE *out,
                                          struct mCc_assembly_data *data,
                                          struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *unary_op_identifier =
	    get_unary_op_identifier(tac_elem);
	struct mCc_tac_identifier *result_identifier =
	    get_unary_op_result_identifier(tac_elem);
	int arg_offset = mCc_assembly_calc_stack_position(unary_op_identifier,
	                                                  data->current_stack_pos);
	int result_offset = mCc_assembly_calc_stack_position(
	    result_identifier, data->current_stack_pos);

	mCc_assembly_allocate_bool_on_stack(out, data, 1);
	mCc_assembly_load_int(out, arg_offset, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_unary_negation(out);


	mCc_assembly_push_int(out, result_offset, DEFAULT_ACCUMULATOR_OPERAND);
}
