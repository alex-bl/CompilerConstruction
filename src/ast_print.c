#include "mCc/ast_print.h"

#include "mCc/ast_visit.h"

const char *mC_ast_print_binary_op(enum mC_ast_binary_op op)
{
	switch (op) {
		case MC_AST_BINARY_OP_ADD: return "+";
		case MC_AST_BINARY_OP_SUB: return "-";
		case MC_AST_BINARY_OP_MUL: return "*";
		case MC_AST_BINARY_OP_DIV: return "/";
	}

	return "unknown binary op";
}

/* ------------------------------------------------------------- DOT Printer */

void mC_ast_print_dot_begin(FILE *out)
{
	fprintf(out, "digraph \"AST\" {\n");
	fprintf(out, "\tnodesep=0.6\n");
}

void mC_ast_print_dot_end(FILE *out)
{
	fprintf(out, "}\n");
}

static void print_dot_node_begin(FILE *out, const void *node)
{
	fprintf(out, "\t\"%p\" [shape=box, label=\"", node);
}

static void print_dot_node_end(FILE *out)
{
	fprintf(out, "\"];\n");
}

static void print_dot_edge(FILE *out, const void *src_node,
                           const void *dst_node, const char *label)
{
	fprintf(out, "\t\"%p\" -> \"%p\" [label=\"%s\"]\n", src_node, dst_node,
	        label);
}

static void print_dot_expression_literal(struct mC_ast_expression *expression,
                                         void *data)
{
	FILE *out = data;
	print_dot_node_begin(out, expression);
	fprintf(out, "expr: lit");
	print_dot_node_end(out);

	print_dot_edge(out, expression, expression->literal, "literal");
}

static void print_dot_expression_binary_op(struct mC_ast_expression *expression,
                                           void *data)
{
	FILE *out = data;
	print_dot_node_begin(out, expression);
	fprintf(out, "expr: %s", mC_ast_print_binary_op(expression->op));
	print_dot_node_end(out);

	print_dot_edge(out, expression, expression->lhs, "lhs");
	print_dot_edge(out, expression, expression->rhs, "rhs");
}

static void print_dot_expression_parenth(struct mC_ast_expression *expression,
                                         void *data)
{
	FILE *out = data;
	print_dot_node_begin(out, expression);
	fprintf(out, "( )");
	print_dot_node_end(out);

	print_dot_edge(out, expression, expression->expression, "expression");
}

static void print_dot_literal_int(struct mC_ast_literal *literal, void *data)
{
	FILE *out = data;
	print_dot_node_begin(out, literal);
	fprintf(out, "%ld", literal->i_value);
	print_dot_node_end(out);
}

static void print_dot_literal_float(struct mC_ast_literal *literal, void *data)
{
	FILE *out = data;
	print_dot_node_begin(out, literal);
	fprintf(out, "%f", literal->f_value);
	print_dot_node_end(out);
}

void mC_ast_print_dot_expression(FILE *out,
                                 struct mC_ast_expression *expression)
{
	struct mC_ast_visitor visitor = {
	    .data = out,

	    .expression_literal = print_dot_expression_literal,
	    .expression_binary_op = print_dot_expression_binary_op,
	    .expression_parenth = print_dot_expression_parenth,

	    .literal_int = print_dot_literal_int,
	    .literal_float = print_dot_literal_float,
	};

	mC_ast_visit_expression_df(MC_AST_VISIT_PRE_ORDER, expression, &visitor);
}
