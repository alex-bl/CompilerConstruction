#include "assembly_offset.h"

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "assembly_utils.h"
#include "basic_tac.h"
#include "config.h"
#include "log.h"

/*
 * TODO:
 * - wie kann man feststellen, welchen typ der tac-identifier hat? (speziell die
 * var-typen)
 * - setzen des offsets von l0 noch fehlerhaft?
 */
static struct mCc_assembly_offset_holder init_offset_info()
{
	struct mCc_assembly_offset_holder info;
	map_init(&info.offset_table);
	map_init(&info.param_table);
	map_init(&info.function_table);

	info.actual_offset = 0;
	return info;
}

static struct mCc_tac_identifier *get_param(struct mCc_tac_element *elem)
{
	return elem->tac_argument1;
}

static struct mCc_tac_identifier *get_function_def(struct mCc_tac_element *elem)
{
	return elem->tac_result;
}

static bool param_contained(struct mCc_tac_identifier *identifier,
                            struct mCc_assembly_offset_holder *info)
{
	return map_get(&info->param_table, identifier->name) != NULL;
}

static bool function_def_contained(struct mCc_tac_identifier *identifier,
                                   struct mCc_assembly_offset_holder *info)
{
	return map_get(&info->function_table, identifier->name) != NULL;
}

static void param_add_new_entry(struct mCc_tac_identifier *identifier,
                                struct mCc_assembly_offset_holder *info)
{
	map_set(&info->param_table, identifier->name, 0);
}

static void function_def_add_new_entry(struct mCc_tac_identifier *identifier,
                                       struct mCc_assembly_offset_holder *info)
{
	map_set(&info->function_table, identifier->name, 0);
}

static size_t get_tac_elem_size(enum mCc_tac_type type)
{
	switch (type) {
	case MCC_TAC_TYPE_INTEGER: return mCc_assembly_calc_int_space(1);
	case MCC_TAC_TYPE_FLOAT: return mCc_assembly_calc_float_space(1);
	case MCC_TAC_TYPE_BOOL: return mCc_assembly_calc_bool_space(1);
	case MCC_TAC_TYPE_STRING: return mCc_assembly_calc_string_space(NULL);
	}
	log_warn("No type?");
	return 0;
}

static bool identifier_available(struct mCc_tac_identifier *identifier)
{
	return identifier != NULL;
}

static bool identifier_denotes_var(struct mCc_tac_identifier *identifier)
{
	return identifier->type == MCC_IDENTIFIER_TAC_TYPE_VAR;
}

static bool
identifier_requires_offset_calculation(struct mCc_tac_identifier *identifier)
{
	return identifier_available(identifier) &&
	       identifier_denotes_var(identifier);
}

static bool tac_offset_contained(struct mCc_tac_identifier *identifier,
                                 struct mCc_assembly_offset_holder *info)
{
	return map_get(&info->offset_table, identifier->name) != NULL;
}

static int get_tac_offset(struct mCc_tac_identifier *identifier,
                          struct mCc_assembly_offset_holder *info)
{
	return *(map_get(&info->offset_table, identifier->name));
}

static int calc_new_offset(enum mCc_tac_type type,
                           struct mCc_assembly_offset_holder *info)
{
	size_t size = get_tac_elem_size(type);
	return info->actual_offset + size;
}

static void add_new_entry(struct mCc_tac_identifier *identifier,
                          struct mCc_assembly_offset_holder *info,
                          int new_offset)
{
	map_set(&info->offset_table, identifier->name, new_offset);
}

static void adjust_identifier_offset(struct mCc_tac_identifier *identifier,
                                     int offset)
{
	identifier->stack_offset = offset;
}

static void
process_identifier_offset_calculation(struct mCc_tac_identifier *identifier,
                                      enum mCc_tac_type type,
                                      struct mCc_assembly_offset_holder *info)
{
	int stack_offset = 0;
	if (tac_offset_contained(identifier, info)) {
		stack_offset = get_tac_offset(identifier, info);
		log_debug("Identifier '%s' found with offset %d", identifier->name,
		          stack_offset);
	} else {
		stack_offset = calc_new_offset(type, info);
		// set new offset
		info->actual_offset = stack_offset;

		add_new_entry(identifier, info, stack_offset);
		log_debug("New entry for identifier '%s' with new offset %d",
		          identifier->name, stack_offset);
	}
	adjust_identifier_offset(identifier, stack_offset);
}

