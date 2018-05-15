#ifndef MCC_AST_PRINT_H
#define MCC_AST_PRINT_H

#include "ast_basic_printing.h"
#include "ast_print_assignment.h"
#include "ast_print_declaration.h"
#include "ast_print_expression.h"
#include "ast_print_function.h"
#include "ast_print_identifier.h"
#include "ast_print_literal.h"
#include "ast_print_program.h"
#include "ast_print_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_print_dot_assignment(FILE *out,
                                  struct mCc_ast_assignment *assignment);

void mCc_ast_print_dot_statement(FILE *out,
                                 struct mCc_ast_statement *statement);

void mCc_ast_print_dot_program(FILE *out, struct mCc_ast_program *program);

void mCc_ast_print_dot_literal(FILE *out, struct mCc_ast_literal *literal);

void mCc_ast_print_dot_identifier(FILE *out,
                                  struct mCc_ast_identifier *identifier);

void mCc_ast_print_dot_function_def(FILE *out,
                                    struct mCc_ast_function_def *function_def);

void mCc_ast_print_dot_function_call(
    FILE *out, struct mCc_ast_function_call *function_call);

void mCc_ast_print_dot_expression(FILE *out,
                                  struct mCc_ast_expression *expression);

void mCc_ast_print_dot_declaration(FILE *out,
                                   struct mCc_ast_declaration *declaration);

#ifdef __cplusplus
}
#endif

#endif
