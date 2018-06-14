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

static bool is_main(char *function_def_label)
{
	return strcmp(function_def_label, "main") == 0;
}

void mCc_assembly_start_function_def(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	char *function_def_label = get_function_def_identifier(tac_elem)->name;

	if (is_main(function_def_label)) {
		mCc_assembly_main_function_enter(out);
	} else {
		mCc_assembly_new_function_def_enter(out, function_def_label);
	}
}

void mCc_assembly_end_function_def(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *function_def_identifier =
	    get_function_def_identifier(tac_elem);
	char *function_def_label = function_def_identifier->name;

	const char *next_function_label =
	    mCc_assembly_get_next_function_label(function_def_identifier);
	if (is_main(function_def_label)) {
		mCc_assembly_main_function_leave(out);
	} else {
		mCc_assembly_new_function_def_leave(out, function_def_label,
		                                    next_function_label);
	}
}

void mCc_assembly_function_call(FILE *out, struct mCc_assembly_data *data,
                                struct mCc_tac_element *tac_elem)
{
	char *function_def_label = tac_elem->tac_argument1->name;
	mCc_assembly_call_function(out, function_def_label);
}
