#include "ast_print_statement.h"

#include <assert.h>

#include "ast_basic_printing.h"

void mCc_print_dot_statement_if(struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, statement, "statement: if");
	mCc_ast_print_dot_edge(out, statement, statement->condition_expression,
	               "condition");
	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->if_statement,
	                              "if true");
	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->else_statement,
	                              "otherwise");

	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_while(struct mCc_ast_statement *statement,
                                   void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, statement, "statement: while");
	mCc_ast_print_dot_edge(out, statement, statement->loop_condition_expression,
	               "condition");
	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->while_statement,
	                              "statement");

	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_return(struct mCc_ast_statement *statement,
                                    void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, statement, "statement: return");
	mCc_ast_print_dot_edge(out, statement, statement->return_expression, "of-type");

	// TODO: required here? Does dead-code throws an error?
	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_declaration(struct mCc_ast_statement *statement,
                                         void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, statement, "statement: declaration");
	mCc_ast_print_dot_edge(out, statement, statement->declaration, "of-type");

	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_assignment(struct mCc_ast_statement *statement,
                                        void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, statement, "statement: assignment");
	mCc_ast_print_dot_edge(out, statement, statement->assignment, "of-type");

	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}

void mCc_print_dot_statement_expression(struct mCc_ast_statement *statement,
                                        void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, statement, "statement: expression");
	mCc_ast_print_dot_edge(out, statement, statement->expression, "of-type");

	mCc_ast_print_dot_edge_if_dest_exists(out, statement, statement->next_statement,
	                              "next");
}
