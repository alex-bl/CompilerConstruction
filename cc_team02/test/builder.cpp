#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "mCc/ast.h"
#include "mCc_test/mCc_test_utils.h"

/*=========================================================== literal*/
TEST(AstBuildLiteral, CreateLiteralInt)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_int(12);

	ASSERT_EQ(lit->type, MCC_AST_DATA_TYPE_INT);
	ASSERT_EQ(lit->i_value, 12);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuildLiteral, CreateLiteralFloat)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_float(1.2);

	ASSERT_EQ(lit->type, MCC_AST_DATA_TYPE_FLOAT);
	ASSERT_EQ(lit->f_value, 1.2);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuildLiteral, CreateLiteralBool)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_bool(true);

	ASSERT_EQ(lit->type, MCC_AST_DATA_TYPE_BOOL);
	ASSERT_EQ(lit->b_value, true);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuildLiteral, CreateLiteralString)
{
	mCc_ast_literal *lit = mCc_test_build_test_lit_string("test");

	ASSERT_EQ(lit->type, MCC_AST_DATA_TYPE_STRING);
	ASSERT_STREQ(lit->s_value, "test");

	mCc_ast_delete_literal(lit);
}

/*=========================================================== Expression*/

TEST(AstBuildExpression, CreateExpressionLiteral)
{
	mCc_ast_literal *lit = mCc_test_build_test_lit_string("test");
	mCc_ast_expression *exp = mCc_ast_new_expression_literal(lit);

	ASSERT_EQ(exp->type, MCC_AST_EXPRESSION_TYPE_LITERAL);
	ASSERT_STREQ(exp->literal->s_value, "test");

	mCc_ast_delete_expression(exp);
}

TEST(AstBuildExpression, CreateExpressionBinaryOp)
{
	mCc_ast_literal *lit_left = mCc_ast_new_literal_int(2);
	mCc_ast_literal *lit_right = mCc_ast_new_literal_int(4);

	mCc_ast_expression *left_side = mCc_ast_new_expression_literal(lit_left);
	mCc_ast_expression *right_side = mCc_ast_new_expression_literal(lit_right);

	mCc_ast_expression *exp = mCc_ast_new_expression_binary_op(MCC_AST_BINARY_OP_ADD, left_side, right_side);

	ASSERT_EQ(exp->type, MCC_AST_EXPRESSION_TYPE_BINARY_OP);
	ASSERT_EQ(exp->lhs->literal->i_value, 2);
	ASSERT_EQ(exp->rhs->literal->i_value, 4);

	mCc_ast_delete_expression(exp);
}

TEST(AstBuildExpression, CreateExpressionUnaryOp)
{
	mCc_ast_literal *lit_right = mCc_ast_new_literal_bool(false);

	mCc_ast_expression *right_side = mCc_ast_new_expression_literal(lit_right);

	mCc_ast_expression *exp = mCc_ast_new_expression_unary_op(MCC_AST_UNARY_OP_NEGATION, right_side);

	ASSERT_EQ(exp->type, MCC_AST_EXPRESSION_TYPE_UNARY_OP);
	ASSERT_EQ(exp->unary_rhs->literal->b_value, false);

	mCc_ast_delete_expression(exp);
}

TEST(AstBuildExpression, CreateExpressionParent)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_float(2.1);
	mCc_ast_expression *exp = mCc_ast_new_expression_literal(lit);
	mCc_ast_expression *parenth = mCc_ast_new_expression_parenth(exp);

	ASSERT_EQ(parenth->type, MCC_AST_EXPRESSION_TYPE_PARENTH);
	ASSERT_EQ(parenth->expression->literal->f_value, 2.1);

	mCc_ast_delete_expression(parenth);
}

TEST(AstBuildExpression, CreateExpressionIdentifier)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_var");
	struct mCc_ast_expression *expression_identifier = mCc_ast_new_expression_identifier(identifier);

	ASSERT_EQ(expression_identifier->type, MCC_AST_EXPRESSION_TYPE_IDENTIFIER);
	ASSERT_STREQ(expression_identifier->identifier->identifier_name, "my_var");

	mCc_ast_delete_expression(expression_identifier);
}

