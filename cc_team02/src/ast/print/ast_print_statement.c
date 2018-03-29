#include "mCc/ast/print/ast_print_statement.h"
#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/visit/ast_visit_statement.h"
#include <assert.h>
#include <stdlib.h>

void mCc_print_dot_statement_if(struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: if");
	print_dot_edge(out, statement, statement->condition_expression,
	               "condition");
	print_dot_edge_if_dest_exists(out, statement, statement->if_statement,
	                              "if true");
	print_dot_edge_if_dest_exists(out, statement, statement->else_statement,
	                              "otherwise");

	print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_while(struct mCc_ast_statement *statement,
                                   void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: while");
	print_dot_edge(out, statement, statement->loop_condition_expression,
	               "condition");
	print_dot_edge_if_dest_exists(out, statement, statement->while_statement,
	                              "statement");

	print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_return(struct mCc_ast_statement *statement,
                                    void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: return");
	print_dot_edge(out, statement, statement->return_expression, "of-type");

	// TODO: required here? Does dead-code throws an error?
	print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_declaration(struct mCc_ast_statement *statement,
                                         void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: declaration");
	print_dot_edge(out, statement, statement->declaration, "of-type");

	print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_assignment(struct mCc_ast_statement *statement,
                                        void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: assignment");
	print_dot_edge(out, statement, statement->assignment, "of-type");

	print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_expression(struct mCc_ast_statement *statement,
                                        void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: expression");
	print_dot_edge(out, statement, statement->expression, "of-type");

	print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}
