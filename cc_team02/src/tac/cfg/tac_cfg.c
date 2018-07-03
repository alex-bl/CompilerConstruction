#include "mCc/tac_cfg.h"

#include "basic_tac.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mCc_tac_cfg_element *
mCc_tac_cfg_new_element(struct mCc_tac_element *tac_element,
                        struct mCc_tac_cfg_element *next_element_left,
                        struct mCc_tac_cfg_element *next_element_right)
{
	assert(tac_element);

	struct mCc_tac_cfg_element *tac_cfg_element =
	    malloc(sizeof(*tac_cfg_element));
	if (!tac_cfg_element) {
		return NULL;
	}

	tac_cfg_element->tac_element = tac_element;
	tac_cfg_element->next_cfg_element_left = next_element_left;
	tac_cfg_element->next_cfg_element_right = next_element_right;
	return tac_cfg_element;
}

struct mCc_tac_cfg_element *mCc_tac_cfg_generate(struct mCc_tac_element *tac)
{
	// iterate throw all function -> each function separate cfg
	struct mCc_tac_cfg_element *prev_cfg =
	    mCc_tac_cfg_new_element(tac, NULL, NULL);
	struct mCc_tac_element *tac_next_element = tac->tac_next_element;
	struct mCc_tac_cfg_element *first_cfg = prev_cfg;
	struct mCc_tac_cfg_element *cfg_function;
	while (tac_next_element != NULL) {
		if (tac_next_element->tac_operation ==
		    MCC_TAC_OPARATION_START_FUNCTION_DEF) {
			cfg_function = cfg_start_function(tac_next_element);
			// iterate through previous cfg to put the next on the end
			while (prev_cfg->next_cfg_element_left != NULL) {
				prev_cfg = prev_cfg->next_cfg_element_left;
			}
			prev_cfg->next_cfg_element_left = cfg_function;
			prev_cfg = cfg_function;
			// define the first cfg once
			/*if (first_cfg == NULL) {
			    first_cfg = cfg_function;
			}*/
		}
		tac_next_element = tac_next_element->tac_next_element;
	}

	return first_cfg;
}

static struct mCc_tac_cfg_element *
get_actual_cfg_element(struct mCc_tac_cfg_element *prev_cfg_element)
{
	while (prev_cfg_element->next_cfg_element_left != NULL) {
		prev_cfg_element = prev_cfg_element->next_cfg_element_left;
	}
	return prev_cfg_element;
}

/*
 * improvement:
 * left side always continues with next tac elements
 * if label where the jump points to comes up -> continue with the right side
 * storing the element where the left side ends and connect it with the end of
 * the right side
 *
 */

struct mCc_tac_cfg_element *
cfg_start_function(struct mCc_tac_element *tac_function_element)
{
	assert(tac_function_element);

	struct mCc_tac_element *tac_next_element = tac_function_element;
	struct mCc_tac_cfg_element *cfg_first_element;
	// struct mCc_tac_cfg_element *cfg_element;
	struct mCc_tac_cfg_element *prev_cfg_element;

	// building first element:
	cfg_first_element = cfg_connect_elements_to_left(NULL, tac_next_element);
	prev_cfg_element = cfg_first_element;
	tac_next_element = tac_next_element->tac_next_element;

	// TODO build up cfg for each function here
	while (tac_next_element->tac_operation != NULL &&
	       tac_next_element->tac_operation !=
	           MCC_TAC_OPARATION_END_FUNCTION_DEF) {
		// prev_cfg_element = cfg_element;

		if (prev_cfg_element != NULL) {

			tac_next_element =
			    cfg_connect_elements(prev_cfg_element, tac_next_element);

			// getting to the actual cfg_element, if there were any banches in
			// between:
			prev_cfg_element = get_actual_cfg_element(prev_cfg_element);
			/*while (prev_cfg_element->next_cfg_element_left != NULL) {
			    prev_cfg_element = prev_cfg_element->next_cfg_element_left;
			}*/
		}
	}
	// evaluating the last ..._END_FUNCTION_DEF element
	cfg_connect_elements_to_left(prev_cfg_element, tac_next_element);

	// returning one cfg for this function
	return cfg_first_element;
}