TEST(AstBuildExpression, CreateExpressionArrayIdentifier)
{
	struct mCc_ast_identifier *identifier_arr = mCc_test_build_const_test_identifier("my_var_arr");
	mCc_ast_literal *lit_index = mCc_ast_new_literal_int(2);
	mCc_ast_expression *expression_arr_index = mCc_ast_new_expression_literal(lit_index);

	struct mCc_ast_expression *expression_array_identifier = mCc_ast_new_expression_array_identifier(identifier_arr, expression_arr_index);

	ASSERT_EQ(expression_array_identifier->type, MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY);
	ASSERT_STREQ(expression_array_identifier->array_identifier->identifier_name, "my_var_arr");
	ASSERT_EQ(expression_array_identifier->array_index_expression->literal->i_value, 2);

	mCc_ast_delete_expression(expression_array_identifier);
}

TEST(AstBuildExpression, CreateExpressionFunctionCall)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_func");
	struct mCc_ast_literal *lit = mCc_ast_new_literal_int(2);
	struct mCc_ast_expression *param = mCc_ast_new_expression_literal(lit);

	struct mCc_ast_function_call *function_call = mCc_ast_new_parameterized_function_call(identifier, param);

	ASSERT_STREQ(function_call->identifier->identifier_name, "my_func");
	ASSERT_EQ(function_call->first_argument->literal->i_value, 2);

	mCc_ast_delete_function_call(function_call);
}

/*=========================================================== Assignment*/

TEST(AstBuildAssignment, CreateAssignmentPrimitive)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident");
	struct mCc_ast_literal *lit = mCc_ast_new_literal_int(14);
	struct mCc_ast_expression *assigned_expresion_value = mCc_ast_new_expression_literal(lit);

	struct mCc_ast_assignment *primitive_assignment = mCc_ast_new_primitive_assignment(identifier, assigned_expresion_value);

	ASSERT_EQ(primitive_assignment->assignment_type, MCC_AST_ASSIGNMENT_PRIMITIVE);
	ASSERT_STREQ(primitive_assignment->identifier->identifier_name, "my_ident");
	ASSERT_EQ(primitive_assignment->assigned_expression->literal->i_value, 14);

	mCc_ast_delete_assignment(primitive_assignment);
}

TEST(AstBuildAssignment, CreateAssignmentArray)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident");
	struct mCc_ast_literal *index = mCc_ast_new_literal_int(15);
	struct mCc_ast_expression *assigned_expresion_index = mCc_ast_new_expression_literal(index);
	struct mCc_ast_literal *value = mCc_test_build_test_lit_string("value");
	struct mCc_ast_expression *assigned_expresion_value = mCc_ast_new_expression_literal(value);

	struct mCc_ast_assignment *primitive_assignment = mCc_ast_new_array_assignment(identifier, assigned_expresion_index,
	                                 assigned_expresion_value);

	ASSERT_EQ(primitive_assignment->assignment_type, MCC_AST_ASSIGNMENT_ARRAY);
	ASSERT_STREQ(primitive_assignment->identifier->identifier_name, "my_ident");
	ASSERT_EQ(primitive_assignment->array_index_expression->literal->i_value, 15);
	ASSERT_STREQ(primitive_assignment->array_assigned_expression->literal->s_value, "value");

	mCc_ast_delete_assignment(primitive_assignment);
}

/*=========================================================== Declaration*/

TEST(AstBuildDeclaration, CreateDeclarationPrimitive)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident_1");
	enum mCc_ast_data_type data_type = MCC_AST_DATA_TYPE_INT;

	struct mCc_ast_declaration *primitive_declaration = mCc_ast_new_primitive_declaration(data_type, identifier);

	ASSERT_EQ(primitive_declaration->declaration_type, MCC_AST_DECLARATION_PRIMITIVE);
	ASSERT_EQ(primitive_declaration->data_type, MCC_AST_DATA_TYPE_INT);
	ASSERT_STREQ(primitive_declaration->identifier->identifier_name, "my_ident_1");

	mCc_ast_delete_declaration(primitive_declaration);
}

