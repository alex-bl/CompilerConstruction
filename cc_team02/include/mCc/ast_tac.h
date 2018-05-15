#ifndef MCC_AST_TAC_H
#define MCC_AST_TAC_H

#include "basic_tac.h"
#include "tac_assignment.h"
#include "tac_declaration.h"
#include "tac_expression.h"
#include "tac_function.h"
#include "tac_identifier.h"
#include "tac_literal.h"
#include "tac_program.h"
#include "tac_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_ast_tac_assignment(FILE *out,
                                  struct mCc_ast_assignment *assignment);

void mCc_ast_tac_statement(FILE *out,
                                 struct mCc_ast_statement *statement);

void mCc_ast_tac_program(FILE *out, struct mCc_ast_program *program);

void mCc_ast_tac_literal(FILE *out, struct mCc_ast_literal *literal);

void mCc_ast_tac_identifier(FILE *out,
                                  struct mCc_ast_identifier *identifier);

void mCc_ast_tac_function_def(FILE *out,
                                    struct mCc_ast_function_def *function_def);

void mCc_ast_tac_function_call(
    FILE *out, struct mCc_ast_function_call *function_call);

void mCc_ast_tac_expression(FILE *out,
                                  struct mCc_ast_expression *expression);

void mCc_ast_tac_declaration(FILE *out,
                                   struct mCc_ast_declaration *declaration);

struct mCc_tac_element mCc_tac_start_program(struct mCc_tac_element *tac,
                           struct mCc_ast_program *program);

#ifdef __cplusplus
}
#endif

#endif
