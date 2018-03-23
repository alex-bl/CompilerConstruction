#include <assert.h>
#include <stdlib.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_statement.h"
#include "mCc/ast/visit/ast_visit_statement.h"

static void print_dot_statement_if(struct mCc_ast_statement *statement,
                                   void *data)
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

static void print_dot_statement_while(struct mCc_ast_statement *statement,
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

static void print_dot_statement_return(struct mCc_ast_statement *statement,
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

static void print_dot_statement_declaration(struct mCc_ast_statement *statement,
                                            void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: declaration");
	print_dot_edge(out, statement, statement->declaration, "declaration");
}

static void print_dot_statement_assignment(struct mCc_ast_statement *statement,
                                           void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: assignment");
	print_dot_edge(out, statement, statement->assignment, "assignment stmt");
}

static void print_dot_statement_expression(struct mCc_ast_statement *statement,
                                           void *data)
{
	assert(statement);
	assert(data);

	FILE *out = data;
	print_dot_node(out, statement, "statement: expression");
	print_dot_edge(out, statement, statement->expression, "expression stmt");
}

static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){
		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,

		.userdata = out,
		.statement_if = print_dot_statement_if,
		.statement_while = print_dot_statement_while,
		.statement_return = print_dot_statement_return,
		.statement_declaration = print_dot_statement_declaration,
		.statement_assignment = print_dot_statement_assignment,
		.statement_expression = print_dot_statement_expression,
	};
}

void mCc_ast_print_dot_statement(FILE *out, struct mCc_ast_statement *statement)
{
	assert(out);
	assert(statement);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_statement(statement, &visitor);

	print_dot_end(out);
}