TEST(AstBuildDeclaration, CreateDeclarationArray)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident_2");
	enum mCc_ast_data_type data_type = MCC_AST_DATA_TYPE_STRING;
	size_t size = 13;

	struct mCc_ast_declaration *primitive_declaration = mCc_ast_new_array_declaration(data_type, identifier, size);

	ASSERT_EQ(primitive_declaration->declaration_type, MCC_AST_DECLARATION_ARRAY);
	ASSERT_EQ(primitive_declaration->data_type, MCC_AST_DATA_TYPE_STRING);
	ASSERT_STREQ(primitive_declaration->identifier->identifier_name, "my_ident_2");
	ASSERT_EQ(primitive_declaration->size, size);

	mCc_ast_delete_declaration(primitive_declaration);
}

/*=========================================================== Function*/

TEST(AstBuildFunction, CreateFunctionDefNonParameterized)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident_3");
	enum mCc_ast_data_type return_type = MCC_AST_DATA_TYPE_VOID;

	// Building if/else statement:
	struct mCc_ast_literal *literal = mCc_ast_new_literal_bool(1);
	struct mCc_ast_expression *condition_expr = mCc_ast_new_expression_literal(literal);

	struct mCc_ast_identifier *identifier_else = mCc_test_build_const_test_identifier("my_ident_4");
	enum mCc_ast_data_type data_type = MCC_AST_DATA_TYPE_INT;
	struct mCc_ast_declaration *primitive_declaration = mCc_ast_new_primitive_declaration(data_type, identifier_else);
	struct mCc_ast_statement *if_stmt = mCc_ast_new_declaration_statement(primitive_declaration);

	mCc_ast_literal *lit = mCc_test_build_test_lit_string("test");
	mCc_ast_expression *exp = mCc_ast_new_expression_literal(lit);
	struct mCc_ast_statement *else_stmt = mCc_ast_new_expression_statement(exp);

	struct mCc_ast_statement *stmts = mCc_ast_new_if_statement(condition_expr, if_stmt, else_stmt);

	// Building Function
	struct mCc_ast_function_def *function = mCc_ast_new_non_parameterized_function_def(identifier, return_type, stmts);

	ASSERT_STREQ(function->identifier->identifier_name, "my_ident_3");
	ASSERT_EQ(function->return_type, MCC_AST_DATA_TYPE_VOID);
	ASSERT_EQ(function->first_statement->if_statement->declaration->declaration_type, MCC_AST_DECLARATION_PRIMITIVE);
	ASSERT_EQ(function->first_statement->if_statement->declaration->data_type, MCC_AST_DATA_TYPE_INT);
	ASSERT_STREQ(function->first_statement->if_statement->declaration->identifier->identifier_name, "my_ident_4");
	ASSERT_STREQ(function->first_statement->else_statement->expression->literal->s_value, "test");
	ASSERT_EQ(function->first_statement->condition_expression->literal->b_value, 1);

	mCc_ast_delete_function_def(function);
}

TEST(AstBuildFunction, CreateFunctionDefParameterized)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident_7");
	enum mCc_ast_data_type return_type = MCC_AST_DATA_TYPE_BOOL;

	// Building if/else statement:
	struct mCc_ast_literal *literal = mCc_ast_new_literal_bool(1);
	struct mCc_ast_expression *condition_expr = mCc_ast_new_expression_literal(literal);

	struct mCc_ast_identifier *identifier_else = mCc_test_build_const_test_identifier("my_ident_6");
	enum mCc_ast_data_type data_type = MCC_AST_DATA_TYPE_INT;
	struct mCc_ast_declaration *primitive_declaration = mCc_ast_new_primitive_declaration(data_type, identifier_else);
	struct mCc_ast_statement *if_stmt = mCc_ast_new_declaration_statement(primitive_declaration);

	mCc_ast_literal *lit = mCc_test_build_test_lit_string("test");
	mCc_ast_expression *exp = mCc_ast_new_expression_literal(lit);
	struct mCc_ast_statement *else_stmt = mCc_ast_new_expression_statement(exp);

	struct mCc_ast_statement *stmts = mCc_ast_new_if_statement(condition_expr, if_stmt, else_stmt);

	// Building Paramaters:
	enum mCc_ast_data_type data_type_param = MCC_AST_DATA_TYPE_FLOAT;
	struct mCc_ast_identifier *identifier_param = mCc_test_build_const_test_identifier("my_ident_5");
	struct mCc_ast_declaration *params = mCc_ast_new_primitive_declaration(data_type_param, identifier_param);

	// Building Function
	struct mCc_ast_function_def *function = mCc_ast_new_parameterized_function_def(identifier, return_type, params, stmts);

	ASSERT_STREQ(function->identifier->identifier_name, "my_ident_7");
	ASSERT_EQ(function->return_type, MCC_AST_DATA_TYPE_BOOL);
	ASSERT_EQ(function->first_statement->if_statement->declaration->declaration_type, MCC_AST_DECLARATION_PRIMITIVE);
	ASSERT_EQ(function->first_statement->if_statement->declaration->data_type, MCC_AST_DATA_TYPE_INT);
	ASSERT_STREQ(function->first_statement->if_statement->declaration->identifier->identifier_name, "my_ident_6");
	ASSERT_STREQ(function->first_statement->else_statement->expression->literal->s_value, "test");
	ASSERT_EQ(function->first_parameter->data_type, MCC_AST_DATA_TYPE_FLOAT);
	ASSERT_EQ(function->first_parameter->declaration_type, MCC_AST_DECLARATION_PRIMITIVE);
	ASSERT_STREQ(function->first_parameter->identifier->identifier_name, "my_ident_5");
	ASSERT_EQ(function->first_statement->condition_expression->literal->b_value, 1);

	mCc_ast_delete_function_def(function);
}

