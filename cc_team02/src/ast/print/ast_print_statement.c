#include <assert.h>
#include <stdlib.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_statement.h"
#include "mCc/ast/visit/ast_visit_statement.h"

void mCc_print_dot_statement_if(struct mCc_ast_statement *statement, void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: if");
	print_dot_edge(out, statement, statement->condition_expression,
	               "condition");
	print_dot_edge(out, statement, statement->if_statement, "if true");
	print_dot_edge(out, statement, statement->else_statement, "else");
}

void mCc_print_dot_statement_while(struct mCc_ast_statement *statement,
                                   void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: while");
	print_dot_edge(out, statement, statement->loop_condition_expression,
	               "loop cond.");
	print_dot_edge(out, statement, statement->while_statement, "while stmt");
}

void mCc_print_dot_statement_return(struct mCc_ast_statement *statement,
                                    void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: while");
	print_dot_edge(out, statement, statement->loop_condition_expression,
	               "loop cond.");
	print_dot_edge(out, statement, statement->while_statement, "while stmt");
}

void mCc_print_dot_statement_declaration(struct mCc_ast_statement *statement,
                                         void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: declaration");
	print_dot_edge(out, statement, statement->declaration, "declaration");
}

void mCc_print_dot_statement_assignment(struct mCc_ast_statement *statement,
                                        void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: assignment");
	print_dot_edge(out, statement, statement->assignment, "assignment stmt");
}

void mCc_print_dot_statement_expression(struct mCc_ast_statement *statement,
                                        void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: expression");
	print_dot_edge(out, statement, statement->expression, "expression stmt");
}
