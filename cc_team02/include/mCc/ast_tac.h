#ifndef MCC_AST_TAC_H
#define MCC_AST_TAC_H

#include "mCc/ast/tac/ast_basic_tac.h"
#include "mCc/ast/tac/ast_tac_assignment.h"
#include "mCc/ast/tac/ast_tac_declaration.h"
#include "mCc/ast/tac/ast_tac_expression.h"
#include "mCc/ast/tac/ast_tac_function.h"
#include "mCc/ast/tac/ast_tac_identifier.h"
#include "mCc/ast/tac/ast_tac_literal.h"
#include "mCc/ast/tac/ast_tac_program.h"
#include "mCc/ast/tac/ast_tac_statement.h"

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

#ifdef __cplusplus
}
#endif

#endif
