#ifndef MCC_SYMTAB_HANDLE_H
#define MCC_SYMTAB_HANDLE_H

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_assignment.h"
#include "mCc/ast/print/ast_print_declaration.h"
#include "mCc/ast/print/ast_print_expression.h"
#include "mCc/ast/print/ast_print_function.h"
#include "mCc/ast/print/ast_print_identifier.h"
#include "mCc/ast/print/ast_print_literal.h"
#include "mCc/ast/print/ast_print_program.h"
#include "mCc/ast/print/ast_print_statement.h"
#include "mCc/symtab/symbol_table.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_symtab_build_assignment(struct mCc_symbol_table *symbol_table,
                                 int *start_scope_level,
                                 struct mCc_ast_assignment *assignment);

void mCc_symtab_build_statement(struct mCc_symbol_table *symbol_table,
                                int *start_scope_level,
                                struct mCc_ast_statement *statement);

void mCc_symtab_build_program(struct mCc_symbol_table *symbol_table,
                              int *start_scope_level,
                              struct mCc_ast_program *program);

void mCc_symtab_build_literal(struct mCc_symbol_table *symbol_table,
                              int *start_scope_level,
                              struct mCc_ast_literal *literal);

void mCc_symtab_build_identifier(struct mCc_symbol_table *symbol_table,
                                 int *start_scope_level,
                                 struct mCc_ast_identifier *identifier);

void mCc_symtab_build_function_def(struct mCc_symbol_table *symbol_table,
                                   int *start_scope_level,
                                   struct mCc_ast_function_def *function_def);

void mCc_symtab_build_function_call(
    struct mCc_symbol_table *symbol_table, int *start_scope_level,
    struct mCc_ast_function_call *function_call);

void mCc_symtab_build_expression(struct mCc_symbol_table *symbol_table,
                                 int *start_scope_level,
                                 struct mCc_ast_expression *expression);

void mCc_symtab_build_declaration(struct mCc_symbol_table *symbol_table,
                                  int *start_scope_level,
                                  struct mCc_ast_declaration *declaration);

#ifdef __cplusplus
}
#endif

#endif