// Function Calls:

TEST(AstBuildFunction, CreateFunctionCallNonParameterized)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident_7");

	// Building Function
	struct mCc_ast_function_call *function = mCc_ast_new_non_parameterized_function_call(identifier);

	ASSERT_STREQ(function->identifier->identifier_name, "my_ident_7");

	mCc_ast_delete_function_call(function);
}

TEST(AstBuildFunction, CreateFunctionCallParameterized)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident_3");

	// Building Paramaters:
	struct mCc_ast_literal *literal_exp = mCc_ast_new_literal_float(2.3);
	struct mCc_ast_expression *args = mCc_ast_new_expression_literal(literal_exp);

	// Building Function
	struct mCc_ast_function_call *function = mCc_ast_new_parameterized_function_call(identifier, args);

	ASSERT_STREQ(function->identifier->identifier_name, "my_ident_3");
	ASSERT_EQ(function->first_argument->literal->f_value, 2.3);
	ASSERT_EQ(function->first_argument->literal->type, MCC_AST_DATA_TYPE_FLOAT);

	mCc_ast_delete_function_call(function);
}

/*=========================================================== Identifier*/

TEST(AstBuildIdentifier, CreateIdentifier)
{
	const char *name = "identifier_name";

	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier(name);

	ASSERT_STREQ(identifier->identifier_name, "identifier_name");

	mCc_ast_delete_identifier(identifier);
}

/*=========================================================== Program*/

TEST(AstBuildProgram, CreateProgram)
{
	struct mCc_ast_identifier *identifier_function = mCc_test_build_const_test_identifier("my_ident_8");
	enum mCc_ast_data_type return_type_function = MCC_AST_DATA_TYPE_FLOAT;

	struct mCc_ast_identifier *identifier_assignment = mCc_test_build_const_test_identifier("my_ident_9");

	enum mCc_ast_unary_op op = MCC_AST_UNARY_OP_MINUS;
	struct mCc_ast_literal *bool_literal = mCc_ast_new_literal_bool(1);
	struct mCc_ast_expression *expression = mCc_ast_new_expression_literal(bool_literal);
	struct mCc_ast_expression *assigned_expresion_value = mCc_ast_new_expression_unary_op(op, expression);

	struct mCc_ast_assignment *assignment_function = mCc_ast_new_primitive_assignment(identifier_assignment, assigned_expresion_value);

	struct mCc_ast_statement *stmts = mCc_ast_new_assign_statement(assignment_function);

	// Building Function
	struct mCc_ast_function_def *function_defs = mCc_ast_new_non_parameterized_function_def(identifier_function,
	                                               return_type_function, stmts);

	struct mCc_ast_program *program = mCc_ast_new_program(function_defs);

	ASSERT_STREQ(program->first_function_def->identifier->identifier_name, "my_ident_8");
	ASSERT_EQ(program->first_function_def->return_type, MCC_AST_DATA_TYPE_FLOAT);
	ASSERT_EQ(program->first_function_def->first_statement->assignment->assignment_type, MCC_AST_ASSIGNMENT_PRIMITIVE);
	ASSERT_STREQ(program->first_function_def->first_statement->assignment->identifier->identifier_name, "my_ident_9");
	ASSERT_EQ(program->first_function_def->first_statement->assignment->assigned_expression->type, MCC_AST_EXPRESSION_TYPE_UNARY_OP);
	ASSERT_EQ(program->first_function_def->first_statement->assignment->assigned_expression->unary_op, MCC_AST_UNARY_OP_MINUS);
	ASSERT_EQ(program->first_function_def->first_statement->assignment->assigned_expression->unary_rhs->type, MCC_AST_EXPRESSION_TYPE_LITERAL);
	ASSERT_EQ(program->first_function_def->first_statement->assignment->assigned_expression->unary_rhs->literal->type, MCC_AST_DATA_TYPE_BOOL);
	ASSERT_EQ(program->first_function_def->first_statement->assignment->assigned_expression->unary_rhs->literal->b_value, 1);

	mCc_ast_delete_program(program);
}

