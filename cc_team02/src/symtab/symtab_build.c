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

		//===============================
		// needed for symtab-construction:
		.function_def_enter_scope = mCc_symtab_function_def_enter_scope,
		.function_def_leave_scope = mCc_symtab_function_def_leave_scope,
		.statement_if_enter_scope = mCc_symtab_statement_if_enter_scope,
		.statement_if_leave_scope = mCc_symtab_statement_if_leave_scope,
		.statement_while_enter_scope = mCc_symtab_statement_while_leave_scope,
		.statement_while_leave_scope = mCc_symtab_statement_while_leave_scope,
		//.declaration => add declarations to current symtab
		.declaration_primitive = mCc_symtab_handle_declaration_primitive,
		.declaration_array = mCc_symtab_handle_declaration_array,
		// identifier => get from symtab an link information
		.identifier = mCc_symtab_handle_identifier,
		//=================================

		// maybe not needed inside symtab-construction
		//.expression
		.expression_literal = NULL,
		.expression_binary_op = NULL,
		.expression_parenth = NULL,
		.expression_function_call = NULL,
		.expression_identifier = NULL,
		.expression_array_identifier = NULL,
		.expression_unary_op = NULL,
		//.literal
		.literal_int = NULL,
		.literal_float = NULL,
		.literal_bool = NULL,
		.literal_string = NULL,
		//.assignment
		.assignment_primitive = NULL,
		.assignment_array = NULL,
		//.function
		.function_call = NULL,
		.function_def = NULL,
		// program
		.program = NULL,
		// statement
		.statement_if = NULL,
		.statement_while = NULL,
		.statement_return = NULL,
		.statement_declaration = NULL,
		.statement_assignment = NULL,
		.statement_expression = NULL,
	};
}

void mCc_symtab_build_program(struct mCc_ast_program *program)
{
	assert(program);

	struct mCc_symbol_table *symbol_table = mCc_symtab_new_symbol_table(NULL);
	struct mCc_symtab_and_validation_holder info_holder;

	info_holder.symbol_table = symbol_table;
	info_holder.first_semantic_error = NULL;

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
