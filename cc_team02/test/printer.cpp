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

TEST(AstPrintExpression, PrintExpressionIdentifier)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("val");

	struct mCc_ast_expression *expression_identifier =
	    mCc_ast_new_expression_identifier(identifier);

	test_print_ast_expression(expression_identifier, "expression_identifier");
}

TEST(AstPrintExpression, PrintExpressionIdentifierUnaryOp)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("isBinary");
	struct mCc_ast_expression *expression_identifier =
	    mCc_ast_new_expression_identifier(identifier);

	struct mCc_ast_expression *expression_unary_op =
	    mCc_ast_new_expression_unary_op(MCC_AST_UNARY_OP_NEGATION,
	                                    expression_identifier);

	test_print_ast_expression(expression_unary_op,
	                          "expression_identifier_unary");
}

TEST(AstPrintExpression, PrintExpressionArrayIdentifier)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("arr");

	struct mCc_ast_literal *index_left = mCc_ast_new_literal_int(2);
	struct mCc_ast_literal *index_right = mCc_ast_new_literal_int(3);

	struct mCc_ast_expression *left_side =
	    mCc_ast_new_expression_literal(index_left);
	struct mCc_ast_expression *right_side =
	    mCc_ast_new_expression_literal(index_right);

	struct mCc_ast_expression *expression_index =
	    mCc_ast_new_expression_binary_op(MCC_AST_BINARY_OP_ADD, left_side,
	                                     right_side);

	struct mCc_ast_expression *expression_arr_identifier =
	    mCc_ast_new_expression_array_identifier(identifier, expression_index);

	test_print_ast_expression(expression_arr_identifier,
	                          "expression_identifier_array");
}

TEST(AstPrintExpression, PrintExpressionFunctionCallSimple)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_func");
	struct mCc_ast_literal *lit = mCc_ast_new_literal_int(2);
	struct mCc_ast_expression *param = mCc_ast_new_expression_literal(lit);

	struct mCc_ast_function_call *function_call =
	    mCc_ast_new_parameterized_function_call(identifier, param);

	struct mCc_ast_expression *expr_function_call =
	    mCc_ast_new_expression_function_call(function_call);

	test_print_ast_expression(expr_function_call,
	                          "expression_function_call_args");
}

TEST(AstPrintExpression, PrintExpressionFunctionCallConcated)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_func");
	struct mCc_ast_literal *lit_1 = mCc_ast_new_literal_int(2);
	struct mCc_ast_literal *lit_2 = mCc_ast_new_literal_int(3);

	struct mCc_ast_expression *param_1 = mCc_ast_new_expression_literal(lit_1);
	struct mCc_ast_expression *param_2 = mCc_ast_new_expression_literal(lit_2);
	// concat
	param_1->next_expr = param_2;

	struct mCc_ast_function_call *function_call =
	    mCc_ast_new_parameterized_function_call(identifier, param_1);

	struct mCc_ast_expression *expr_function_call =
	    mCc_ast_new_expression_function_call(function_call);

	test_print_ast_expression(expr_function_call,
	                          "expression_function_call_concatted_args");
}

/*===========================================================================
 * identifier tests*/

TEST(AstPrintIdentifier, PrintIdentifier)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_var");
	test_print_ast_identifier(identifier, "identifier_simple");
}

/*===========================================================================
 * declaration tests*/

TEST(AstPrintDeclaration, PrintDeclarationPrimitive)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_float");
	struct mCc_ast_declaration *declaration_primitive =
	    mCc_ast_new_primitive_declaration(MCC_AST_LITERAL_TYPE_FLOAT,
	                                      identifier);
	test_print_ast_declaration(declaration_primitive, "declaration_primitive");
}

TEST(AstPrintDeclaration, PrintDeclarationArray)
{
	struct mCc_ast_identifier *identifier =
	    mCc_ast_new_identifier("my_float_arr");
	struct mCc_ast_declaration *declaration_array =
	    mCc_ast_new_array_declaration(MCC_AST_LITERAL_TYPE_FLOAT, identifier,
	                                  100);
	test_print_ast_declaration(declaration_array, "declaration_array");
}

TEST(AstPrintDeclaration, PrintDeclarationConcated)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_float");
	struct mCc_ast_declaration *declaration_concated =
	    mCc_ast_new_primitive_declaration(MCC_AST_LITERAL_TYPE_FLOAT,
	                                      identifier);

	struct mCc_ast_identifier *identifier_arr =
	    mCc_ast_new_identifier("my_float_arr");
	struct mCc_ast_declaration *declaration_array =
	    mCc_ast_new_array_declaration(MCC_AST_LITERAL_TYPE_FLOAT,
	                                  identifier_arr, 100);

	// do a concatenation
	declaration_concated->next_declaration = declaration_array;

	test_print_ast_declaration(declaration_concated, "declaration_concated");
}

/*===========================================================================
 * function tests*/
TEST(AstPrintFunctionDef, PrintFunctionDefSimple)
{
	ASSERT_TRUE(false);
}

TEST(AstPrintFunctionDef, PrintFunctionDefAdvanced)
{
	ASSERT_TRUE(false);
}

TEST(AstPrintFunctionCall, PrintFunctionCallSimple)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_func");
	struct mCc_ast_function_call *function_call =
	    mCc_ast_new_non_parameterized_function_call(identifier);

	test_print_ast_function_call(function_call, "function_call_simple");
}

TEST(AstPrintFunctionCall, PrintFunctionCallConcated)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_func");
	struct mCc_ast_literal *lit_1 = mCc_ast_new_literal_int(2);
	struct mCc_ast_literal *lit_2 = mCc_ast_new_literal_int(3);

	struct mCc_ast_expression *param_1 = mCc_ast_new_expression_literal(lit_1);
	struct mCc_ast_expression *param_2 = mCc_ast_new_expression_literal(lit_2);

	param_1->next_expr = param_2;

	struct mCc_ast_function_call *function_call =
	    mCc_ast_new_parameterized_function_call(identifier, param_1);

	test_print_ast_function_call(function_call, "function_call_concated");
}

/*===========================================================================
 * program tests*/

/**
 * TODO: implement
 */
TEST(AstPrintProgram, PrintProgramFunctionSimple)
{
	ASSERT_TRUE(false);
}

/**
 * TODO: implement
 */
TEST(AstPrintProgram, PrintProgramFunctionConcated)
{
	// reminder
	ASSERT_TRUE(false);
}
