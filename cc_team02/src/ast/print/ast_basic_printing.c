#include "mCc/ast/print/ast_basic_printing.h"

#include <assert.h>
#include <stdio.h>

#include "mCc/ast/basis/ast_data_type.h"

void print_dot_begin(FILE *out)
{
	assert(out);

	fprintf(out, "digraph \"AST\" {\n");
	fprintf(out, "\tnodesep=0.6\n");
}

void print_dot_end(FILE *out)
{
	assert(out);

	fprintf(out, "}\n");
}

void print_dot_node(FILE *out, const void *node, const char *label)
{
	assert(out);
	assert(node);
	assert(label);

	fprintf(out, "\t\"%p\" [shape=box, label=\"%s\"];\n", node, label);
}

void print_dot_edge(FILE *out, const void *src_node, const void *dst_node,
                    const char *label)
{
	assert(out);
	assert(src_node);
	assert(dst_node);
	assert(label);

	fprintf(out, "\t\"%p\" -> \"%p\" [label=\"%s\"];\n", src_node, dst_node,
	        label);
}

void print_dot_edge_if_dest_exists(FILE *out, const void *src_node,
                                   const void *dst_node, const char *label)
{
	if (dst_node) {
		print_dot_edge(out, src_node, dst_node, label);
	}
}

const char *print_data_type(enum mCc_ast_data_type type)
{
	switch (type) {
	case MCC_AST_DATA_TYPE_VOID: return "void";
	case MCC_AST_DATA_TYPE_INT: return "int";
	case MCC_AST_DATA_TYPE_FLOAT: return "float";
	case MCC_AST_DATA_TYPE_BOOL: return "bool";
	case MCC_AST_DATA_TYPE_STRING: return "string";
	case MCC_AST_DATA_TYPE_INCONSISTENT: return "inconsistent";
	}
	return "unknown type";
}