static void handle_identifier(struct mCc_tac_identifier *identifier,
                              enum mCc_tac_type type,
                              struct mCc_assembly_offset_holder *info)
{
	if (identifier_requires_offset_calculation(identifier)) {
		if (function_def_contained(identifier, info)) {
			identifier->type = MCC_IDENTIFIER_TAC_TYPE_FUNCTION_CALL;
		} else {
			process_identifier_offset_calculation(identifier, type, info);
		}

		if (param_contained(identifier, info)) {
			identifier->is_param = true;
		}
	}
}

static bool tac_elem_contains_stack_vars(struct mCc_tac_element *element)
{
	// TODO: which operations allowed here? => extend them

	switch (element->tac_operation) {
	case MCC_TAC_OPARATION_LABEL_ARGUMENT:

	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_INT:
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_FLOAT:
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_BOOL:
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_STRING:
	case MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_INT:
	case MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_FLOAT:
	case MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_BOOL:
	case MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_STRING:

	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT:
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_FLOAT:
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL:
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_STRING:

	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_INT:
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_FLOAT:
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_BOOL:
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_STRING:

	case MCC_TAC_OPARATION_BINARY_OP_ADD_INT:
	case MCC_TAC_OPARATION_BINARY_OP_SUB_INT:
	case MCC_TAC_OPARATION_BINARY_OP_MUL_INT:
	case MCC_TAC_OPARATION_BINARY_OP_DIV_INT:

	case MCC_TAC_OPARATION_BINARY_OP_ADD_FLOAT:
	case MCC_TAC_OPARATION_BINARY_OP_SUB_FLOAT:
	case MCC_TAC_OPARATION_BINARY_OP_MUL_FLOAT:
	case MCC_TAC_OPARATION_BINARY_OP_DIV_FLOAT:

	case MCC_TAC_OPARATION_EQUALS_INT:
	case MCC_TAC_OPARATION_EQUALS_FLOAT:
	case MCC_TAC_OPARATION_EQUALS_BOOL:
	case MCC_TAC_OPARATION_NOT_EQUALS_INT:
	case MCC_TAC_OPARATION_NOT_EQUALS_FLOAT:
	case MCC_TAC_OPARATION_NOT_EQUALS_BOOL:
	case MCC_TAC_OPARATION_GREATER_INT:
	case MCC_TAC_OPARATION_GREATER_FLOAT:
	case MCC_TAC_OPARATION_LESS_INT:
	case MCC_TAC_OPARATION_LESS_FLOAT:
	case MCC_TAC_OPARATION_GREATER_EQUALS_INT:
	case MCC_TAC_OPARATION_GREATER_EQUALS_FLOAT:
	case MCC_TAC_OPARATION_LESS_EQUALS_INT:
	case MCC_TAC_OPARATION_LESS_EQUALS_FLOAT:
	case MCC_TAC_OPARATION_BINARY_AND:
	case MCC_TAC_OPARATION_BINARY_OR:

	case MCC_TAC_OPARATION_UNARY_MINUS_INT:
	case MCC_TAC_OPARATION_UNARY_MINUS_FLOAT:
	case MCC_TAC_OPARATION_UNARY_NEGATION:
	case MCC_TAC_OPARATION_JUMP_NOT_EQUALS:
	case MCC_TAC_OPARATION_JUMP_EQUALS:

	case MCC_TAC_OPARATION_RETURN_PRIMITIVE_INT:
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_FLOAT:
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_BOOL:
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_STRING:
	case MCC_TAC_OPARATION_RETURN_ARRAY_INT:
	case MCC_TAC_OPARATION_RETURN_ARRAY_FLOAT:
	case MCC_TAC_OPARATION_RETURN_ARRAY_BOOL:
	case MCC_TAC_OPARATION_RETURN_ARRAY_STRING:

	case MCC_TAC_OPARATION_INTERMEDIATE_RETURN_INT:
	case MCC_TAC_OPARATION_INTERMEDIATE_RETURN_FLOAT:
	case MCC_TAC_OPARATION_INTERMEDIATE_RETURN_BOOL:
	case MCC_TAC_OPARATION_INTERMEDIATE_RETURN_STRING:

	case MCC_TAC_OPARATION_PARAM_INT_PRIMITIVE:
	case MCC_TAC_OPARATION_PARAM_FLOAT_PRIMITIVE:
	case MCC_TAC_OPARATION_PARAM_BOOL_PRIMITIVE:
	case MCC_TAC_OPARATION_PARAM_STRING_PRIMITIVE:
	case MCC_TAC_OPARATION_PARAM_INT_ARRAY:
	case MCC_TAC_OPARATION_PARAM_FLOAT_ARRAY:
	case MCC_TAC_OPARATION_PARAM_BOOL_ARRAY:
	case MCC_TAC_OPARATION_PARAM_STRING_ARRAY: return true;
	default: return false;
	}

	return false;
}

