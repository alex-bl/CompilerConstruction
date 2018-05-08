#include "mCc/ast/tac/ast_basic_tac.h"

#include <assert.h>
#include <stdio.h>

#include "mCc/ast/basis/ast_data_type.h"



struct mCc_tac_elmenet *tac_elmenet(enum mCc_tac_operation *operation, struct mCc_ast_identifier *argument1,
		struct mCc_ast_identifier *argument2, struct mCc_ast_identifier *result)
{
	struct mCc_tac_elmenet *tac_elmenet = malloc(sizeof(tac_elmenet));
	if (!tac_elmenet) {
		return NULL;
	}
	enum mCc_tac_operation tac_operation=operation;
	struct mCc_ast_identifier tac_argument1=argument1;
	struct mCc_ast_identifier tac_argument2=argument2;
	struct mCc_ast_identifier tac_result=result;
	return tac_elmenet;
}


void mCc_tac_element_delete(struct mCc_tac_elmenet *tac_elmenet)
{
	assert(tac_elmenet);

	mCc_tac_delete_operation(tac_elmenet->tac_operation);
	mCc_ast_delete_identifier(tac_elmenet->tac_argument1);
	mCc_ast_delete_identifier(tac_elmenet->tac_argument2);
	mCc_ast_delete_identifier(tac_elmenet->tac_result);
	free(tac_elmenet);
}

const char *tac_data_type(enum mCc_ast_data_type type)
{
	assert(type);

	return "unknown type";
}

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

