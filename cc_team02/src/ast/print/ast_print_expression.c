#include "ast_print_expression.h"

#include <assert.h>

#include "ast_basic_printing.h"
#include "print_helper.h"

void mCc_print_dot_expression_literal(struct mCc_ast_expression *expression,
                                      void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	print_dot_node(out, expression, "expr: lit");
	print_dot_edge(out, expression, expression->literal,
	               print_data_type(expression->literal->type));
	print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_binary_op(struct mCc_ast_expression *expression,
                                        void *data)
{
	assert(expression);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "expr: %s",
	         mCc_ast_print_binary_op(expression->op));

	FILE *out = data;
	print_dot_node(out, expression, label);
	print_dot_edge(out, expression, expression->lhs, "lhs");
	print_dot_edge(out, expression, expression->rhs, "rhs");
	print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_parenth(struct mCc_ast_expression *expression,
                                      void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	print_dot_node(out, expression, "expr: ( )");
	print_dot_edge(out, expression, expression->expression, "of-type");
	print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_identifier(struct mCc_ast_expression *expression,
                                         void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	print_dot_node(out, expression, "expr: identifier");
	print_dot_edge(out, expression, expression->identifier, "identifier");
	print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_identifier_array(
    struct mCc_ast_expression *expression, void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	print_dot_node(out, expression, "expr: identifier_arr");
	print_dot_edge(out, expression, expression->array_identifier, "identifier");
	print_dot_edge(out, expression, expression->array_index_expression,
	               "[index]");
	print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_function_call(
    struct mCc_ast_expression *expression, void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	print_dot_node(out, expression, "expr: function_call");
	print_dot_edge(out, expression, expression->function_call, "of-type");
	print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_unary_op(struct mCc_ast_expression *expression,
                                       void *data)
{
	assert(expression);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "expr: %s",
	         mCc_ast_print_unary_op(expression->op));

	FILE *out = data;
	print_dot_node(out, expression, label);
	print_dot_edge(out, expression, expression->unary_rhs, "rhs");
	print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}
