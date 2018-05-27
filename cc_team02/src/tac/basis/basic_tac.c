#include "basic_tac.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	//tac_identifier->stack_offset;
	return tac_identifier;
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

	if (identifier->name != NULL) {
		free(identifier->name);
	}
	free(identifier);
}
