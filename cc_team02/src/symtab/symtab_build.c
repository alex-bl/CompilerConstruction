#include "mCc/symtab_build.h"

#include <assert.h>
#include <stddef.h>

#include "mCc/ast_print_visitors.h"
#include "mCc/ast_visit.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab_handler.h"

//"global" visitor needed
static struct mCc_ast_visitor
symtab_visitor(struct mCc_symtab_and_validation_holder *symtab_info_holder)
{
	assert(symtab_info_holder);

	return (struct mCc_ast_visitor){

		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,
		.userdata = symtab_info_holder,

		//.expression
		.expression_literal = mCc_symtab_handle_expression_literal,
		.expression_binary_op = mCc_symtab_handle_expression_binary_op,
		.expression_parenth = mCc_symtab_handle_expression_parenth,

		.expression_function_call = mCc_symtab_handle_expression_function_call,
		.expression_identifier = mCc_symtab_handle_expression_identifier,
		.expression_array_identifier =
		    mCc_symtab_handle_expression_identifier_array,
		.expression_unary_op = mCc_symtab_handle_expression_unary_op,

		//.literal
		.literal_int = mCc_symtab_handle_literal_int,
		.literal_float = mCc_symtab_handle_literal_float,
		.literal_bool = mCc_symtab_handle_literal_bool,
		.literal_string = mCc_symtab_handle_literal_string,

		//.assignment
		.assignment_primitive = mCc_symtab_handle_assignment_primitive,
		.assignment_array = mCc_symtab_handle_assignment_array,

		//.declaration
		.declaration_primitive = mCc_symtab_handle_declaration_primitive,
		.declaration_array = mCc_symtab_handle_declaration_array,

		.function_call = mCc_symtab_handle_function_call,
		.function_def = mCc_symtab_handle_function_def,

		// identifier
		.identifier = mCc_symtab_handle_identifier,

		// program
		.program = mCc_symtab_handle_program,

		// statement
		.statement_if = mCc_symtab_handle_statement_if,
		.statement_while = mCc_symtab_handle_statement_while,
		.statement_return = mCc_symtab_handle_statement_return,
		.statement_declaration = mCc_symtab_handle_statement_declaration,
		.statement_assignment = mCc_symtab_handle_statement_assignment,
		.statement_expression = mCc_symtab_handle_statement_expression
	};
}

void mCc_symtab_build_program(struct mCc_ast_program *program)
{
	assert(program);

	struct mCc_symbol_table *symbol_table = mCc_symtab_new_symbol_table(NULL);
	struct mCc_symtab_and_validation_holder info_holder;

	info_holder.symbol_table=symbol_table;
	info_holder.first_semantic_error=NULL;

	// TODO: add build-ins
	struct mCc_ast_visitor visitor = symtab_visitor(&info_holder);

	mCc_ast_visit_program(program, &visitor);
}

void mCc_symtab_build_assignment(struct mCc_ast_assignment *assignment)
{
	assert(assignment);
}

void mCc_symtab_build_declaration(struct mCc_ast_declaration *declaration)
{
	assert(declaration);
}

void mCc_symtab_build_expression(struct mCc_ast_expression *expression)
{
	assert(expression);
}

void mCc_symtab_build_function_def(struct mCc_ast_function_def *function_def)
{

	assert(function_def);
}

void mCc_symtab_build_function_call(struct mCc_ast_function_call *function_call)
{
	assert(function_call);
}

void mCc_symtab_build_identifier(struct mCc_ast_identifier *identifier)
{

	assert(identifier);
}

void mCc_symtab_build_literal(struct mCc_ast_literal *literal)
{

	assert(literal);
}

void mCc_symtab_build_statement(struct mCc_ast_statement *statement)
{

	assert(statement);
}
