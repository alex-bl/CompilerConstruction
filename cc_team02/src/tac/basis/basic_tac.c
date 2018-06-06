#include "basic_tac.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int label_count = 0;

//#include "ast_data_type.h"

// add another parameter for defining the next tac element?
// or how to define the next tac element?
// improving the whole tac structure
struct mCc_tac_element *tac_new_element(enum mCc_tac_operation operation,
                                        struct mCc_tac_identifier *argument1,
                                        struct mCc_tac_identifier *argument2,
                                        struct mCc_tac_identifier *result,
                                        enum mCc_tac_type tac_type,
                                        int tac_scope)
{
	// assert(result);

	struct mCc_tac_element *tac_element = malloc(sizeof(*tac_element));
	if (!tac_element) {
		return NULL;
	}
	tac_element->tac_operation = operation;
	tac_element->tac_argument1 = argument1;
	tac_element->tac_argument2 = argument2;
	tac_element->tac_result = result;
	tac_element->tac_type = tac_type;
	tac_element->tac_scope = tac_scope;
	tac_element->tac_next_element = NULL;
	return tac_element;
}

// connect the previous tac element to the current
void mCc_tac_connect_tac_entry(struct mCc_tac_element *previous_tac,
                               struct mCc_tac_element *tac)
{
	assert(previous_tac);
	assert(tac);

	previous_tac->tac_next_element = tac;
}

struct mCc_tac_identifier *tac_new_identifier(char *name)
{
	assert(name);

	struct mCc_tac_identifier *tac_identifier = malloc(sizeof(*tac_identifier));
	if (!tac_identifier) {
		return NULL;
	}
	tac_identifier->name = strndup(name, strlen(name));
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_STRING;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

struct mCc_tac_identifier *tac_new_identifier_float(double value)
{
	// assert(value);

	struct mCc_tac_identifier *tac_identifier = malloc(sizeof(*tac_identifier));
	if (!tac_identifier) {
		return NULL;
	}
	tac_identifier->f_val = value;
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_FLOAT;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

struct mCc_tac_identifier *tac_new_identifier_int(long value)
{
	// assert(value);

	struct mCc_tac_identifier *tac_identifier = malloc(sizeof(*tac_identifier));
	if (!tac_identifier) {
		return NULL;
	}
	tac_identifier->i_val = value;
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_INTEGER;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

struct mCc_tac_identifier *tac_new_identifier_bool(bool value)
{
	// assert(value);

	struct mCc_tac_identifier *tac_identifier = malloc(sizeof(*tac_identifier));
	if (!tac_identifier) {
		return NULL;
	}
	tac_identifier->b_val = value;
	tac_identifier->type = MCC_IDENTIFIER_TAC_TYPE_BOOL;
	// tac_identifier->stack_offset;
	return tac_identifier;
}

// helper function for getting the size of an int
int mCc_tac_helper_intlen(int var)
{
	int length;
	if (var < 10) {
		length = 1;
	} else if (var < 100) {
		length = 2;
	} else if (var < 1000) {
		length = 3;
	} else if (var < 10000) {
		length = 4;
	} else if (var < 100000) {
		length = 5;
	}
	return length;
}

// TODO: maybe here the the char has to be freed
// function for concatenate a name of a variable with the scope
struct mCc_tac_identifier *mCc_helper_concat_name_and_scope(char *name,
                                                            int scope)
{
	assert(name);
	assert(scope);

	// if (scope != NULL) {
	// puts scope level behind the variable name
	char new_name[strlen(name) + mCc_tac_helper_intlen(scope)];
	sprintf(new_name, "%s%d", name, scope);
	struct mCc_tac_identifier *tac_identifier = tac_new_identifier(new_name);
	// free(new_name);
	return tac_identifier;
	/*} else {
	    return tac_new_identifier(name);
	}*/
}

void mCc_tac_element_delete(struct mCc_tac_element *tac_element)
{
	assert(tac_element);

	if (tac_element->tac_argument1 != NULL) {
		mCc_tac_delete_identifier(tac_element->tac_argument1);
	}
	if (tac_element->tac_argument2 != NULL) {
		mCc_tac_delete_identifier(tac_element->tac_argument2);
	}
	if (tac_element->tac_result != NULL) {
		mCc_tac_delete_identifier(tac_element->tac_result);
	}
	free(tac_element);
}

void mCc_tac_delete(struct mCc_tac_element *tac_element)
{
	assert(tac_element);

	struct mCc_tac_element *next_tac_element;
	while (tac_element != NULL) {
		next_tac_element = tac_element->tac_next_element;
		mCc_tac_element_delete(tac_element);
		tac_element = next_tac_element;
	}
}

void mCc_tac_delete_identifier(struct mCc_tac_identifier *identifier)
{
	assert(identifier);

	if (identifier->type == MCC_IDENTIFIER_TAC_TYPE_STRING &&
	    identifier->name != NULL) {
		free(identifier->name);
	}
	free(identifier);
}

struct mCc_tac_identifier *
mCc_tac_create_from_tac_identifier(struct mCc_tac_identifier *identifier)
{
	assert(identifier);

	switch (identifier->type) {
	case MCC_IDENTIFIER_TAC_TYPE_INTEGER:
		return tac_new_identifier_int(identifier->i_val);
	case MCC_IDENTIFIER_TAC_TYPE_FLOAT:
		return tac_new_identifier_float(identifier->f_val);
	case MCC_IDENTIFIER_TAC_TYPE_BOOL:
		return tac_new_identifier_bool(identifier->b_val);
	case MCC_IDENTIFIER_TAC_TYPE_STRING:
		// default
		break;
	}
	return tac_new_identifier(identifier->name);
}

struct mCc_tac_element *
mCc_tac_create_new_lable(struct mCc_tac_identifier *identifier,
                         struct mCc_tac_element *previous_tac)
{
	// assert(identifier);
	assert(previous_tac);

	char label_name[1] = "l";
	struct mCc_tac_identifier *label =
	    mCc_helper_concat_name_and_scope(label_name, label_count);
	label_count++;
	struct mCc_tac_element *tac;
	if (identifier != NULL) {
		tac = tac_new_element(MCC_TAC_OPARATION_LABLE, identifier, NULL, label,
		                      MCC_TAC_TYPE_NO_TYPE, 0);

	} else {
		tac = tac_new_element(MCC_TAC_OPARATION_LABLE, NULL, NULL, label,
		                      MCC_TAC_TYPE_NO_TYPE, 0);
	}
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
