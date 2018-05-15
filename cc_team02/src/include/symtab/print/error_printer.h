#ifndef MCC_ERROR_PRINTER_H
#define MCC_ERROR_PRINTER_H

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

void mCc_print_error_statement_if(struct mCc_ast_statement *statement,
                                  void *data);

void mCc_print_error_statement_while(struct mCc_ast_statement *statement,
                                     void *data);
void mCc_print_error_statement_return(struct mCc_ast_statement *statement,
                                      void *data);
void mCc_print_error_statement_declaration(struct mCc_ast_statement *statement,
                                           void *data);
void mCc_print_error_statement_assignment(struct mCc_ast_statement *statement,
                                          void *data);
void mCc_print_error_statement_expression(struct mCc_ast_statement *statement,
                                          void *data);

void mCc_print_error_program(struct mCc_ast_program *program, void *data);

void mCc_print_error_identifier(struct mCc_ast_identifier *identifier,
                                void *data);

void mCc_print_error_function_def(struct mCc_ast_function_def *def, void *data);

void mCc_print_error_function_call(struct mCc_ast_function_call *call,
                                   void *data);

void mCc_print_error_expression_literal(struct mCc_ast_expression *expression,
                                        void *data);

void mCc_print_error_expression_binary_op(struct mCc_ast_expression *expression,
                                          void *data);

void mCc_print_error_expression_parenth(struct mCc_ast_expression *expression,
                                        void *data);

void mCc_print_error_expression_identifier(
    struct mCc_ast_expression *expression, void *data);

void mCc_print_error_expression_identifier_array(
    struct mCc_ast_expression *expression, void *data);

void mCc_print_error_expression_function_call(
    struct mCc_ast_expression *expression, void *data);

void mCc_print_error_expression_unary_op(struct mCc_ast_expression *expression,
                                         void *data);

void mCc_print_error_declaration_primitive(
    struct mCc_ast_declaration *declaration, void *data);

void mCc_print_error_declaration_array(struct mCc_ast_declaration *declaration,
                                       void *data);

void mCc_print_error_assignment_primitive(struct mCc_ast_assignment *assignment,
                                          void *data);

void mCc_print_error_assignment_array(struct mCc_ast_assignment *assignment,
                                      void *data);

#ifdef __cplusplus
}
#endif

#endif
