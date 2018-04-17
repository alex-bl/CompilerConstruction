#include "mCc/parser.h"
#include "mCc/ast.h"
#include "mCc_test/mCc_test_utils.h"
#include "gtest/gtest.h"

TEST(Parser, BinaryOp_1)
{
	const char input[] = "192 + 3.14";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_ADD, expr->op);

	// root -> lhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, expr->lhs->type);

	// root -> lhs -> literal
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, expr->lhs->literal->type);
	ASSERT_EQ(192, expr->lhs->literal->i_value);

	// root -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, expr->rhs->type);

	// root -> rhs -> literal
	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT, expr->rhs->literal->type);
	ASSERT_EQ(3.14, expr->rhs->literal->f_value);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_2)
{
	const char input[] = "192 > 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_GREATER_THAN, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_3)
{
	const char input[] = "192 < 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_LESS_THAN, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_4)
{
	const char input[] = "192 >= 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_5)
{
	const char input[] = "192 <= 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_6)
{
	const char input[] = "192 && 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_AND, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_7)
{
	const char input[] = "192 || 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_OR, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_8)
{
	const char input[] = "192 == 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_EQUALS, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_9)
{
	const char input[] = "192 != 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_NOT_EQUALS, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_10)
{
	const char input[] = "192 - 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_SUB, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_11)
{
	const char input[] = "192 * 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_MUL, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_12)
{
	const char input[] = "192 / 3.14";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_DIV, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, NestedExpression_1)
{
	const char input[] = "42 * (-192 + 3.14)";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_MUL, expr->op);

	// root -> lhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, expr->lhs->type);

	// root -> lhs -> literal
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, expr->lhs->literal->type);
	ASSERT_EQ(42, expr->lhs->literal->i_value);

	// root -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_PARENTH, expr->rhs->type);

	auto subexpr = expr->rhs->expression;

	// subexpr
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, subexpr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_ADD, subexpr->op);

	// subexpr -> lhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_UNARY_OP, subexpr->lhs->type);

	// subexpr -> lhs -> literal

	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, subexpr->lhs->unary_rhs->type);
	ASSERT_EQ(MCC_AST_UNARY_OP_MINUS, subexpr->lhs->unary_op);

	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, subexpr->lhs->unary_rhs->literal->type);
	ASSERT_EQ(192, subexpr->lhs->unary_rhs->literal->i_value);

	// subexpr -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, subexpr->rhs->type);

	// subexpr -> rhs -> literal
	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT, subexpr->rhs->literal->type);
	ASSERT_EQ(3.14, subexpr->rhs->literal->f_value);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, UnaryExpression_1)
{
	const char input[] = "-5";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expression = result.expression;

	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_UNARY_OP, expression->type);
	ASSERT_EQ(MCC_AST_UNARY_OP_MINUS, expression->unary_op);
	ASSERT_EQ(5, expression->unary_rhs->literal->i_value);
	mCc_ast_delete_expression(expression);
}

TEST(Parser, UnaryExpression_2)
{
	const char input[] = "-5 + 6";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expression = result.expression;

	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expression->type);
	mCc_ast_delete_expression(expression);
}

TEST(Parser, UnaryExpression_3)
{

	const char input[] = "!true";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expression = result.expression;

	ASSERT_EQ(MCC_AST_UNARY_OP_NEGATION, expression->unary_op);
	mCc_ast_delete_expression(expression);
}

TEST(Parser, MissingClosingParenthesis_1)
{
	const char input[] = "(42";
	auto result = mCc_parser_parse_string(input);
	ASSERT_NE(MCC_PARSER_STATUS_OK, result.status);
}

TEST(Parser, Assignment_1)
{
	const char input[] = "a = 4;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto statement = result.statement;

	ASSERT_EQ(4, statement->assignment->assigned_expression->literal->i_value);
	ASSERT_STREQ("a", statement->assignment->identifier->identifier_name);
	ASSERT_EQ(MCC_AST_ASSIGNMENT_PRIMITIVE,
	          statement->assignment->assignment_type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, Assignment_2)
{
	const char input[] = "a = \"london\";";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_ASSIGNMENT_PRIMITIVE,
	          statement->assignment->assignment_type);
	ASSERT_STREQ("a", statement->assignment->identifier->identifier_name);
	ASSERT_STREQ("london",
	             statement->assignment->assigned_expression->literal->s_value);

	mCc_ast_delete_statement(statement);
}

TEST(Parser, Assignment_3)
{
	const char input[] = "a[3] = 4;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_ASSIGNMENT_ARRAY, statement->assignment->assignment_type);
	ASSERT_EQ(3,
	          statement->assignment->array_index_expression->literal->i_value);
	ASSERT_EQ(
	    4, statement->assignment->array_assigned_expression->literal->i_value);
	ASSERT_STREQ("a", statement->assignment->identifier->identifier_name);

	mCc_ast_delete_statement(statement);
}

TEST(Parser, IfStatement_1)
{

	const char input[] = " if(5){}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto if_statement = result.statement;

	ASSERT_EQ(MCC_AST_STATEMENT_IF, if_statement->statement_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT,
	          if_statement->condition_expression->literal->type);
	mCc_ast_delete_statement(if_statement);
}

TEST(Parser, IfStatement_2)
{
	const char input[] = " if(5){int a;}else{int s;}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_STREQ(
	    "s",
	    statement->else_statement->declaration->identifier->identifier_name);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, IfStatement_3)
{
	const char input[] = " if(5){if(true){}else{float a;}}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT,
	          statement->if_statement->else_statement->declaration->data_type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, IfStatement_4)
{
	const char input[] = "if (isLeapYear(n)){print(\" is a leap "
	                     "year.\");}else{print(\" is not a leap year.\");}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_STREQ(" is a leap year.",
	             statement->if_statement->expression->function_call
	                 ->first_argument->literal->s_value);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, WhileStatement_1)
{
	const char input[] = "while(5){}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;
	ASSERT_EQ(MCC_AST_STATEMENT_WHILE, statement->statement_type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, ReturnStatement_1)
{
	const char input[] = "return;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_STATEMENT_RETURN, statement->statement_type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, ReturnStatement_2)
{
	const char input[] = "return 5;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_STATEMENT_RETURN, statement->statement_type);
	ASSERT_EQ(5, statement->return_expression->literal->i_value);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, NestedStatement_1)
{
	const char input[] = "while(5){if(5){return 5;}}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_STATEMENT_RETURN,
	          statement->while_statement->if_statement->statement_type);
	ASSERT_EQ(5, statement->while_statement->if_statement->return_expression
	                 ->literal->i_value);

	mCc_ast_delete_statement(statement);
}

TEST(Parser, Declaration_1)
{
	const char input[] = "int a;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE,
	          statement->declaration->declaration_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, statement->declaration->data_type);
	ASSERT_STREQ("a", statement->declaration->identifier->identifier_name);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, Declaration_2)
{
	const char input[] = "bool a;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE,
	          statement->declaration->declaration_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL, statement->declaration->data_type);
	ASSERT_STREQ("a", statement->declaration->identifier->identifier_name);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, Declaration_3)
{
	const char input[] = "string a;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE,
	          statement->declaration->declaration_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_STRING, statement->declaration->data_type);
	ASSERT_STREQ("a", statement->declaration->identifier->identifier_name);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, Declaration_4)
{
	const char input[] = "float a;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE,
	          statement->declaration->declaration_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT, statement->declaration->data_type);
	ASSERT_STREQ("a", statement->declaration->identifier->identifier_name);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, Literal_1)
{
	const char input[] = "a = 3.4;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DATA_TYPE_FLOAT,
	          statement->assignment->assigned_expression->literal->type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, Literal_2)
{
	const char input[] = "a = \"hallo\";";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DATA_TYPE_STRING,
	          statement->assignment->assigned_expression->literal->type);
	ASSERT_STREQ("hallo",
	             statement->assignment->assigned_expression->literal->s_value);

	mCc_ast_delete_statement(statement);
}

