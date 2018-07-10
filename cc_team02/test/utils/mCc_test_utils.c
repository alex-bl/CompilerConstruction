#include "mCc_test/mCc_test_utils.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "config.h"
#include "mCc/ast_print.h"

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
void build_file_name(char buffer[], size_t size, const char *dir,
                     const char *prefix, const char *file_name,
                     const char *suffix)
{
	snprintf(buffer, size, "%s/%s%s%s", dir, prefix, file_name, suffix);
}

FILE *open_file(const char *dir, const char *prefix, const char *file_name,
                const char *suffix)
{
	char dot_file_name[strlen(dir) + NAME_SIZE];
	build_file_name(dot_file_name, sizeof(dot_file_name), dir, prefix,
	                file_name, suffix);
	return fopen(dot_file_name, "w");
}

void test_print_and_free_ast_literal(struct mCc_ast_literal *lit,
                                     const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_literal(fp, lit);

	fclose(fp);
	mCc_ast_delete_literal(lit);
}

void test_print_and_free_ast_expression(struct mCc_ast_expression *expr,
                                        const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_expression(fp, expr);

	fclose(fp);
	mCc_ast_delete_expression(expr);
}

void test_print_and_free_ast_identifier(struct mCc_ast_identifier *identifier,
                                        const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_identifier(fp, identifier);

	fclose(fp);
	mCc_ast_delete_identifier(identifier);
}

void test_print_and_free_ast_declaration(
    struct mCc_ast_declaration *declaration, const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_declaration(fp, declaration);

	fclose(fp);
	mCc_ast_delete_declaration(declaration);
}

void test_print_and_free_ast_program(struct mCc_ast_program *program,
                                     const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_program(fp, program);

	fclose(fp);
	mCc_ast_delete_program(program);
}

void test_print_and_free_ast_function_def(struct mCc_ast_function_def *function,
                                          const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_function_def(fp, function);

	fclose(fp);
	mCc_ast_delete_function_def(function);
}

void test_print_and_free_ast_function_call(
    struct mCc_ast_function_call *function, const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_function_call(fp, function);

	fclose(fp);
	mCc_ast_delete_function_call(function);
}

void test_print_and_free_ast_assignment(struct mCc_ast_assignment *assignment,
                                        const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_assignment(fp, assignment);

	fclose(fp);
	mCc_ast_delete_assignment(assignment);
}

void test_print_and_free_ast_statement(struct mCc_ast_statement *statement,
                                       const char *file_name)
{
	FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_statement(fp, statement);

	fclose(fp);
	mCc_ast_delete_statement(statement);
}

/*================================================== commonly needed mocks for
 * tests */

struct mCc_ast_identifier *
mCc_test_build_const_test_identifier(const char *identifier)
{
	return mCc_ast_new_identifier(strndup(identifier, strlen(identifier)+1));
}

struct mCc_ast_expression *mCc_test_build_test_lit_expression(int value)
{
	return mCc_ast_new_expression_literal(mCc_ast_new_literal_int(value));
}

struct mCc_ast_expression *mCc_test_build_test_lit_expression_float(float value)
{
	return mCc_ast_new_expression_literal(mCc_ast_new_literal_float(value));
}

struct mCc_ast_expression *mCc_test_build_test_lit_expression_bool(bool value)
{
	return mCc_ast_new_expression_literal(mCc_ast_new_literal_bool(value));
}

struct mCc_ast_literal *mCc_test_build_test_lit_string(const char *value)
{
	return mCc_ast_new_literal_string(strndup(value, strlen(value)+1));
}

struct mCc_ast_expression *
mCc_test_build_test_identifier(const char *identifier)
{
	return mCc_ast_new_expression_identifier(
	    mCc_test_build_const_test_identifier(identifier));
}

struct mCc_ast_expression *
mCc_test_build_test_binary_expression(int value_1, int value_2,
                                      enum mCc_ast_binary_op op)
{
	return mCc_ast_new_expression_binary_op(
	    op, mCc_test_build_test_lit_expression(value_1),
	    mCc_test_build_test_lit_expression(value_2));
}

struct mCc_ast_expression *
mCc_test_build_test_binary_expression_float(float value_1, float value_2,
                                            enum mCc_ast_binary_op op)
{
	return mCc_ast_new_expression_binary_op(
	    op, mCc_test_build_test_lit_expression_float(value_1),
	    mCc_test_build_test_lit_expression_float(value_2));
}

struct mCc_ast_declaration *
mCc_test_build_test_declaration(const char *identifier,
                                enum mCc_ast_data_type type)
{
	return mCc_ast_new_primitive_declaration(
	    type, mCc_test_build_const_test_identifier(identifier));
}

struct mCc_ast_declaration *
mCc_test_build_test_array_declaration(const char *identifier,
                                      enum mCc_ast_data_type type, size_t size)
{
	return mCc_ast_new_array_declaration(
	    type, mCc_test_build_const_test_identifier(identifier), size);
}

struct mCc_ast_assignment *
mCc_test_build_test_assignment(const char *identifier, int value)
{
	return mCc_ast_new_primitive_assignment(
	    mCc_test_build_const_test_identifier(identifier),
	    mCc_test_build_test_lit_expression(value));
}

struct mCc_ast_function_def *
mCc_test_build_test_function_def(enum mCc_ast_data_type return_type,
                                 const char *identifier,
                                 struct mCc_ast_expression *return_expr)
{
	return mCc_ast_new_non_parameterized_function_def(
	    mCc_test_build_const_test_identifier(identifier), return_type,
	    (return_expr ? mCc_ast_new_return_statement(return_expr) : NULL));
}
