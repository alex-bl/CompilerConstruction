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
	struct mCc_ast_expression *expression_binary_op =
	    mCc_test_build_test_binary_expression(4, 2, MCC_AST_BINARY_OP_MUL);

	test_print_ast_expression(expression_binary_op, "expression_binary");
}

TEST(AstPrintExpression, PrintExpressionBinaryOpAdvanced)
{
	struct mCc_ast_expression *left_side =
	    mCc_test_build_test_binary_expression(4, 2, MCC_AST_BINARY_OP_ADD);
	struct mCc_ast_expression *right_side =
	    mCc_test_build_test_binary_expression_float(3.4, 2.3,
	                                                MCC_AST_BINARY_OP_DIV);

	struct mCc_ast_expression *expression_binary_op =
	    mCc_ast_new_expression_binary_op(MCC_AST_BINARY_OP_EQUALS, left_side,
	                                     right_side);

	test_print_ast_expression(expression_binary_op,
	                          "expression_binary_advanced");
}

TEST(AstPrintExpression, PrintExpressionBinaryOpUnbalanced)
{
	struct mCc_ast_expression *left_side =
	    mCc_test_build_test_lit_expression(4);
	struct mCc_ast_expression *right_side =
	    mCc_test_build_test_binary_expression_float(3.4, 2.3,
	                                                MCC_AST_BINARY_OP_DIV);
	struct mCc_ast_expression *expression_binary_op =
	    mCc_ast_new_expression_binary_op(MCC_AST_BINARY_OP_NOT_EQUALS,
	                                     left_side, right_side);

	test_print_ast_expression(expression_binary_op,
	                          "expression_binary_unbalanced");
}

TEST(AstPrintExpression, PrintExpressionUnaryOp)
{
	struct mCc_ast_expression *expression_unary_op =
	    mCc_ast_new_expression_unary_op(
	        MCC_AST_UNARY_OP_NEGATION,
	        mCc_ast_new_expression_literal(mCc_ast_new_literal_bool(false)));

	test_print_ast_expression(expression_unary_op, "expression_unary");
}

TEST(AstPrintExpression, PrintExpressionParenth)
{
	struct mCc_ast_expression *expression_parent =
	    mCc_ast_new_expression_parenth(mCc_test_build_test_lit_expression(1));

	test_print_ast_expression(expression_parent, "expression_parenth");
}

TEST(AstPrintExpression, PrintExpressionIdentifier)
{
	struct mCc_ast_expression *expression_identifier =
	    mCc_ast_new_expression_identifier(mCc_ast_new_identifier("val"));

	test_print_ast_expression(expression_identifier, "expression_identifier");
}

TEST(AstPrintExpression, PrintExpressionIdentifierUnaryOp)
{
	struct mCc_ast_expression *expression_unary_op =
	    mCc_ast_new_expression_unary_op(
	        MCC_AST_UNARY_OP_NEGATION,
	        mCc_test_build_test_identifier("is_binary"));

	test_print_ast_expression(expression_unary_op,
	                          "expression_identifier_unary");
}

TEST(AstPrintExpression, PrintExpressionArrayIdentifier)
{
	struct mCc_ast_expression *expression_index =
	    mCc_ast_new_expression_binary_op(MCC_AST_BINARY_OP_ADD,
	                                     mCc_test_build_test_lit_expression(2),
	                                     mCc_test_build_test_lit_expression(3));

	struct mCc_ast_expression *expression_arr_identifier =
	    mCc_ast_new_expression_array_identifier(mCc_ast_new_identifier("arr"),
	                                            expression_index);

	test_print_ast_expression(expression_arr_identifier,
	                          "expression_identifier_array");
}

TEST(AstPrintExpression, PrintExpressionFunctionCallSimple)
{
	struct mCc_ast_function_call *function_call =
	    mCc_ast_new_parameterized_function_call(
	        mCc_ast_new_identifier("my_func"),
	        mCc_test_build_test_lit_expression(2));

	struct mCc_ast_expression *expr_function_call =
	    mCc_ast_new_expression_function_call(function_call);

	test_print_ast_expression(expr_function_call,
	                          "expression_function_call_args");
}

