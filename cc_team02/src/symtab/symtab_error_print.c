#include "symtab_error_print.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "ast_visit_program.h"
#include "error_printer.h"
#include "mCc/ast_visit.h"

//"global" visitor needed
static struct mCc_ast_visitor error_print_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,
		.userdata = out,

		//.expression
		.expression_literal = mCc_print_error_expression_literal,
		.expression_binary_op = mCc_print_error_expression_binary_op,
		.expression_parenth = mCc_print_error_expression_parenth,

		.expression_function_call = mCc_print_error_expression_function_call,
		.expression_identifier = mCc_print_error_expression_identifier,
		.expression_array_identifier =
		    mCc_print_error_expression_identifier_array,
		.expression_unary_op = mCc_print_error_expression_unary_op,

		//.literal
		.literal_int = NULL,
		.literal_float = NULL,
		.literal_bool = NULL,
		.literal_string = NULL,

		//.assignment
		.assignment_primitive = mCc_print_error_assignment_primitive,
		.assignment_array = mCc_print_error_assignment_array,

		//.declaration
		.declaration_primitive = mCc_print_error_declaration_primitive,
		.declaration_array = mCc_print_error_declaration_array,

		.function_call = mCc_print_error_function_call,
		.function_def = mCc_print_error_function_def,

		// identifier
		.identifier = mCc_print_error_identifier,

		// program
		.program = mCc_print_error_program,

		// statement
		.statement_if = mCc_print_error_statement_if,
		.statement_while = mCc_print_error_statement_while,
		.statement_return = mCc_print_error_statement_return,
		.statement_declaration = mCc_print_error_statement_declaration,
		.statement_assignment = mCc_print_error_statement_assignment,
		.statement_expression = mCc_print_error_statement_expression,

		// not needed for print
		.statement = NULL,
		.assignment = NULL,
		.declaration = NULL,
		.literal = NULL,
		.expression = NULL,

		// scope enter/leave hooks also not needed here
		.function_def_enter_scope = NULL,
		.function_def_leave_scope = NULL,

		.statement_if_enter_scope = NULL,
		.statement_if_leave_scope = NULL,
		.statement_while_enter_scope = NULL,
		.statement_while_leave_scope = NULL
	};
}

// TODO: return status
void mCc_symtab_print_semantic_errors(struct mCc_ast_program *program,
                                      FILE *out)
{
	assert(program);
	assert(out);

	struct mCc_ast_visitor visitor = error_print_visitor(out);
	mCc_ast_visit_program(program, &visitor);
}