// TODO if handling
struct mCc_tac_element *
cfg_if_statement(struct mCc_tac_cfg_element *prev_cfg_element,
                 struct mCc_tac_element *tac_if_statement)
{
	assert(prev_cfg_element);
	assert(tac_if_statement);

	prev_cfg_element =
	    cfg_connect_elements_to_left(prev_cfg_element, tac_if_statement);
	tac_if_statement = tac_if_statement->tac_next_element;

	// struct mCc_tac_cfg_element *cfg_element;
	// iterates till the real branching into if and else comes:
	while (tac_if_statement->tac_operation !=
	           MCC_TAC_OPARATION_JUMP_NOT_EQUALS &&
	       tac_if_statement->tac_operation != MCC_TAC_OPARATION_JUMP &&
	       tac_if_statement->tac_operation != MCC_TAC_OPARATION_JUMP_EQUALS) {

		// new function for enabling nesting
		tac_if_statement =
		    cfg_connect_elements(prev_cfg_element, tac_if_statement);
		prev_cfg_element = get_actual_cfg_element(prev_cfg_element);
		// tac_if_statement = tac_if_statement->tac_next_element;

		/*cfg_element = mCc_tac_cfg_new_element(tac_if_statement, NULL, NULL);
		prev_cfg_element->next_cfg_element_left = cfg_element;
		prev_cfg_element = cfg_element;
		tac_if_statement = tac_if_statement->tac_next_element;*/
	}

	// remembering the cfg element with the branch
	struct mCc_tac_cfg_element *cfg_before_if =
	    cfg_connect_elements_to_left(prev_cfg_element, tac_if_statement);
	prev_cfg_element = cfg_before_if;
	tac_if_statement = tac_if_statement->tac_next_element;

	// evaluating the first/left side of the if
	while (tac_if_statement->tac_operation != MCC_TAC_OPARATION_LABEL_ELSE) {
		/*prev_cfg_element =
		    cfg_connect_elements_to_left(prev_cfg_element, tac_if_statement);
		tac_if_statement = tac_if_statement->tac_next_element;*/
		tac_if_statement =
		    cfg_connect_elements(prev_cfg_element, tac_if_statement);
		prev_cfg_element = get_actual_cfg_element(prev_cfg_element);
	}

	struct mCc_tac_cfg_element *cfg_after_if = prev_cfg_element;

	// going further to evaluate the right side, starting from the branch
	// element:
	struct mCc_tac_cfg_element *cfg_before_else =
	    mCc_tac_cfg_new_element(tac_if_statement, NULL, NULL);
	tac_if_statement = tac_if_statement->tac_next_element;
	cfg_before_if->next_cfg_element_right = cfg_before_else;
	prev_cfg_element = cfg_before_else;

	// evaluating the else/right side of the if
	while (tac_if_statement->tac_operation !=
	       MCC_TAC_OPARATION_LABEL_AFTER_ELSE) {
		/*prev_cfg_element =
		    cfg_connect_elements_to_left(prev_cfg_element, tac_if_statement);
		tac_if_statement = tac_if_statement->tac_next_element;*/
		tac_if_statement =
		    cfg_connect_elements(prev_cfg_element, tac_if_statement);
		prev_cfg_element = get_actual_cfg_element(prev_cfg_element);
	}

	// connecting the branches together in the end
	// conecting cfg_after_if and last element
	struct mCc_tac_cfg_element *cfg_after_else =
	    cfg_connect_elements_to_left(prev_cfg_element, tac_if_statement);
	tac_if_statement = tac_if_statement->tac_next_element;
	// if (tac_if_statement->tac_operation != MCC_TAC_OPARATION_JUMP) {
	// another step further
	cfg_after_else =
	    cfg_connect_elements_to_left(cfg_after_else, tac_if_statement);
	tac_if_statement = tac_if_statement->tac_next_element;
	//}
	// connecting to previous part
	cfg_after_if->next_cfg_element_left = cfg_after_else;

	return tac_if_statement;
}

// TODO while handling
struct mCc_tac_element *
cfg_while_statement(struct mCc_tac_cfg_element *prev_cfg_element,
                    struct mCc_tac_element *tac_while_statement)
{
	assert(prev_cfg_element);
	assert(tac_while_statement);