/*=========================================================== Statement*/

TEST(AstBuildStatement, CreateStatementIf)
{
	// Building Expression
	struct mCc_ast_identifier *identifier_expression = mCc_test_build_const_test_identifier("my_ident_9");
	struct mCc_ast_expression *condition_expr = mCc_ast_new_expression_identifier(identifier_expression);

	// Builiding if Statement
	struct mCc_ast_identifier *identifier_assignment = mCc_test_build_const_test_identifier("my_ident_10");
	struct mCc_ast_literal *index_literal = mCc_ast_new_literal_float(4.7);
	struct mCc_ast_expression *index_assignment = mCc_ast_new_expression_literal(index_literal);
	struct mCc_ast_identifier *identifier_assignment_value = mCc_test_build_const_test_identifier("my_ident_11");
	struct mCc_ast_expression *value_assignment = mCc_ast_new_expression_identifier(identifier_assignment_value);
	struct mCc_ast_assignment *assignment_if = mCc_ast_new_array_assignment(identifier_assignment, index_assignment, value_assignment);
	struct mCc_ast_statement *if_stmt = mCc_ast_new_assign_statement(assignment_if);

	// Building else statement
	struct mCc_ast_identifier *identifier_return = mCc_test_build_const_test_identifier("my_ident_12");
	struct mCc_ast_expression *return_expression = mCc_ast_new_expression_identifier(identifier_return);
	struct mCc_ast_statement *else_stmt = mCc_ast_new_return_statement(return_expression);

	struct mCc_ast_statement *statement = mCc_ast_new_if_statement(condition_expr, if_stmt, else_stmt);

	ASSERT_EQ(statement->condition_expression->type, MCC_AST_EXPRESSION_TYPE_IDENTIFIER);
	ASSERT_STREQ(statement->condition_expression->identifier->identifier_name, "my_ident_9");

	ASSERT_EQ(statement->if_statement->statement_type, MCC_AST_STATEMENT_ASSIGNMENT);
	ASSERT_STREQ(statement->if_statement->assignment->identifier->identifier_name, "my_ident_10");
	ASSERT_EQ(statement->if_statement->assignment->assignment_type, MCC_AST_ASSIGNMENT_ARRAY);
	ASSERT_EQ(statement->if_statement->assignment->array_index_expression->literal->f_value, 4.7);
	ASSERT_STREQ(statement->if_statement->assignment->array_assigned_expression->identifier->identifier_name, "my_ident_11");

	ASSERT_EQ(statement->else_statement->statement_type, MCC_AST_STATEMENT_RETURN);
	ASSERT_EQ(statement->else_statement->return_expression->type, MCC_AST_EXPRESSION_TYPE_IDENTIFIER);
	ASSERT_EQ(statement->else_statement->statement_type, MCC_AST_STATEMENT_RETURN);
	ASSERT_STREQ(statement->else_statement->return_expression->identifier->identifier_name, "my_ident_12");

	mCc_ast_delete_statement(statement);
}

