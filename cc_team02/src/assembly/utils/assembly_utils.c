#include "assembly_utils.h"

/**
 * Contains basic utils needed for assembly-generation
 */

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic_tac.h"
#include "config.h"
#include "log.h"

static struct mCc_tac_identifier *
get_function_label_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result;
}

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
	// TODO: => always 8?
	return STRING_SIZE;
}

/*
 * NOTE:
 * Currently unused, but maybe useful in the future
 *
 */
size_t mCc_assembly_calc_param_space(struct mCc_tac_element *function_def)
{
	return 0;
}

int mCc_assembly_calc_stack_pos_param(struct mCc_tac_identifier *identifier)
{
	//+4 is return address
	return identifier->stack_offset; // + BASE_OFFSET_PARAMS; => directly done
	                                 // at assembly_offset
}

int mCc_assembly_calc_stack_position(struct mCc_tac_identifier *identifier,
                                     int current_stack_ptr_pos)
{
	assert(identifier);
	if (identifier->is_param) {
		return mCc_assembly_calc_stack_pos_param(identifier);
	}
	// NOTE: current_stack_ptr_pos useless right now. Maybe sometimes useful
	return (identifier->stack_offset) * -1;
}

const char *
mCc_assembly_get_next_function_label(struct mCc_tac_element *tac_elem)
{
	assert(tac_elem);
	struct mCc_tac_element *next_tac_elem = tac_elem;
	while (next_tac_elem) {
		if (next_tac_elem->tac_operation == MCC_TAC_OPARATION_LABEL_FUNCTION) {
			return get_function_label_identifier(next_tac_elem)->name;
		}
		next_tac_elem = next_tac_elem->tac_next_element;
	}

	log_warn("No next function?");
	return "";
}

// NOTE: currently not used
void mCc_assembly_adjust_stack_pointer(int offset,
                                       struct mCc_assembly_data *data)
{
	data->current_stack_pos += offset;
}

struct mCc_assembly_argument_list *
mCc_assembly_create_new_arg_list_elem(int scope)
{
	struct mCc_assembly_argument_list *elem = malloc(sizeof(*elem));
	if (!elem) {
		log_error("Malloc failed");
		return NULL;
	}
	elem->open_scope = scope;
	elem->next = NULL;
	return elem;
}

struct mCc_assembly_argument_list *
mCc_assembly_prepend_arg_list_elem(struct mCc_assembly_argument_list *actual,
                                   struct mCc_tac_element *to_prepend,
                                   int scope)
{
	struct mCc_assembly_argument_list *elem =
	    mCc_assembly_create_new_arg_list_elem(scope);
	if (elem) {
		elem->argument = to_prepend;
		if (actual) {
			elem->next = actual;
		} else {
			elem->next = NULL;
		}
	}
	return elem;
}

void mCc_assembly_free_arg_list_elem(struct mCc_assembly_argument_list *to_free)
{
	free(to_free);
}