TEST(AstPrintExpression, PrintExpressionFunctionCallConcated)
{
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_func");
	struct mCc_ast_expression *param_1 = mCc_test_build_test_lit_expression(2);
	struct mCc_ast_expression *param_2 = mCc_test_build_test_lit_expression(3);

	// concat
	param_1->next_expr = param_2;

	struct mCc_ast_expression *expr_function_call =
	    mCc_ast_new_expression_function_call(
	        mCc_ast_new_parameterized_function_call(identifier, param_1));

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
	struct mCc_ast_declaration *declaration_primitive =
	    mCc_test_build_test_declaration("my_float", MCC_AST_LITERAL_TYPE_FLOAT);
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
	struct mCc_ast_declaration *declaration_concated =
	    mCc_test_build_test_declaration("my_float", MCC_AST_LITERAL_TYPE_FLOAT);

	struct mCc_ast_declaration *declaration_concated_other =
	    mCc_test_build_test_declaration("my_other_float",
	                                    MCC_AST_LITERAL_TYPE_FLOAT);

	struct mCc_ast_identifier *identifier_arr =
	    mCc_ast_new_identifier("my_float_arr");
	struct mCc_ast_declaration *declaration_array =
	    mCc_ast_new_array_declaration(MCC_AST_LITERAL_TYPE_FLOAT,
	                                  identifier_arr, 100);

	// do a concatenation
	declaration_array->next_declaration = declaration_concated_other;
	declaration_concated->next_declaration = declaration_array;

	test_print_ast_declaration(declaration_concated, "declaration_concated");
}
/*===========================================================================
 * assignment tests*/

TEST(AstPrintAssignment, PrintAssignmentPrimitive)
{
	struct mCc_ast_assignment *assignment =
	    mCc_test_build_test_assignment("my_var", 2);

	test_print_ast_assignment(assignment, "assignment_primitive");
}

TEST(AstPrintAssignment, PrintAssignmentArray)
{

	struct mCc_ast_assignment *assignment = mCc_ast_new_array_assignment(
	    mCc_ast_new_identifier("my_arr"), mCc_test_build_test_lit_expression(0),
	    mCc_test_build_test_lit_expression_float(3.4));

	test_print_ast_assignment(assignment, "assignment_arr");
}

/*===========================================================================
 * statement tests*/

TEST(AstPrintStatement, PrintStatementExpression)
{
	struct mCc_ast_expression *lit_expr = mCc_ast_new_expression_literal(
	    mCc_ast_new_literal_string("test_string"));

	struct mCc_ast_statement *statement =
	    mCc_ast_new_expression_statement(lit_expr);

	test_print_ast_statement(statement, "statement_expression");
}

TEST(AstPrintStatement, PrintStatementDeclaration)
{
	struct mCc_ast_statement *statement = mCc_ast_new_declaration_statement(
	    mCc_test_build_test_declaration("my_var", MCC_AST_LITERAL_TYPE_STRING));

	test_print_ast_statement(statement, "statement_declaration");
}

TEST(AstPrintStatement, PrintStatementAssignment)
{
	struct mCc_ast_assignment *assignment =
	    mCc_test_build_test_assignment("my_var", 10);

	struct mCc_ast_statement *statement =
	    mCc_ast_new_assign_statement(assignment);
	test_print_ast_statement(statement, "statement_assignment");
}

TEST(AstPrintStatement, PrintStatementIf)
{
	struct mCc_ast_expression *condition_expr =
	    mCc_ast_new_expression_literal(mCc_ast_new_literal_bool(true));

	struct mCc_ast_assignment *assignment_if =
	    mCc_test_build_test_assignment("my_var", 2);

	struct mCc_ast_assignment *assignment_else =
	    mCc_test_build_test_assignment("my_var", 14);

	struct mCc_ast_statement *if_else_statement = mCc_ast_new_if_statement(
	    condition_expr, mCc_ast_new_assign_statement(assignment_if),
	    mCc_ast_new_assign_statement(assignment_else));

	test_print_ast_statement(if_else_statement, "statement_if");
}

TEST(AstPrintStatement, PrintStatementWhile)
{
	struct mCc_ast_literal *condition = mCc_ast_new_literal_bool(true);
	struct mCc_ast_expression *condition_expr =
	    mCc_ast_new_expression_literal(condition);

	struct mCc_ast_statement *statement_1 = mCc_ast_new_assign_statement(
	    mCc_test_build_test_assignment("my_var", 2));

	struct mCc_ast_statement *statement_2 = mCc_ast_new_assign_statement(
	    mCc_test_build_test_assignment("my_second_var", 14));

	statement_1->next_statement = statement_2;

	struct mCc_ast_statement *while_statement =
	    mCc_ast_new_while_statement(condition_expr, statement_1);

	test_print_ast_statement(while_statement, "statement_while");
}

