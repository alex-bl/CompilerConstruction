#ifndef MCC_AST_TAC_H
#define MCC_AST_TAC_H

#include "basic_tac_print.h"
#include "tac_print_assignment.h"
#include "tac_print_declaration.h"
#include "tac_print_expression.h"
#include "tac_print_function.h"
#include "tac_print_identifier.h"
#include "tac_print_literal.h"
#include "tac_print_program.h"
#include "tac_print_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

/*void mCc_ast_tac_print_assignment(FILE *out,
                                  struct mCc_ast_assignment *assignment);

void mCc_ast_tac_print_statement(FILE *out,
                                 struct mCc_ast_statement *statement);

void mCc_ast_tac_print_program(FILE *out, struct mCc_ast_program *program);

void mCc_ast_tac_print_literal(FILE *out, struct mCc_ast_literal *literal);

void mCc_ast_tac_print_identifier(FILE *out,
                                  struct mCc_ast_identifier *identifier);

void mCc_ast_tac_print_function_def(FILE *out,
                                    struct mCc_ast_function_def *function_def);

void mCc_ast_tac_print_function_call(
    FILE *out, struct mCc_ast_function_call *function_call);

void mCc_ast_tac_print_expression(FILE *out,
                                  struct mCc_ast_expression *expression);

void mCc_ast_tac_print_declaration(FILE *out,
                                   struct mCc_ast_declaration *declaration);*/

void mCc_tac_print_start_program(struct mCc_tac_element *tac, void *data);

#ifdef __cplusplus
}
#endif

#endif