TEST(Parser, Literal_3)
{
	const char input[] = "a = true;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL,
	          statement->assignment->assigned_expression->literal->type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, Literal_4)
{
	const char input[] = "a = 3;";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto statement = result.statement;

	ASSERT_EQ(MCC_AST_DATA_TYPE_INT,
	          statement->assignment->assigned_expression->literal->type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, Function_1)
{
	const char input[] = "int foo(bool a, int b){int bla;}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto program = result.program;

	// test first parameter
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT, program->first_function_def->return_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL,
	          program->first_function_def->first_parameter->data_type);

	// test second parameter
	ASSERT_EQ(MCC_AST_DATA_TYPE_INT,
	          program->first_function_def->first_parameter->next_declaration
	              ->data_type);

	// test statement
	ASSERT_EQ(
	    MCC_AST_DATA_TYPE_INT,
	    program->first_function_def->first_statement->declaration->data_type);
	mCc_ast_delete_program(program);
}

TEST(Parser, CallExpression_1)
{
	const char input[] = "foo()";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto call_expr = result.expression;

	ASSERT_STREQ("foo", call_expr->function_call->identifier->identifier_name);
	mCc_ast_delete_expression(call_expr);
}

TEST(Parser, CallExpression_2)
{
	const char input[] = "foo(-5,5+4, a, true)";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto call_expr = result.expression;

	// test first argument
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_UNARY_OP,
	          call_expr->function_call->first_argument->type);
	ASSERT_EQ(
	    5,
	    call_expr->function_call->first_argument->unary_rhs->literal->i_value);

	// test second argument
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP,
	          call_expr->function_call->first_argument->next_expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_ADD,
	          call_expr->function_call->first_argument->next_expr->op);
	ASSERT_EQ(4, call_expr->function_call->first_argument->next_expr->rhs
	                 ->literal->i_value);

	// test third argument
	ASSERT_STREQ("a", call_expr->function_call->first_argument->next_expr
	                      ->next_expr->identifier->identifier_name);

	// test fourth argument
	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL,
	          call_expr->function_call->first_argument->next_expr->next_expr
	              ->next_expr->literal->type);

	mCc_ast_delete_expression(call_expr);
}