TEST(AstPrintStatement, PrintStatementReturn)
{
	struct mCc_ast_expression *return_expression =
	    mCc_ast_new_expression_literal(mCc_ast_new_literal_bool(true));

	struct mCc_ast_statement *return_statement =
	    mCc_ast_new_return_statement(return_expression);
	test_print_ast_statement(return_statement, "statement_return");
}

/*===========================================================================
 * function tests*/
TEST(AstPrintFunctionDef, PrintFunctionDefSimple)
{
	struct mCc_ast_identifier *identifier =
	    mCc_ast_new_identifier("my_bool_function");
	struct mCc_ast_literal *return_expr_lit = mCc_ast_new_literal_bool(true);
	struct mCc_ast_expression *return_expression =
	    mCc_ast_new_expression_literal(return_expr_lit);

	struct mCc_ast_statement *return_statement =
	    mCc_ast_new_return_statement(return_expression);

	struct mCc_ast_function_def *function_def =
	    mCc_ast_new_non_parameterized_function_def(
	        identifier, MCC_AST_FUNCTION_RETURN_TYPE_BOOL, return_statement);

	test_print_ast_function_def(function_def,
	                            "function_def_parameterless_simple");
}

TEST(AstPrintFunctionDef, PrintFunctionDefAdvanced)
{
	struct mCc_ast_statement *return_statement = mCc_ast_new_return_statement(
	    mCc_test_build_test_lit_expression_bool(true));

	struct mCc_ast_function_def *function_def =
	    mCc_ast_new_parameterized_function_def(
	        mCc_ast_new_identifier("my_bool_function"),
	        MCC_AST_FUNCTION_RETURN_TYPE_BOOL,
	        mCc_test_build_test_declaration("my_float_var",
	                                        MCC_AST_LITERAL_TYPE_FLOAT),
	        return_statement);

	test_print_ast_function_def(function_def, "function_def_parameter");
}

TEST(AstPrintFunctionCall, PrintFunctionCallSimple)
{
	struct mCc_ast_function_call *function_call =
	    mCc_ast_new_non_parameterized_function_call(
	        mCc_ast_new_identifier("my_func"));

	test_print_ast_function_call(function_call, "function_call_simple");
}

TEST(AstPrintFunctionCall, PrintFunctionCallConcated)
{
	struct mCc_ast_expression *param_1 = mCc_test_build_test_lit_expression(2);
	struct mCc_ast_expression *param_2 = mCc_test_build_test_lit_expression(4);

	param_1->next_expr = param_2;

	struct mCc_ast_function_call *function_call =
	    mCc_ast_new_parameterized_function_call(
	        mCc_ast_new_identifier("my_func"), param_1);

	test_print_ast_function_call(function_call, "function_call_concated");
}

/*===========================================================================
 * program tests*/

TEST(AstPrintProgram, PrintProgramFunctionSimple)
{

	struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(
	        MCC_AST_FUNCTION_RETURN_TYPE_BOOL, "my_bool_function",
	        mCc_test_build_test_lit_expression_bool(true));

	struct mCc_ast_program *program = mCc_ast_new_program(function_def);

	test_print_ast_program(program, "program_simple");
}

TEST(AstPrintProgram, PrintProgramFunctionConcated)
{
	struct mCc_ast_function_def *function_def_1 =
	    mCc_test_build_test_function_def(
	        MCC_AST_FUNCTION_RETURN_TYPE_BOOL, "my_bool_function",
	        mCc_test_build_test_lit_expression_bool(true));

	struct mCc_ast_function_def *function_def_2 =
	    mCc_test_build_test_function_def(MCC_AST_FUNCTION_RETURN_TYPE_VOID,
	                                     "my_void_function", NULL);

	struct mCc_ast_function_def *function_def_3 =
	    mCc_test_build_test_function_def(
	        MCC_AST_FUNCTION_RETURN_TYPE_INT, "my_int_function",
	        mCc_test_build_test_lit_expression(10));

	// concat
	function_def_2->next_function_def = function_def_3;
	function_def_1->next_function_def = function_def_2;

	struct mCc_ast_program *program = mCc_ast_new_program(function_def_1);

	test_print_ast_program(program, "program_concated");
}
