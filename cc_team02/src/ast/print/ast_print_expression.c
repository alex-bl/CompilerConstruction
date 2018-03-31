#include "mCc/ast/print/ast_print_expression.h"

#include <assert.h>

#include "mCc/ast/print/ast_basic_printing.h"

const char *mCc_ast_print_binary_op(enum mCc_ast_binary_op op)
{
	switch (op) {
	case MCC_AST_BINARY_OP_ADD: return "+";
	case MCC_AST_BINARY_OP_SUB: return "-";
	case MCC_AST_BINARY_OP_MUL: return "*";
	case MCC_AST_BINARY_OP_DIV: return "/";
	case MCC_AST_BINARY_OP_LESS_THAN: return "<";
	case MCC_AST_BINARY_OP_GREATER_THAN: return ">";
	case MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN: return "<=";
	case MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN: return ">=";
	case MCC_AST_BINARY_OP_AND: return "&&";
	case MCC_AST_BINARY_OP_OR: return "||";
	case MCC_AST_BINARY_OP_EQUALS: return "==";
	case MCC_AST_BINARY_OP_NOT_EQUALS: return "!=";
	}
	return "unknown op";
}

const char *mCc_ast_print_unary_op(enum mCc_ast_unary_op op)
{
	switch (op) {
	case MCC_AST_UNARY_OP_MINUS: return "-";
	case MCC_AST_UNARY_OP_NEGATION: return "!";
	}
	return "unknown op";
}

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
