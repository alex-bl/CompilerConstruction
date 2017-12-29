#include "mCc/ast.h"

#include <assert.h>
#include <stdlib.h>

struct mC_ast_expression* mC_ast_expression_new_literal_expression(struct mC_ast_literal* literal)
{
	assert(literal);

	struct mC_ast_expression* expr = malloc(sizeof(struct mC_ast_expression));
	if (!expr) {
		return NULL;
	}

	expr->type = MC_AST_EXPRESSION_TYPE_LITERAL;
	expr->literal = literal;
	return expr;
}

struct mC_ast_expression*
mC_ast_expression_new_parenth_expression(struct mC_ast_expression* expression)
{
	assert(expression);

	struct mC_ast_expression* expr = malloc(sizeof(struct mC_ast_expression));
	if (!expr) {
		return NULL;
	}

	expr->type = MC_AST_EXPRESSION_TYPE_PARENTH;
	expr->expression = expression;
	return expr;
}

struct mC_ast_expression* mC_ast_expression_new_binary_op_expression(enum mC_ast_binary_op op,
                                                                     struct mC_ast_expression* lhs,
                                                                     struct mC_ast_expression* rhs)
{
	assert(lhs);
	assert(rhs);

	struct mC_ast_expression* expr = malloc(sizeof(struct mC_ast_expression));
	if (!expr) {
		return NULL;
	}

	expr->type = MC_AST_EXPRESSION_TYPE_BINARY_OP;
	expr->op = op;
	expr->lhs = lhs;
	expr->rhs = rhs;
	return expr;
}

void mC_ast_expression_delete(struct mC_ast_expression *expression)
{
	assert(expression);

	switch(expression->type) {
		case MC_AST_EXPRESSION_TYPE_LITERAL:
			mC_ast_literal_delete(expression->literal);
			break;

		case MC_AST_EXPRESSION_TYPE_BINARY_OP:
			mC_ast_expression_delete(expression->lhs);
			mC_ast_expression_delete(expression->rhs);
			break;

		case MC_AST_EXPRESSION_TYPE_PARENTH:
			mC_ast_expression_delete(expression->expression);
			break;

		/* ignore invalid types */
	}

	free(expression);
}

struct mC_ast_literal* mC_ast_literal_new_int_literal(long value)
{
	struct mC_ast_literal* lit = malloc(sizeof(struct mC_ast_literal));
	if (!lit) {
		return NULL;
	}

	lit->type = MC_AST_LITERAL_TYPE_INT;
	lit->i_value = value;
	return lit;
}

struct mC_ast_literal* mC_ast_literal_new_float_literal(double value)
{
	struct mC_ast_literal* lit = malloc(sizeof(struct mC_ast_literal));
	if (!lit) {
		return NULL;
	}

	lit->type = MC_AST_LITERAL_TYPE_FLOAT;
	lit->f_value = value;
	return lit;
}

void mC_ast_literal_delete(struct mC_ast_literal *literal)
{
	assert(literal);
	free(literal);
}

/* ----------------------------------------------------------------- PRINTER */

void mC_ast_print_binary_op(FILE *out, enum mC_ast_binary_op op)
{
	switch (op) {
		case MC_AST_BINARY_OP_ADD: fprintf(out, "+"); break;
		case MC_AST_BINARY_OP_SUB: fprintf(out, "-"); break;
		case MC_AST_BINARY_OP_MUL: fprintf(out, "*"); break;
		case MC_AST_BINARY_OP_DIV: fprintf(out, "/"); break;

		/* ignore invalid types */
	}
}

/* -------------------------------------------------------- GRAPHVIZ PRINTER */

static void dot_print_node_begin(FILE *out, const void *node, const char* label_prefix)
{
	fprintf(out, "\t\"%p\" [shape=box, label=\"%s: ", node, label_prefix);
}

static void dot_print_node_end(FILE *out)
{
	fprintf(out, "\"];\n");
}

static void dot_print_edge(FILE *out, const void *src_node, const void *dst_node)
{
	fprintf(out, "\t\"%p\" -> \"%p\"\n", src_node, dst_node);
}

void mC_ast_dot_print_begin(FILE *out)
{
	fprintf(out, "digraph \"AST\" {\n");
	fprintf(out, "\tnodesep=0.6\n");
}

void mC_ast_dot_print_end(FILE *out)
{
	fprintf(out, "}\n");
}

void mC_ast_dot_print_expression(FILE *out, struct mC_ast_expression *expression)
{
	dot_print_node_begin(out, expression, "expr");

	switch (expression->type) {
		case MC_AST_EXPRESSION_TYPE_LITERAL:
			fprintf(out, "lit");
			break;

		case MC_AST_EXPRESSION_TYPE_BINARY_OP:
			mC_ast_print_binary_op(out, expression->op);
			break;

		case MC_AST_EXPRESSION_TYPE_PARENTH:
			fprintf(out, "( )");
			break;

		/* ignore invalid types */
	}

	dot_print_node_end(out);

	/* children */
	switch (expression-> type) {
		case MC_AST_EXPRESSION_TYPE_LITERAL:
			mC_ast_dot_print_literal(out, expression->literal);
			dot_print_edge(out, expression, expression->literal);
			break;

		case MC_AST_EXPRESSION_TYPE_BINARY_OP:
			mC_ast_dot_print_expression(out, expression->lhs);
			dot_print_edge(out, expression, expression->lhs);
			mC_ast_dot_print_expression(out, expression->rhs);
			dot_print_edge(out, expression, expression->rhs);
			break;

		case MC_AST_EXPRESSION_TYPE_PARENTH:
			mC_ast_dot_print_expression(out, expression->expression);
			dot_print_edge(out, expression, expression->expression);
			break;

		/* ignore invalid types */
	}
}

void mC_ast_dot_print_literal(FILE *out, struct mC_ast_literal *literal)
{
	dot_print_node_begin(out, literal, "lit");

	switch (literal->type) {
		case MC_AST_LITERAL_TYPE_INT:
			fprintf(out, "%ld", literal->i_value);
			break;

		case MC_AST_LITERAL_TYPE_FLOAT:
			fprintf(out, "%f", literal->f_value);
			break;

		/* ignore invalid types */
	}

	dot_print_node_end(out);
}
