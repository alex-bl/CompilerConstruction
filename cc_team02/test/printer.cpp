#include "mCc/ast.h"
#include "mCc/ast_print.h"
#include "gtest/gtest.h"
#include <stdbool.h>
#include <stddef.h>

#define DOT_OUTPUT_DIR "DOT_"
#define DOT_FILE_SUFFIX ".dot"
#define NAME_SIZE 64

/**
 * This file lists tests that print given expressions out in a file to test the
 * graph-correctness manually. It just tests the print-functionality without
 * assertions. The ast-construction is tested in "builder.cpp".
 */

/*===========================================================================
 * test infrastructure*/
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

/*===========================================================================
 * literal tests*/
TEST(AstPrintLiteral, PrintLiteralInt)
{
	struct mCc_ast_literal *lit = mCc_ast_new_literal_int(12);

	test_print_ast_literal(lit, "literal_int");
}

TEST(AstPrintLiteral, PrintLiteralFloat)
{
	struct mCc_ast_literal *lit = mCc_ast_new_literal_float(1.22);

	test_print_ast_literal(lit, "literal_float");
}

TEST(AstPrintLiteral, PrintLiteralBool)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_bool(true);

	test_print_ast_literal(lit, "literal_bool");
}

TEST(AstPrintLiteral, PrintLiteralString)
{
	struct mCc_ast_literal *lit = mCc_ast_new_literal_string("test");

	test_print_ast_literal(lit, "literal_string");
}

/*===========================================================================
 * expresion tests*/

TEST(AstPrintExpression, PrintExpressionBinaryOp)
{
	struct mCc_ast_literal *lit_left = mCc_ast_new_literal_int(4);
	struct mCc_ast_literal *lit_right = mCc_ast_new_literal_int(1);

	struct mCc_ast_expression *expression_binary_op =
	    mCc_ast_new_expression_binary_op(
	        MCC_AST_BINARY_OP_MUL, mCc_ast_new_expression_literal(lit_left),
	        mCc_ast_new_expression_literal(lit_right));

	test_print_ast_expression(expression_binary_op, "expression_binary");
}

TEST(AstPrintExpression, PrintExpressionBinaryOpAdvanced)
{
	struct mCc_ast_literal *lit_left_1 = mCc_ast_new_literal_int(4);
	struct mCc_ast_literal *lit_right_1 = mCc_ast_new_literal_int(1);

	struct mCc_ast_literal *lit_left_2 = mCc_ast_new_literal_float(3.4);
	struct mCc_ast_literal *lit_right_2 = mCc_ast_new_literal_float(2.3);

	struct mCc_ast_expression *left_side = mCc_ast_new_expression_binary_op(
	    MCC_AST_BINARY_OP_ADD, mCc_ast_new_expression_literal(lit_left_1),
	    mCc_ast_new_expression_literal(lit_right_1));

	struct mCc_ast_expression *right_side = mCc_ast_new_expression_binary_op(
	    MCC_AST_BINARY_OP_DIV, mCc_ast_new_expression_literal(lit_left_2),
	    mCc_ast_new_expression_literal(lit_right_2));

	struct mCc_ast_expression *expression_binary_op =
	    mCc_ast_new_expression_binary_op(MCC_AST_BINARY_OP_EQUALS, left_side,
	                                     right_side);

	test_print_ast_expression(expression_binary_op,
	                          "expression_binary_advanced");
}

TEST(AstPrintExpression, PrintExpressionBinaryOpUnbalanced)
{
	struct mCc_ast_literal *lit_left_1 = mCc_ast_new_literal_int(4);

	struct mCc_ast_literal *lit_left_2 = mCc_ast_new_literal_float(3.4);
	struct mCc_ast_literal *lit_right_2 = mCc_ast_new_literal_float(2.3);

	struct mCc_ast_expression *left_side =
	    mCc_ast_new_expression_literal(lit_left_1);

	struct mCc_ast_expression *right_side = mCc_ast_new_expression_binary_op(
	    MCC_AST_BINARY_OP_SUB, mCc_ast_new_expression_literal(lit_left_2),
	    mCc_ast_new_expression_literal(lit_right_2));

	struct mCc_ast_expression *expression_binary_op =
	    mCc_ast_new_expression_binary_op(MCC_AST_BINARY_OP_NOT_EQUALS,
	                                     left_side, right_side);

	test_print_ast_expression(expression_binary_op,
	                          "expression_binary_unbalanced");
}

TEST(AstPrintExpression, PrintExpressionUnaryOp)
{
	struct mCc_ast_literal *lit_right = mCc_ast_new_literal_int(1);

	struct mCc_ast_expression *expression_unary_op =
	    mCc_ast_new_expression_unary_op(
	        MCC_AST_UNARY_OP_NEGATION,
	        mCc_ast_new_expression_literal(lit_right));

	test_print_ast_expression(expression_unary_op, "expression_unary");
}

TEST(AstPrintExpression, PrintExpressionParenth)
{
	struct mCc_ast_literal *lit_right = mCc_ast_new_literal_int(1);

	struct mCc_ast_expression *expression_parent =
	    mCc_ast_new_expression_parenth(
	        mCc_ast_new_expression_literal(lit_right));

	test_print_ast_expression(expression_parent, "expression_parenth");
}
/*
 * Identifier currently not implemented...
 *
TEST(AstPrintExpression, PrintExpressionIdentifier)
{
    struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("val");

    struct mCc_ast_expression *expression_identifier =
        mCc_ast_new_expression_identifier(identifier);

    test_print_ast_expression(expression_identifier, "expression_identifier");
}
*/