TEST(Parser, CallExpression_3)
{
	const char input[] = "foo(bla())";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto call_expr = result.expression;

	// test first argument
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_CALL_EXPR,
	          call_expr->function_call->first_argument->type);
	ASSERT_STREQ("bla", call_expr->function_call->first_argument->function_call
	                        ->identifier->identifier_name);

	mCc_ast_delete_expression(call_expr);
}

TEST(Parser, CallExpression_4)
{
	const char input[] = "foo(\"string_argument\")";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto call_expr = result.expression;

	// test first argument
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL,
	          call_expr->function_call->first_argument->type);
	ASSERT_STREQ("string_argument",
	             call_expr->function_call->first_argument->literal->s_value);

	mCc_ast_delete_expression(call_expr);
}

TEST(Parser, Program_1)
{
	const char input[] = "int get_num(){} string get_string(){}";
	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	auto program = result.program;

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_EQ(MCC_AST_DATA_TYPE_STRING,
	          program->first_function_def->next_function_def->return_type);
	mCc_ast_delete_program(program);
}

TEST(Parser, SourceLocation_SingleLineColumn)
{
	const char input[] = "(42 + 192)";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	EXPECT_EQ(MCC_AST_EXPRESSION_TYPE_PARENTH, expr->type);
	ASSERT_EQ(1, expr->node.sloc.start_col);

	EXPECT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->expression->type);
	ASSERT_EQ(2, expr->expression->node.sloc.start_col);

	EXPECT_EQ(MCC_AST_DATA_TYPE_INT, expr->expression->lhs->literal->type);
	ASSERT_EQ(2, expr->expression->lhs->literal->node.sloc.start_col);
	ASSERT_EQ(4, expr->expression->lhs->literal->node.sloc.end_col);

	EXPECT_EQ(MCC_AST_DATA_TYPE_INT, expr->expression->rhs->literal->type);
	ASSERT_EQ(7, expr->expression->rhs->literal->node.sloc.start_col);
	ASSERT_EQ(10, expr->expression->rhs->literal->node.sloc.end_col);

	mCc_parser_destroy_parser(result);
}

