#include "assembly_jump.h"

#include "assembly_general.h"
#include "assembly_utils.h"

// TODO: where is jump-dest?
static char *get_jump_dest(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result->name;
}

static struct mCc_tac_identifier *
get_condition_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

/*
 * TODO:
 * Wirds nicht zu kompliziert, immer rauszufinden, welche op gerade gemacht
 * wurde?
 * => jump true oder jump false einfacher?
 * => "condition" sowieso in einem "single-boolean"?
 */

void mCc_assembly_generate_jump(FILE *out, struct mCc_assembly_data *data,
                                struct mCc_tac_element *tac_elem)
{
	mCc_assembly_jump(out, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_equals(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *condition_identifier =
	    get_condition_identifier(tac_elem);
	int condition_offset = mCc_assembly_calc_stack_position(
	    condition_identifier, data->current_stack_pos);

	mCc_assembly_compare_bool(out, condition_offset, true);

	mCc_assembly_jump_equals(out, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_not_equals(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *condition_identifier =
	    get_condition_identifier(tac_elem);
	int condition_offset = mCc_assembly_calc_stack_position(
	    condition_identifier, data->current_stack_pos);
	;
	mCc_assembly_compare_bool(out, condition_offset, true);

	mCc_assembly_jump_not_equals(out, get_jump_dest(tac_elem));
}