TEST(AstBuildStatement, CreateStatementWhile)
{
	struct mCc_ast_identifier *identifier_loop = mCc_test_build_const_test_identifier("my_ident_13");
	struct mCc_ast_expression *loop_expression = mCc_ast_new_expression_identifier(identifier_loop);
	struct mCc_ast_expression *loop_expr = loop_expression;

	enum mCc_ast_data_type data_type = MCC_AST_DATA_TYPE_STRING;
	struct mCc_ast_identifier *identifier_declaration = mCc_test_build_const_test_identifier("my_ident_14");
	struct mCc_ast_declaration *declaration = mCc_ast_new_primitive_declaration(data_type, identifier_declaration);
	struct mCc_ast_statement *while_stmt = mCc_ast_new_declaration_statement(declaration);

	struct mCc_ast_statement *statement = mCc_ast_new_while_statement(loop_expr, while_stmt);

	ASSERT_EQ(statement->while_statement->declaration->data_type, MCC_AST_DATA_TYPE_STRING);
	ASSERT_STREQ(statement->while_statement->declaration->identifier->identifier_name, "my_ident_14");
	ASSERT_EQ(statement->loop_condition_expression->type, MCC_AST_EXPRESSION_TYPE_IDENTIFIER);
	ASSERT_STREQ(statement->loop_condition_expression->identifier->identifier_name, "my_ident_13");

	mCc_ast_delete_statement(statement);
}

TEST(AstBuildStatement, CreateStatementReturn)
{
	struct mCc_ast_identifier *identifier_return = mCc_test_build_const_test_identifier("my_ident_15");
	struct mCc_ast_expression *return_expression = mCc_ast_new_expression_identifier(identifier_return);

	struct mCc_ast_statement *statement = mCc_ast_new_return_statement(return_expression);

	ASSERT_EQ(statement->return_expression->type, MCC_AST_EXPRESSION_TYPE_IDENTIFIER);
	ASSERT_STREQ(statement->return_expression->identifier->identifier_name, "my_ident_15");

	mCc_ast_delete_statement(statement);
}

TEST(AstBuildStatement, CreateStatementExpression)
{
	struct mCc_ast_literal *literal = mCc_ast_new_literal_int(577);
	struct mCc_ast_expression *expression = mCc_ast_new_expression_literal(literal);

	struct mCc_ast_statement *statement = mCc_ast_new_expression_statement(expression);

	ASSERT_EQ(statement->expression->type, MCC_AST_EXPRESSION_TYPE_LITERAL);
	ASSERT_EQ(statement->expression->literal->i_value, 577);

	mCc_ast_delete_statement(statement);
}

TEST(AstBuildStatement, CreateStatementDeclaration)
{
	enum mCc_ast_data_type data_type = MCC_AST_DATA_TYPE_BOOL;
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident_16");
	struct mCc_ast_declaration *declaration = mCc_ast_new_primitive_declaration(data_type, identifier);

	struct mCc_ast_statement *statement = mCc_ast_new_declaration_statement(declaration);

	ASSERT_EQ(statement->declaration->data_type, MCC_AST_DATA_TYPE_BOOL);
	ASSERT_EQ(statement->declaration->declaration_type, MCC_AST_DECLARATION_PRIMITIVE);
	ASSERT_STREQ(statement->declaration->identifier->identifier_name, "my_ident_16");

	mCc_ast_delete_statement(statement);
}

TEST(AstBuildStatement, CreateStatementAssignment)
{
	struct mCc_ast_identifier *identifier = mCc_test_build_const_test_identifier("my_ident_17");
	struct mCc_ast_literal *literal = mCc_ast_new_literal_float(55.23);
	struct mCc_ast_expression *assigned_expresion_value = mCc_ast_new_expression_literal(literal);
	struct mCc_ast_assignment *assignment = mCc_ast_new_primitive_assignment(identifier, assigned_expresion_value);

	struct mCc_ast_statement *statement = mCc_ast_new_assign_statement(assignment);

	ASSERT_STREQ(statement->assignment->identifier->identifier_name, "my_ident_17");
	ASSERT_EQ(statement->assignment->assigned_expression->type, MCC_AST_EXPRESSION_TYPE_LITERAL);
	ASSERT_EQ(statement->assignment->assigned_expression->literal->type, MCC_AST_DATA_TYPE_FLOAT);
	ASSERT_EQ(statement->assignment->assigned_expression->literal->f_value, 55.23);

	mCc_ast_delete_statement(statement);
}
