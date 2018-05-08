#include "mCc/symtab/print/error_printer.h"

#include <stdio.h>
#include <string.h>

#include "config.h"
#include "mCc/symtab/validator/validator.h"

static void print_error_if_exists(FILE *out, struct mCc_ast_node location,
                                  struct mCc_validation_status_result *error)
{
	if (error) {
		fprintf(out, "Line %d col %d:\t%s\n", location.sloc.start_line,
		        location.sloc.start_col, error->error_msg);
	}
}

void mCc_print_error_statement_if(struct mCc_ast_statement *statement,
                                  void *data)
{
	print_error_if_exists(data, statement->node, statement->semantic_error);
};

void mCc_print_error_statement_while(struct mCc_ast_statement *statement,
                                     void *data)
{
	print_error_if_exists(data, statement->node, statement->semantic_error);
};
void mCc_print_error_statement_return(struct mCc_ast_statement *statement,
                                      void *data)
{
	print_error_if_exists(data, statement->node, statement->semantic_error);
};
void mCc_print_error_statement_declaration(struct mCc_ast_statement *statement,
                                           void *data)
{
	print_error_if_exists(data, statement->node, statement->semantic_error);
};
void mCc_print_error_statement_assignment(struct mCc_ast_statement *statement,
                                          void *data)
{
	print_error_if_exists(data, statement->node, statement->semantic_error);
};
void mCc_print_error_statement_expression(struct mCc_ast_statement *statement,
                                          void *data)
{
	print_error_if_exists(data, statement->node, statement->semantic_error);
};

void mCc_print_error_program(struct mCc_ast_program *program, void *data)
{
	print_error_if_exists(data, program->node, program->semantic_error);
};

void mCc_print_error_identifier(struct mCc_ast_identifier *identifier,
                                void *data)
{
	print_error_if_exists(data, identifier->node, identifier->semantic_error);
};

void mCc_print_error_function_def(struct mCc_ast_function_def *def, void *data)
{
	print_error_if_exists(data, def->node, def->semantic_error);
};

void mCc_print_error_function_call(struct mCc_ast_function_call *call,
                                   void *data)
{
	print_error_if_exists(data, call->node, call->semantic_error);
};

void mCc_print_error_expression_literal(struct mCc_ast_expression *expression,
                                        void *data)
{
	print_error_if_exists(data, expression->node, expression->semantic_error);
};

void mCc_print_error_expression_binary_op(struct mCc_ast_expression *expression,
                                          void *data)
{
	print_error_if_exists(data, expression->node, expression->semantic_error);
};

void mCc_print_error_expression_parenth(struct mCc_ast_expression *expression,
                                        void *data)
{
	print_error_if_exists(data, expression->node, expression->semantic_error);
};

void mCc_print_error_expression_identifier(
    struct mCc_ast_expression *expression, void *data)
{
	print_error_if_exists(data, expression->node, expression->semantic_error);
};

void mCc_print_error_expression_identifier_array(
    struct mCc_ast_expression *expression, void *data)
{
	print_error_if_exists(data, expression->node, expression->semantic_error);
};

void mCc_print_error_expression_function_call(
    struct mCc_ast_expression *expression, void *data)
{
	print_error_if_exists(data, expression->node, expression->semantic_error);
};

void mCc_print_error_expression_unary_op(struct mCc_ast_expression *expression,
                                         void *data)
{
	print_error_if_exists(data, expression->node, expression->semantic_error);
};

void mCc_print_error_declaration_primitive(
    struct mCc_ast_declaration *declaration, void *data)
{
	print_error_if_exists(data, declaration->node, declaration->semantic_error);
};

void mCc_print_error_declaration_array(struct mCc_ast_declaration *declaration,
                                       void *data)
{
	print_error_if_exists(data, declaration->node, declaration->semantic_error);
};

void mCc_print_error_assignment_primitive(struct mCc_ast_assignment *assignment,
                                          void *data)
{
	print_error_if_exists(data, assignment->node, assignment->semantic_error);
};

void mCc_print_error_assignment_array(struct mCc_ast_assignment *assignment,
                                      void *data)
{
	print_error_if_exists(data, assignment->node, assignment->semantic_error);
};
