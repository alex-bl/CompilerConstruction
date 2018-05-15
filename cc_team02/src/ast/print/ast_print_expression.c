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
	mCc_ast_print_dot_node(out, expression, "expr: lit");
	mCc_ast_print_dot_edge(out, expression, expression->literal,
	               mCc_ast_print_data_type(expression->literal->type));
	mCc_ast_print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
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
	mCc_ast_print_dot_node(out, expression, label);
	mCc_ast_print_dot_edge(out, expression, expression->lhs, "lhs");
	mCc_ast_print_dot_edge(out, expression, expression->rhs, "rhs");
	mCc_ast_print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_parenth(struct mCc_ast_expression *expression,
                                      void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, expression, "expr: ( )");
	mCc_ast_print_dot_edge(out, expression, expression->expression, "of-type");
	mCc_ast_print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_identifier(struct mCc_ast_expression *expression,
                                         void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, expression, "expr: identifier");
	mCc_ast_print_dot_edge(out, expression, expression->identifier, "identifier");
	mCc_ast_print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_identifier_array(
    struct mCc_ast_expression *expression, void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, expression, "expr: identifier_arr");
	mCc_ast_print_dot_edge(out, expression, expression->array_identifier, "identifier");
	mCc_ast_print_dot_edge(out, expression, expression->array_index_expression,
	               "[index]");
	mCc_ast_print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}

void mCc_print_dot_expression_function_call(
    struct mCc_ast_expression *expression, void *data)
{
	assert(expression);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, expression, "expr: function_call");
	mCc_ast_print_dot_edge(out, expression, expression->function_call, "of-type");
	mCc_ast_print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
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
	mCc_ast_print_dot_node(out, expression, label);
	mCc_ast_print_dot_edge(out, expression, expression->unary_rhs, "rhs");
	mCc_ast_print_dot_edge_if_dest_exists(out, expression, expression->next_expr,
	                              "next");
}
