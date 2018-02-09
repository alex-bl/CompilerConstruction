#include "mCc/ast_print.h"

#include <assert.h>

#include "mCc/ast_visit.h"

void mCc_ast_print_binary_op(FILE *out, enum mCc_ast_binary_op op)
{
	assert(out);

	switch (op) {
	case MCC_AST_BINARY_OP_ADD: fprintf(out, "+"); return;
	case MCC_AST_BINARY_OP_SUB: fprintf(out, "-"); return;
	case MCC_AST_BINARY_OP_MUL: fprintf(out, "*"); return;
	case MCC_AST_BINARY_OP_DIV: fprintf(out, "/"); return;
	}

	fprintf(out, "unknown binary op");
}

/* ------------------------------------------------------------- DOT Printer */

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

static void print_dot_node_begin(FILE *out, const void *node)
{
	assert(out);
	assert(node);

	fprintf(out, "\t\"%p\" [shape=box, label=\"", node);
}

static void print_dot_node_end(FILE *out)
{
	assert(out);

	fprintf(out, "\"];\n");
}

static void print_dot_edge(FILE *out, const void *src_node,
                           const void *dst_node, const char *label)
{
	assert(out);
	assert(src_node);
	assert(dst_node);
	assert(label);

	fprintf(out, "\t\"%p\" -> \"%p\" [label=\"%s\"]\n", src_node, dst_node,
	        label);
}

static void print_dot_expression_literal(struct mCc_ast_expression *expression,
                                         void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	print_dot_node_begin(out, expression);
	fprintf(out, "expr: lit");
	print_dot_node_end(out);

	print_dot_edge(out, expression, expression->literal, "literal");
}

static void
print_dot_expression_binary_op(struct mCc_ast_expression *expression,
                               void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	print_dot_node_begin(out, expression);
	fprintf(out, "expr: ");
	mCc_ast_print_binary_op(out, expression->op);
	print_dot_node_end(out);

	print_dot_edge(out, expression, expression->lhs, "lhs");
	print_dot_edge(out, expression, expression->rhs, "rhs");
}

static void print_dot_expression_parenth(struct mCc_ast_expression *expression,
                                         void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	print_dot_node_begin(out, expression);
	fprintf(out, "( )");
	print_dot_node_end(out);

	print_dot_edge(out, expression, expression->expression, "expression");
}

static void print_dot_literal_int(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	FILE *out = data;
	print_dot_node_begin(out, literal);
	fprintf(out, "%ld", literal->i_value);
	print_dot_node_end(out);
}

static void print_dot_literal_float(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	FILE *out = data;
	print_dot_node_begin(out, literal);
	fprintf(out, "%f", literal->f_value);
	print_dot_node_end(out);
}

void mCc_ast_print_dot_expression(FILE *out,
                                  struct mCc_ast_expression *expression)
{
	assert(out);
	assert(expression);

	struct mCc_ast_visitor visitor = {
		.userdata = out,

		.expression_literal = print_dot_expression_literal,
		.expression_binary_op = print_dot_expression_binary_op,
		.expression_parenth = print_dot_expression_parenth,

		.literal_int = print_dot_literal_int,
		.literal_float = print_dot_literal_float,
	};

	mCc_ast_visit_expression_df(MCC_AST_VISIT_PRE_ORDER, expression, &visitor);
}
