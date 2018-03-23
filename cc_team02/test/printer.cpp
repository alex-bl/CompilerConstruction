#include "mCc/ast.h"
#include "mCc/ast/print/ast_print_literal.h"
#include "gtest/gtest.h"
#include <stdbool.h>
#include <stddef.h>

#define DOT_OUTPUT_DIR "./bin/test/"
#define DOT_FILE_SUFFIX ".dot"
#define NAME_SIZE 64

void build_file_name(char buffer[], size_t size, const char *file_name)
{
	snprintf(buffer, size, "%s%s%s", DOT_OUTPUT_DIR, file_name,
	         DOT_FILE_SUFFIX);
}

TEST(AstPrint, PrintInt)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_int(12);
	char dot_file_name[NAME_SIZE];

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_INT);
	ASSERT_EQ(lit->i_value, 12);

	build_file_name(dot_file_name, sizeof(dot_file_name), "print_lit_int");

	FILE *fp = fopen(dot_file_name, "w");

	mCc_ast_print_dot_literal(fp, lit);

	fclose(fp);
	mCc_ast_delete_literal(lit);
}

TEST(AstPrint, PrintFloat)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_float(1.22);
	char dot_file_name[NAME_SIZE];

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_FLOAT);
	ASSERT_EQ(lit->f_value, 1.22);

	build_file_name(dot_file_name, sizeof(dot_file_name), "print_lit_float");

	FILE *fp = fopen(dot_file_name, "w");

	mCc_ast_print_dot_literal(fp, lit);

	fclose(fp);
	mCc_ast_delete_literal(lit);
}

TEST(AstPrint, PrintBool)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_bool(true);
	char dot_file_name[NAME_SIZE];

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_BOOL);
	ASSERT_EQ(lit->b_value, true);

	build_file_name(dot_file_name, sizeof(dot_file_name), "print_lit_bool");

	FILE *fp = fopen(dot_file_name, "w");

	mCc_ast_print_dot_literal(fp, lit);

	fclose(fp);
	mCc_ast_delete_literal(lit);
}

TEST(AstPrint, PrintString)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_string("test");
	char dot_file_name[NAME_SIZE];

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_STRING);
	ASSERT_EQ(lit->s_value, "test");

	build_file_name(dot_file_name, sizeof(dot_file_name), "print_lit_string");

	FILE *fp = fopen(dot_file_name, "w");

	mCc_ast_print_dot_literal(fp, lit);

	fclose(fp);
	mCc_ast_delete_literal(lit);
}
