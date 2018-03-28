#include "gtest/gtest.h"
#include <iostream>

#include "mCc/ast.h"
#include "mCc/parser.h"

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
	ASSERT_EQ(MCC_AST_LITERAL_TYPE_INT, expr->lhs->literal->type);
	ASSERT_EQ(192, expr->lhs->literal->i_value);

	// root -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, expr->rhs->type);

	// root -> rhs -> literal
	ASSERT_EQ(MCC_AST_LITERAL_TYPE_FLOAT, expr->rhs->literal->type);
	ASSERT_EQ(3.14, expr->rhs->literal->f_value);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_2){
	const char input[] = "192 > 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_GREATER_THAN, expr->op);

	mCc_ast_delete_expression(expr);

}

TEST(Parser, BinaryOp_3){
	const char input[] = "192 < 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_LESS_THAN, expr->op);

	mCc_ast_delete_expression(expr);

}

TEST(Parser, BinaryOp_4){
	const char input[] = "192 >= 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN, expr->op);

	mCc_ast_delete_expression(expr);

}

TEST(Parser, BinaryOp_5){
	const char input[] = "192 <= 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_6){
	const char input[] = "192 && 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_AND, expr->op);

	mCc_ast_delete_expression(expr);
}


TEST(Parser, BinaryOp_7){
	const char input[] = "192 || 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_OR, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_8){
	const char input[] = "192 == 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_EQUALS, expr->op);

	mCc_ast_delete_expression(expr);
}


TEST(Parser, BinaryOp_9){
	const char input[] = "192 != 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_NOT_EQUALS, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_10){
	const char input[] = "192 - 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_SUB, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_11){
	const char input[] = "192 * 3.14";
	auto result = mCc_parser_parse_string(input);


	ASSERT_EQ(MCC_PARSER_STATUS_OK, result.status);

	auto expr = result.expression;

	// root
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, expr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_MUL, expr->op);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, BinaryOp_12){
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
	ASSERT_EQ(MCC_AST_LITERAL_TYPE_INT, expr->lhs->literal->type);
	ASSERT_EQ(42, expr->lhs->literal->i_value);

	// root -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_PARENTH, expr->rhs->type);

	auto subexpr = expr->rhs->expression;

	// subexpr
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_BINARY_OP, subexpr->type);
	ASSERT_EQ(MCC_AST_BINARY_OP_ADD, subexpr->op);

	// subexpr -> lhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, subexpr->lhs->type);

	// subexpr -> lhs -> literal
	ASSERT_EQ(MCC_AST_LITERAL_TYPE_INT, subexpr->lhs->literal->type);
	ASSERT_EQ(-192, subexpr->lhs->literal->i_value);

	// subexpr -> rhs
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL, subexpr->rhs->type);

	// subexpr -> rhs -> literal
	ASSERT_EQ(MCC_AST_LITERAL_TYPE_FLOAT, subexpr->rhs->literal->type);
	ASSERT_EQ(3.14, subexpr->rhs->literal->f_value);

	mCc_ast_delete_expression(expr);
}

TEST(Parser, MissingClosingParenthesis_1)
{
	const char input[] = "(42";
	auto result = mCc_parser_parse_string(input);

	ASSERT_NE(MCC_PARSER_STATUS_OK, result.status);
}

TEST(Parser, Assignment_1)
{
	const char input[] = "a = 4";
	auto result = mCc_parser_parse_string(input);

	auto assignment = result.assignment;

	ASSERT_EQ(4, assignment->assigned_expression->literal->i_value);
	ASSERT_STREQ("a", assignment->identifier->identifier_name);
	
	mCc_ast_delete_assignment(assignment);
}

TEST(Parser, IfStatement_1)
{

	const char input[] = " if(5){}";
	auto result = mCc_parser_parse_string(input);

	auto if_statement = result.statement;

	ASSERT_EQ(MCC_AST_LITERAL_TYPE_INT, if_statement->condition_expression->literal->type);
	ASSERT_EQ(MCC_AST_STATEMENT_IF, if_statement->statement_type);
	//mCc_ast_delete_statement(if_statement);
}

TEST(Parser, IfStatement_2)
{

	const char input[] = " if(5){int a;}else{int s;}";
	auto result = mCc_parser_parse_string(input);

	auto statement = result.statement;

	ASSERT_STREQ("s", statement->else_statement->declaration->identifier->identifier_name);
	
	mCc_ast_delete_statement(statement);
}

TEST(Parser, WhileStatement_1){
	const char input[] = "while(5){int a;}";
	auto result = mCc_parser_parse_string(input);

	auto statement = result.statement;
	ASSERT_EQ(MCC_AST_STATEMENT_WHILE, statement->statement_type);

	mCc_ast_delete_statement(statement);
}

TEST(Parser, ReturnStatement_1){
	const char input[] = "return;";
	auto result = mCc_parser_parse_string(input);
	auto statement = result.statement;
	ASSERT_EQ(MCC_AST_STATEMENT_RETURN, statement->statement_type);
	mCc_ast_delete_statement(statement);
}

TEST(Parser, ReturnStatement_2){
	const char input[] = "return 5;";
	auto result = mCc_parser_parse_string(input);
	auto statement = result.statement;
	ASSERT_EQ(MCC_AST_STATEMENT_RETURN, statement->statement_type);
	ASSERT_EQ(5, statement->return_expression->literal->i_value);
	mCc_ast_delete_statement(statement);
}


TEST(Parser, Declaration_1){
	const char input[] = "int a";
	
	auto result = mCc_parser_parse_string(input);
	auto declaration = result.declaration;

	ASSERT_EQ(MCC_AST_DECLARATION_PRIMITIVE, declaration->declaration_type);
	ASSERT_STREQ("a", declaration->identifier->identifier_name);
//	mCc_ast_delete_program(program);
}