	// first while branch statement:
	struct mCc_tac_cfg_element *cfg_before_while =
	    cfg_connect_elements_to_left(prev_cfg_element, tac_while_statement);
	prev_cfg_element = cfg_before_while;
	tac_while_statement = tac_while_statement->tac_next_element;

	// from printer:
	//(cfg_element->tac_element->tac_operation ==    MCC_TAC_OPARATION_JUMP &&
	// cfg_element->tac_element->tac_next_element->tac_operation ==
	// MCC_TAC_OPARATION_LABEL_WHILE)

	// working through the while statement
	// while (tac_while_statement->tac_operation !=
	// MCC_TAC_OPARATION_LABEL_WHILE)
	while (!(tac_while_statement->tac_operation == MCC_TAC_OPARATION_JUMP &&
	         tac_while_statement->tac_next_element->tac_operation ==
	             MCC_TAC_OPARATION_LABEL_WHILE)) {
		tac_while_statement =
		    cfg_connect_elements(prev_cfg_element, tac_while_statement);
		prev_cfg_element = get_actual_cfg_element(prev_cfg_element);
		/*prev_cfg_element =
		    cfg_connect_elements_to_left(prev_cfg_element, tac_while_statement);
		tac_while_statement = tac_while_statement->tac_next_element;*/
	}

	// connecting before while and end of while in the end
	// cfg_before_while->next_cfg_element_right = prev_cfg_element;

	// going one element further to don't have a while label again
	prev_cfg_element =
	    cfg_connect_elements_to_left(prev_cfg_element, tac_while_statement);
	tac_while_statement = tac_while_statement->tac_next_element;

	// going one element further to don't have a while label again
	prev_cfg_element =
	    cfg_connect_elements_to_left(prev_cfg_element, tac_while_statement);
	tac_while_statement = tac_while_statement->tac_next_element;

	// connecting before while and end of while in the end
	cfg_before_while->next_cfg_element_right = prev_cfg_element;

	return tac_while_statement;
}

struct mCc_tac_element *
cfg_connect_elements(struct mCc_tac_cfg_element *prev_cfg_element,
                     struct mCc_tac_element *tac_next_element)
{
	assert(prev_cfg_element);
	assert(tac_next_element);

	if (tac_next_element->tac_operation == MCC_TAC_OPARATION_LABEL_IF) {
		tac_next_element = cfg_if_statement(prev_cfg_element, tac_next_element);
	} else if (tac_next_element->tac_operation ==
	               MCC_TAC_OPARATION_LABEL_WHILE &&
	           prev_cfg_element->tac_element->tac_operation !=
	               MCC_TAC_OPARATION_JUMP) {
		tac_next_element =
		    cfg_while_statement(prev_cfg_element, tac_next_element);
	} else {
		// if the is no right side, the cfg uses the left side without
		// any splits
		cfg_connect_elements_to_left(prev_cfg_element, tac_next_element);
		tac_next_element = tac_next_element->tac_next_element;

		/*cfg_element =
		    mCc_tac_cfg_new_element(tac_next_element, NULL, NULL);
		prev_cfg_element->next_cfg_element_left = cfg_element;
		tac_next_element = tac_next_element->tac_next_element;*/
	}

	return tac_next_element;
}

struct mCc_tac_cfg_element *
cfg_connect_elements_to_left(struct mCc_tac_cfg_element *prev_cfg_element,
                             struct mCc_tac_element *tac_statement)
{
	assert(tac_statement);

	struct mCc_tac_cfg_element *cfg_element =
	    mCc_tac_cfg_new_element(tac_statement, NULL, NULL);
	if (prev_cfg_element != NULL) {
		prev_cfg_element->next_cfg_element_left = cfg_element;
	}
	return cfg_element;
}

// function not needed?
/*void cfg_connect_elements(struct mCc_tac_cfg_element *previous_element,
                          struct mCc_tac_cfg_element *next_element_left,
                          struct mCc_tac_cfg_element *next_element_right)
{
    previous_element->next_cfg_element_left = next_element_left;
    previous_element->next_cfg_element_right = next_element_right;
}*/
