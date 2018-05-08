#ifndef MCC_MCC_TEST_UTILS_H
#define MCC_MCC_TEST_UTILS_H

#include "mCc/ast.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Builds the file-name
 *
 * @param buffer
 * 			Where name is copied
 * @param size
 * 			The size
 * @param file_name
 * 			The file-name
 */
void build_file_name(char buffer[], size_t size, const char *file_name);

FILE *open_file(const char *file_name);
void test_print_and_free_ast_literal(struct mCc_ast_literal *lit,
                                     const char *file_name);

void test_print_and_free_ast_expression(struct mCc_ast_expression *expr,
                                        const char *file_name);
void test_print_and_free_ast_identifier(struct mCc_ast_identifier *identifier,
                                        const char *file_name);
void test_print_and_free_ast_declaration(
    struct mCc_ast_declaration *declaration, const char *file_name);
void test_print_and_free_ast_program(struct mCc_ast_program *program,
                                     const char *file_name);
void test_print_and_free_ast_function_def(struct mCc_ast_function_def *function,
                                          const char *file_name);

void test_print_and_free_ast_function_call(
    struct mCc_ast_function_call *function, const char *file_name);

void test_print_and_free_ast_assignment(struct mCc_ast_assignment *assignment,
                                        const char *file_name);

void test_print_and_free_ast_statement(struct mCc_ast_statement *statement,
                                       const char *file_name);

/*================================================== commonly needed mocks for
 * tests */

struct mCc_ast_identifier *
mCc_test_build_const_test_identifier(const char *identifier);

struct mCc_ast_expression *mCc_test_build_test_lit_expression(int value);

struct mCc_ast_expression *
mCc_test_build_test_lit_expression_float(float value);

struct mCc_ast_expression *mCc_test_build_test_lit_expression_bool(bool value);

struct mCc_ast_literal *mCc_test_build_test_lit_string(const char *value);

struct mCc_ast_expression *
mCc_test_build_test_identifier(const char *identifier);

struct mCc_ast_expression *
mCc_test_build_test_binary_expression(int value_1, int value_2,
                                      enum mCc_ast_binary_op op);

struct mCc_ast_expression *
mCc_test_build_test_binary_expression_float(float value_1, float value_2,
                                            enum mCc_ast_binary_op op);

struct mCc_ast_declaration *
mCc_test_build_test_declaration(const char *identifier,
                                enum mCc_ast_data_type type);

struct mCc_ast_declaration *
mCc_test_build_test_array_declaration(const char *identifier,
                                      enum mCc_ast_data_type type, size_t size);

struct mCc_ast_assignment *
mCc_test_build_test_assignment(const char *identifier, int value);

struct mCc_ast_function_def *
mCc_test_build_test_function_def(enum mCc_ast_data_type return_type,
                                 const char *identifier,
                                 struct mCc_ast_expression *return_expr);

#ifdef __cplusplus
}
#endif

#endif
