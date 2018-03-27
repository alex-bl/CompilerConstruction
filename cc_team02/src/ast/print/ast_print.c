#include "mCc/ast_print.h"
#include "mCc/ast_visit.h"
#include "mCc/ast_print_visitors.h"

#include <assert.h>

//"global" visitor needed
static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,
		.userdata = out,

		//.expression
		.expression_literal = mCc_print_dot_expression_literal,
		.expression_binary_op = mCc_print_dot_expression_binary_op,
		.expression_parenth = mCc_print_dot_expression_parenth,

		.expression_function_call = mCc_print_dot_expression_function_call,
		.expression_identifier = mCc_print_dot_expression_identifier,
		.expression_array_identifier =
		    mCc_print_dot_expression_identifier_array,
		.expression_unary_op = mCc_print_dot_expression_unary_op,

		//.literal
		.literal_int = mCc_print_dot_literal_int,
		.literal_float = mCc_print_dot_literal_float,
		.literal_bool = mCc_print_dot_literal_bool,
		.literal_string = mCc_print_dot_literal_string,

		//.assignment
		.assignment_primitive = mCc_print_dot_assignment_primitive,
		.assignment_array = mCc_print_dot_assignment_array,

		//.declaration
		.declaration_primitive = mCc_print_dot_declaration_primitive,
		.declaration_array = mCc_print_dot_declaration_array,

		.function_call = mCc_print_dot_function_call,
		.function_def = mCc_print_dot_function_def,

		// identifier
		.identifier = mCc_print_dot_identifier,

		// program
		.program = mCc_print_dot_program,

		// statement
		.statement_if = mCc_print_dot_statement_if,
		.statement_while = mCc_print_dot_statement_while,
		.statement_return = mCc_print_dot_statement_return,
		.statement_declaration = mCc_print_dot_statement_declaration,
		.statement_assignment = mCc_print_dot_statement_assignment,
		.statement_expression = mCc_print_dot_statement_expression

	};
}

void mCc_ast_print_dot_assignment(FILE *out,
                                  struct mCc_ast_assignment *assignment)
{
	assert(out);
	assert(assignment);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_assignment(assignment, &visitor);

	print_dot_end(out);
}

void mCc_ast_print_dot_declaration(FILE *out,
                                   struct mCc_ast_declaration *declaration)
{
	assert(out);
	assert(declaration);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_declaration(declaration, &visitor);

	print_dot_end(out);
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

void mCc_ast_print_dot_program(FILE *out, struct mCc_ast_program *program)
{
	assert(out);
	assert(program);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_program(program, &visitor);

	print_dot_end(out);
}

void mCc_ast_print_dot_literal(FILE *out, struct mCc_ast_literal *literal)
{
	assert(out);
	assert(literal);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_literal(literal, &visitor);

	print_dot_end(out);
}

void mCc_ast_print_dot_identifier(FILE *out,
                                  struct mCc_ast_identifier *identifier)
{
	assert(out);
	assert(identifier);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_identifier(identifier, &visitor);

	print_dot_end(out);
}

void mCc_ast_print_dot_function_def(FILE *out,
                                    struct mCc_ast_function_def *function_def)
{
	assert(out);
	assert(function_def);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_function_def(function_def, &visitor);

	print_dot_end(out);
}

void mCc_ast_print_dot_function_call(
    FILE *out, struct mCc_ast_function_call *function_call)
{
	assert(out);
	assert(function_call);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_function_call(function_call, &visitor);

	print_dot_end(out);
}

void mCc_ast_print_dot_expression(FILE *out,
                                  struct mCc_ast_expression *expression)
{
	assert(out);
	assert(expression);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_expression(expression, &visitor);

	print_dot_end(out);
}
