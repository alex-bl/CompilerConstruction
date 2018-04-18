#include "mCc/ast/tac/ast_basic_tac.h"

#include <assert.h>
#include <stdio.h>

#include "mCc/ast/basis/ast_data_type.h"

void tac_begin(FILE *out)
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

}

const char *tac_data_type(enum mCc_ast_data_type type)
{

	return "unknown type";
}
