#ifndef MCC_SYMTAB_HANDLE_H
#define MCC_SYMTAB_HANDLE_H

#include <stdbool.h>

#include "mCc/ast.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validator.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_build_assignment(struct mCc_ast_assignment *assignment);

void mCc_symtab_build_statement(struct mCc_ast_statement *statement);

// TODO: only this one needed?
bool mCc_symtab_perform_semantic_checks(struct mCc_ast_program *program);

void mCc_symtab_build_literal(struct mCc_ast_literal *literal);

void mCc_symtab_build_identifier(struct mCc_ast_identifier *identifier);

void mCc_symtab_build_function_def(struct mCc_ast_function_def *function_def);

void mCc_symtab_build_function_call(
    struct mCc_ast_function_call *function_call);

void mCc_symtab_build_expression(struct mCc_ast_expression *expression);

void mCc_symtab_build_declaration(struct mCc_ast_declaration *declaration);

#ifdef __cplusplus
}
#endif

#endif
