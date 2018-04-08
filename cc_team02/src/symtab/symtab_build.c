#include "mCc/symtab_build.h"

#include <assert.h>

#include "mCc/ast_visit.h"
#include "mCc/symtab/symbol_table.h"

//"global" visitor needed
static struct mCc_ast_visitor
symtab_visitor(struct mCc_symbol_table *symbol_table, int *start_scope_level)
{
	assert(symbol_table);
	assert(start_scope_level);

	return (struct mCc_ast_visitor){

		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,
		.userdata = symbol_table,
		.scope_level = start_scope_level,

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

void mCc_symtab_build_program(struct mCc_symbol_table *symbol_table,
                              int *start_scope_level,
                              struct mCc_ast_program *program)
{
	assert(symbol_table);
	assert(start_scope_level);
	assert(program);

	struct mCc_ast_visitor visitor =
	    symtab_visitor(symbol_table, start_scope_level);

	// make sure that the callbacks can access to the visitor's
	// "scope-level-counter"
	symbol_table->scope_level_visitor = start_scope_level;

	mCc_ast_visit_program(program, &visitor);
}

void mCc_symtab_build_assignment(struct mCc_symbol_table *symbol_table,
                                 int *start_scope_level,
                                 struct mCc_ast_assignment *assignment)
{
	assert(symbol_table);
	assert(start_scope_level);
	assert(assignment);

	struct mCc_ast_visitor visitor =
	    symtab_visitor(symbol_table, start_scope_level);

	// make sure that the callbacks can access to the visitor's
	// "scope-level-counter"
	symbol_table->scope_level_visitor = start_scope_level;

	mCc_ast_visit_assignment(assignment, &visitor);
}

void mCc_symtab_build_declaration(struct mCc_symbol_table *symbol_table,
                                  int *start_scope_level,
                                  struct mCc_ast_declaration *declaration)
{
	assert(symbol_table);
	assert(start_scope_level);
	assert(declaration);

	struct mCc_ast_visitor visitor =
	    symtab_visitor(symbol_table, start_scope_level);

	// make sure that the callbacks can access to the visitor's
	// "scope-level-counter"
	symbol_table->scope_level_visitor = start_scope_level;

	mCc_ast_visit_declaration(declaration, &visitor);
}

void mCc_symtab_build_expression(struct mCc_symbol_table *symbol_table,
                                 int *start_scope_level,
                                 struct mCc_ast_expression *expression)
{
	assert(symbol_table);
	assert(start_scope_level);
	assert(expression);

	struct mCc_ast_visitor visitor =
	    symtab_visitor(symbol_table, start_scope_level);

	// make sure that the callbacks can access to the visitor's
	// "scope-level-counter"
	symbol_table->scope_level_visitor = start_scope_level;

	mCc_ast_visit_expression(expression, &visitor);
}

void mCc_symtab_build_function(struct mCc_symbol_table *symbol_table,
                               int *start_scope_level,
                               struct mCc_ast_function *function)
{
	assert(symbol_table);
	assert(start_scope_level);
	assert(function);

	struct mCc_ast_visitor visitor =
	    symtab_visitor(symbol_table, start_scope_level);

	// make sure that the callbacks can access to the visitor's
	// "scope-level-counter"
	symbol_table->scope_level_visitor = start_scope_level;

	mCc_ast_visit_function(function, &visitor);
}

void mCc_symtab_build_identifier(struct mCc_symbol_table *symbol_table,
                                 int *start_scope_level,
                                 struct mCc_ast_identifier *identifier)
{
	assert(symbol_table);
	assert(start_scope_level);
	assert(identifier);

	struct mCc_ast_visitor visitor =
	    symtab_visitor(symbol_table, start_scope_level);

	// make sure that the callbacks can access to the visitor's
	// "scope-level-counter"
	symbol_table->scope_level_visitor = start_scope_level;

	mCc_ast_visit_identifier(identifier, &visitor);
}

void mCc_symtab_build_literal(struct mCc_symbol_table *symbol_table,
                              int *start_scope_level,
                              struct mCc_ast_literal *literal)
{
	assert(symbol_table);
	assert(start_scope_level);
	assert(literal);

	struct mCc_ast_visitor visitor =
	    symtab_visitor(symbol_table, start_scope_level);

	// make sure that the callbacks can access to the visitor's
	// "scope-level-counter"
	symbol_table->scope_level_visitor = start_scope_level;

	mCc_ast_visit_literal(literal, &visitor);
}

void mCc_symtab_build_statement(struct mCc_symbol_table *symbol_table,
                                int *start_scope_level,
                                struct mCc_ast_statement *statement)
{
	assert(symbol_table);
	assert(start_scope_level);
	assert(statement);

	struct mCc_ast_visitor visitor =
	    symtab_visitor(symbol_table, start_scope_level);

	// make sure that the callbacks can access to the visitor's
	// "scope-level-counter"
	symbol_table->scope_level_visitor = start_scope_level;

	mCc_ast_visit_statement(statement, &visitor);
}
