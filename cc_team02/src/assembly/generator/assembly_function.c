#include "assembly_function.h"

#include <string.h>

#include "assembly_general.h"
#include "assembly_template.h"
#include "assembly_utils.h"

static struct mCc_tac_identifier *
get_function_def_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

static struct mCc_tac_identifier *
get_next_function_def_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

static struct mCc_tac_identifier *
get_function_call_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

void mCc_assembly_start_function_def(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	char *function_def_label = get_function_def_identifier(tac_elem)->name;
	data->func_scope_counter++;

	mCc_assembly_new_function_def_enter(out, function_def_label);
}

void mCc_assembly_end_function_def(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *function_def_identifier =
	    get_function_def_identifier(tac_elem);
	char *function_def_label = function_def_identifier->name;

	const char *next_function_label =
	    mCc_assembly_get_next_function_label(tac_elem);
	// last function
	if (!get_next_function_def_identifier(tac_elem)) {
		mCc_assembly_last_function_leave(out, function_def_label,
		                                 data->func_scope_counter);
	} else {
		mCc_assembly_new_function_def_leave(out, function_def_label,
		                                    next_function_label,data->func_scope_counter);
	}
}

void mCc_assembly_function_call(FILE *out, struct mCc_assembly_data *data,
                                struct mCc_tac_element *tac_elem)
{
	char *function_def_label = get_function_call_identifier(tac_elem)->name;
	mCc_assembly_call_function(out, function_def_label);
}