static bool tac_elem_is_param(struct mCc_tac_element *element)
{
	// TODO: which operations allowed here? => extend them

	switch (element->tac_operation) {
	case MCC_TAC_OPARATION_PARAM_INT_PRIMITIVE:
	case MCC_TAC_OPARATION_PARAM_FLOAT_PRIMITIVE:
	case MCC_TAC_OPARATION_PARAM_BOOL_PRIMITIVE:
	case MCC_TAC_OPARATION_PARAM_STRING_PRIMITIVE:
	case MCC_TAC_OPARATION_PARAM_INT_ARRAY:
	case MCC_TAC_OPARATION_PARAM_FLOAT_ARRAY:
	case MCC_TAC_OPARATION_PARAM_BOOL_ARRAY:
	case MCC_TAC_OPARATION_PARAM_STRING_ARRAY: return true;
	default: return false;
	}

	return false;
}

static bool tac_elem_is_function_def(struct mCc_tac_element *element)
{
	return element->tac_operation == MCC_TAC_OPARATION_LABEL_FUNCTION;
}

static void handle_tac_elem(struct mCc_tac_element *tac_element,
                            struct mCc_assembly_offset_holder *info)
{
	// if it is a param => mark it as param for later offset-calc
	if (tac_elem_is_param(tac_element)) {
		struct mCc_tac_identifier *identifier_param = get_param(tac_element);
		param_add_new_entry(identifier_param, info);
	}

	if (tac_elem_is_function_def(tac_element)) {
		struct mCc_tac_identifier *identifier_param =
		    get_function_def(tac_element);
		function_def_add_new_entry(identifier_param, info);
	}

	if (tac_elem_contains_stack_vars(tac_element)) {
		enum mCc_tac_type type = tac_element->tac_type;
		handle_identifier(tac_element->tac_argument1, type, info);
		handle_identifier(tac_element->tac_argument2, type, info);
		handle_identifier(tac_element->tac_result, type, info);
	}
}

static bool offset_reset_required(struct mCc_tac_element *tac_element)
{
	/*
	 * MCC_TAC_OPARATION_START_FUNCTION_DEF is not the "real start" because of
	 * the parameter list
	 */
	return tac_element->tac_operation == MCC_TAC_OPARATION_LABEL_FUNCTION;
}

void mCc_assembly_calculate_stack_offsets(
    struct mCc_tac_element *first_tac_element)
{
	struct mCc_assembly_offset_holder info = init_offset_info();
	struct mCc_tac_element *next_tac_element = first_tac_element;

	while (next_tac_element) {
		if (offset_reset_required(next_tac_element)) {
			log_debug("Resetting offset while entering new function def '%s'",
			          next_tac_element->tac_result->name);
			info.actual_offset = 0;
		}
		handle_tac_elem(next_tac_element, &info);
		next_tac_element = next_tac_element->tac_next_element;
	}

	map_deinit(&info.offset_table);
	map_deinit(&info.param_table);
	map_deinit(&info.function_table);
}
