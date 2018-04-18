#include "mCc/ast_tac.h"

#include <assert.h>
#include <stddef.h>

#include "mCc/ast_tac_visitors.h"
#include "mCc/ast_visit.h"

//"global" visitor needed
static struct mCc_ast_visitor tac_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,
		.userdata = out,

		//.expression
		.expression_literal = mCc_tac_expression_literal,
		.expression_binary_op = mCc_tac_expression_binary_op,
		.expression_parenth = mCc_tac_expression_parenth,

		.expression_function_call = mCc_tac_expression_function_call,
		.expression_identifier = mCc_tac_expression_identifier,
		.expression_array_identifier =
		    mCc_tac_expression_identifier_array,
		.expression_unary_op = mCc_tac_expression_unary_op,

		//.literal
		.literal_int = mCc_tac_literal_int,
		.literal_float = mCc_tac_literal_float,
		.literal_bool = mCc_tac_literal_bool,
		.literal_string = mCc_tac_literal_string,

		//.assignment
		.assignment_primitive = mCc_tac_assignment_primitive,
		.assignment_array = mCc_tac_assignment_array,

		//.declaration
		.declaration_primitive = mCc_tac_declaration_primitive,
		.declaration_array = mCc_tac_declaration_array,

		.function_call = mCc_tac_function_call,
		.function_def = mCc_tac_function_def,

		// identifier
		.identifier = mCc_tac_identifier,

		// program
		.program = mCc_tac_program,

		// statement
		.statement_if = mCc_tac_statement_if,
		.statement_while = mCc_tac_statement_while,
		.statement_return = mCc_tac_statement_return,
		.statement_declaration = mCc_tac_statement_declaration,
		.statement_assignment = mCc_tac_statement_assignment,
		.statement_expression = mCc_tac_statement_expression,

		//not needed for print
		.statement=NULL,
		.assignment=NULL,
		.declaration=NULL,
		.literal=NULL,
		.expression=NULL,

		// scope enter/leave hooks also not needed here
		.function_def_enter_scope=NULL,
		.function_def_leave_scope=NULL,

		.statement_if_enter_scope=NULL,
		.statement_if_leave_scope=NULL,
		.statement_while_enter_scope=NULL,
		.statement_while_leave_scope=NULL
	};
}

void mCc_ast_tac_assignment(FILE *out,
                                  struct mCc_ast_assignment *assignment)
{
	assert(out);
	assert(assignment);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_assignment(assignment, &visitor);

	tac_end(out);
}

void mCc_ast_tac_declaration(FILE *out,
                                   struct mCc_ast_declaration *declaration)
{
	assert(out);
	assert(declaration);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_declaration(declaration, &visitor);

	tac_end(out);
}

void mCc_ast_tac_statement(FILE *out, struct mCc_ast_statement *statement)
{
	assert(out);
	assert(statement);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_statement(statement, &visitor);

	tac_end(out);
}

/*
 * should be the "top"
 * is "global"
 */
void mCc_ast_tac_program(FILE *out, struct mCc_ast_program *program)
{
	assert(out);
	assert(program);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_program(program, &visitor);

	tac_end(out);
}

void mCc_ast_tac_literal(FILE *out, struct mCc_ast_literal *literal)
{
	assert(out);
	assert(literal);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_literal(literal, &visitor);

	tac_end(out);
}

void mCc_ast_tac_identifier(FILE *out,
                                  struct mCc_ast_identifier *identifier)
{
	assert(out);
	assert(identifier);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_identifier(identifier, &visitor);

	tac_end(out);
}

void mCc_ast_tac_function_def(FILE *out,
                                    struct mCc_ast_function_def *function_def)
{
	assert(out);
	assert(function_def);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_function_def(function_def, &visitor);

	tac_end(out);
}

void mCc_ast_tac_function_call(
    FILE *out, struct mCc_ast_function_call *function_call)
{
	assert(out);
	assert(function_call);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_function_call(function_call, &visitor);

	tac_end(out);
}

void mCc_ast_tac_expression(FILE *out,
                                  struct mCc_ast_expression *expression)
{
	assert(out);
	assert(expression);

	tac_begin(out);

	struct mCc_ast_visitor visitor = tac_visitor(out);
	mCc_ast_visit_expression(expression, &visitor);

	tac_end(out);
}
