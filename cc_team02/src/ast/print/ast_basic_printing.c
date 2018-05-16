#include "ast_basic_printing.h"

#include <assert.h>
#include <stdio.h>

#include "ast_data_type.h"

void mCc_ast_print_dot_begin(FILE *out)
{
	assert(out);

	fprintf(out, "digraph \"AST\" {\n");
	fprintf(out, "\tnodesep=0.6\n");
}

void mCc_ast_print_dot_end(FILE *out)
{
	assert(out);

	fprintf(out, "}\n");
}

void mCc_ast_print_dot_node(FILE *out, const void *node, const char *label)
{
	assert(out);
	assert(node);
	assert(label);

	fprintf(out, "\t\"%p\" [shape=box, label=\"%s\"];\n", node, label);
}

void mCc_ast_print_dot_edge(FILE *out, const void *src_node,
                            const void *dst_node, const char *label)
{
	assert(out);
	assert(src_node);
	assert(dst_node);
	assert(label);

	fprintf(out, "\t\"%p\" -> \"%p\" [label=\"%s\"];\n", src_node, dst_node,
	        label);
}

void mCc_ast_print_dot_edge_if_dest_exists(FILE *out, const void *src_node,
                                           const void *dst_node,
                                           const char *label)
{
	if (dst_node) {
		mCc_ast_print_dot_edge(out, src_node, dst_node, label);
	}
}
