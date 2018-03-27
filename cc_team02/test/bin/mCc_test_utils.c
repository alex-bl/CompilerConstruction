#include "mCc_test/mCc_test_utils.h"
#include "mCc/ast_print.h"
#include <stdbool.h>
#include <stddef.h>

#define DOT_OUTPUT_DIR "DOT_"
#define DOT_FILE_SUFFIX ".dot"
#define NAME_SIZE 64

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
void build_file_name(char buffer[], size_t size, const char *file_name)
{
	snprintf(buffer, size, "%s%s%s", DOT_OUTPUT_DIR, file_name,
	         DOT_FILE_SUFFIX);
}

FILE *open_file(const char *file_name)
{
	char dot_file_name[NAME_SIZE];

	build_file_name(dot_file_name, sizeof(dot_file_name), file_name);

	return fopen(dot_file_name, "w");
}

void test_print_ast_literal(struct mCc_ast_literal *lit, const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_literal(fp, lit);

	fclose(fp);
	mCc_ast_delete_literal(lit);
}

void test_print_ast_expression(struct mCc_ast_expression *expr,
                               const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_expression(fp, expr);

	fclose(fp);
	mCc_ast_delete_expression(expr);
}

void test_print_ast_identifier(struct mCc_ast_identifier *identifier,
                               const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_identifier(fp, identifier);

	fclose(fp);
	mCc_ast_delete_identifier(identifier);
}

void test_print_ast_declaration(struct mCc_ast_declaration *declaration,
                                const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_declaration(fp, declaration);

	fclose(fp);
	mCc_ast_delete_declaration(declaration);
}

void test_print_ast_program(struct mCc_ast_program *program,
                            const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_program(fp, program);

	fclose(fp);
	mCc_ast_delete_program(program);
}

void test_print_ast_function_def(struct mCc_ast_function_def *function,
                                 const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_function_def(fp, function);

	fclose(fp);
	mCc_ast_delete_function_def(function);
}

void test_print_ast_function_call(struct mCc_ast_function_call *function,
                                  const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_function_call(fp, function);

	fclose(fp);
	mCc_ast_delete_function_call(function);
}

void test_print_ast_assignment(struct mCc_ast_assignment *assignment,
                               const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_assignment(fp, assignment);

	fclose(fp);
	mCc_ast_delete_assignment(assignment);
}

void test_print_ast_statement(struct mCc_ast_statement *statement,
                              const char *file_name)
{
	FILE *fp = open_file(file_name);
	mCc_ast_print_dot_statement(fp, statement);

	fclose(fp);
	mCc_ast_delete_statement(statement);
}

/*================================================== commonly needed mocks for
 * tests */

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

struct mCc_ast_expression *
mCc_test_build_test_identifier(const char *identifier)
{
	return mCc_ast_new_expression_identifier(
	    mCc_ast_new_identifier(identifier));
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
                                enum mCc_ast_literal_type type)
{
	return mCc_ast_new_primitive_declaration(
	    type, mCc_ast_new_identifier(identifier));
}

struct mCc_ast_assignment *
mCc_test_build_test_assignment(const char *identifier, int value)
{
	return mCc_ast_new_primitive_assignment(
	    mCc_ast_new_identifier(identifier),
	    mCc_test_build_test_lit_expression(value));
}

struct mCc_ast_function_def *
mCc_test_build_test_function_def(enum mCc_ast_function_return_type return_type,
                                 const char *identifier,
                                 struct mCc_ast_expression *return_expr)
{
	return mCc_ast_new_non_parameterized_function_def(
	    mCc_ast_new_identifier(identifier), return_type,
	    (return_expr ? mCc_ast_new_expression_statement(return_expr) : NULL));
}