TEST(Parser, SourceLocation_Row)
{
	const char input[] = "(42\n + \n192)";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	EXPECT_EQ(MCC_AST_EXPRESSION_TYPE_PARENTH, expr->type);
	ASSERT_EQ(1, expr->node.sloc.start_line);
	ASSERT_EQ(3, expr->node.sloc.end_line);

	EXPECT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->expression->type);
	ASSERT_EQ(1, expr->expression->node.sloc.start_line);

	EXPECT_EQ(MCC_AST_DATA_TYPE_INT, expr->expression->lhs->literal->type);
	ASSERT_EQ(1, expr->expression->lhs->literal->node.sloc.start_line);
	ASSERT_EQ(1, expr->expression->lhs->literal->node.sloc.end_line);

	EXPECT_EQ(MCC_AST_DATA_TYPE_INT, expr->expression->rhs->literal->type);
	ASSERT_EQ(3, expr->expression->rhs->literal->node.sloc.start_line);
	ASSERT_EQ(3, expr->expression->rhs->literal->node.sloc.end_line);

	mCc_parser_destroy_parser(result);
}

TEST(Parser, ParserSyntaxError)
{
	const char input[] = "(42\n + \n192";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_SYNTAX_ERROR, result.status);
	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_EXPRESSION, result.top_level_type);

	ASSERT_EQ(0, result.error_location.sloc.start_col);
	ASSERT_EQ(3, result.error_location.sloc.end_col);
	ASSERT_EQ(3, result.error_location.sloc.start_line);
}

TEST(Parser, ParserSyntaxError_2)
{
	const char input[] = "int foo(int bla)){}";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_SYNTAX_ERROR, result.status);
	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_EXPRESSION, result.top_level_type);

	ASSERT_EQ(17, result.error_location.sloc.start_col);
	ASSERT_EQ(18, result.error_location.sloc.end_col);
	ASSERT_EQ(1, result.error_location.sloc.start_line);
}

TEST(Parser, ParserSyntaxError_3)
{
	const char input[] = "5 +* 3";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_SYNTAX_ERROR, result.status);
	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_EXPRESSION, result.top_level_type);

	ASSERT_EQ(4, result.error_location.sloc.start_col);
	ASSERT_EQ(5, result.error_location.sloc.end_col);
	ASSERT_EQ(1, result.error_location.sloc.start_line);
}

TEST(Parser, ParserSyntaxError_4)
{
	const char input[] = "foo((5,4)";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_SYNTAX_ERROR, result.status);
	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_EXPRESSION, result.top_level_type);

	ASSERT_EQ(7, result.error_location.sloc.start_col);
	ASSERT_EQ(8, result.error_location.sloc.end_col);
	ASSERT_EQ(1, result.error_location.sloc.start_line);
}

TEST(Parser, Comments_1)
{
	const char input[] = "//THIS is a comment!\nint foo;";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_STATEMENT, result.top_level_type);

	auto statement = result.statement;

	ASSERT_EQ(2, statement->node.sloc.start_line);

	mCc_parser_destroy_parser(result);
}

TEST(Parser, CommentsMultiline)
{
	const char input[] =
	    "int a;/*This is another comment\n Hello\n World!*/\n bool foo;";
	auto result = mCc_parser_parse_string(input);

	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);
	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_STATEMENT, result.top_level_type);

	auto statement = result.statement;
	ASSERT_EQ(1, statement->node.sloc.start_line);
	ASSERT_EQ(4, statement->next_statement->node.sloc.start_line);

	mCc_parser_destroy_parser(result);
}

TEST(Parser, Program_2)
{
	const char input[] = "void main(){	int a;string b;int d;	"
	                     "c=2;a=notDefined(\"test\");d=call();d=call(1,2,3,4);"
	                     "if(a==12){int c;} else{int d;}}";
	

	auto result = mCc_parser_parse_string(input);
	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	ASSERT_EQ(MCC_AST_DATA_TYPE_VOID,
	          result.program->first_function_def->return_type);
	mCc_ast_delete_program(result.program);
}