#include "basic_tac.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//#include "ast_data_type.h"

/*struct mCc_tac_element tac_element_new_element(enum mCc_tac_operation operation, struct mCc_tac_identifier *argument1,
		struct mCc_tac_identifier *argument2, struct mCc_tac_identifier *result)
{
	struct mCc_tac_element *tac_element = malloc(sizeof(tac_element));
	if (!tac_element) {
		//return NULL;
	}
	enum mCc_tac_operation tac_operation=operation;
	struct mCc_tac_identifier tac_argument1=argument1;
	struct mCc_tac_identifier tac_argument2=argument2;
	struct mCc_tac_identifier tac_result=result;
	//return tac_element;
}

struct mCc_tac_identifier tac_identifier_new_identifier() {
	struct mCc_tac_identifier *tac_identifier = malloc(sizeof(tac_identifier));
	if (!tac_identifier) {
		//return NULL;
	}
	char *name;
	//return tac_identifier;
}
*/

struct mCc_tac_element *tac_new_element(enum mCc_tac_operation operation, struct mCc_tac_identifier *argument1,
		struct mCc_tac_identifier *argument2, struct mCc_tac_identifier *result)
{
	struct mCc_tac_element *tac_element = malloc(sizeof(*tac_element));
	if (!tac_element) {
		return NULL;
	}
	tac_element->tac_operation=operation;
	tac_element->tac_argument1=argument1;
	tac_element->tac_argument2=argument2;
	tac_element->tac_result=result;
	return tac_element;
}


void mCc_tac_element_delete(struct mCc_tac_element *tac_element)
{
	assert(tac_element);

	//mCc_tac_delete_operation(tac_element->tac_operation);
	mCc_tac_delete_identifier(tac_element->tac_argument1);
	mCc_tac_delete_identifier(tac_element->tac_argument2);
	mCc_tac_delete_identifier(tac_element->tac_result);
	free(tac_element);
}

/*void mCc_tac_delete_operation(enum mCc_tac_operation operation) {
	free(operation);
}*/

void mCc_tac_delete_identifier(struct mCc_tac_identifier *identifier) {
	free(identifier);
}

/*const char *tac_data_type(enum mCc_ast_data_type type)
{
	assert(type);

	return "unknown type";
}*/

/*void tac_print() {

	printf();
}*/

/*void tac_begin(FILE *out)
{
	assert(out);

}

void tac_end(FILE *out)
{
	assert(out);

}

void tac_node(FILE *out, const void *node, const char *label)
{
	assert(out);
	assert(node);
	assert(label);

}

void tac_edge(FILE *out, const void *src_node, const void *dst_node,
                    const char *label)
{
	assert(out);
	assert(src_node);
	assert(dst_node);
	assert(label);

}

void tac_edge_if_dest_exists(FILE *out, const void *src_node,
                                   const void *dst_node, const char *label)
{
	assert(out);
	assert(src_node);
	assert(dst_node);
	assert(label);

}*/

