#include "gtest/gtest.h"

#include "mCc/ast.h"
#include <stdbool.h>
#include <stddef.h>

/*=========================================================== literal*/
TEST(AstBuildLiteral, CreateLiteralInt)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_int(12);

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_INT);
	ASSERT_EQ(lit->i_value, 12);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuildLiteral, CreateLiteralFloat)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_float(1.2);

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_FLOAT);
	ASSERT_EQ(lit->f_value, 1.2);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuildLiteral, CreateLiteralBool)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_bool(true);

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_BOOL);
	ASSERT_EQ(lit->b_value, true);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuildLiteral, CreateLiteralString)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_string("test");

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_STRING);
	ASSERT_EQ(lit->s_value, "test");

	mCc_ast_delete_literal(lit);
}

/*=========================================================== Expression*/

TEST(AstBuildExpression, CreateExpressionLiteral)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_string("test");
	mCc_ast_expression *exp = mCc_ast_new_expression_literal(lit);

	ASSERT_EQ(exp->type, MCC_AST_EXPRESSION_TYPE_LITERAL);
	ASSERT_EQ(exp->literal->s_value, "test");

	mCc_ast_delete_expression(exp);
}

TEST(AstBuildExpression, CreateExpressionBinaryOp)
{
	mCc_ast_literal *lit_left = mCc_ast_new_literal_int(2);
	mCc_ast_literal *lit_right = mCc_ast_new_literal_int(4);

	mCc_ast_expression *left_side = mCc_ast_new_expression_literal(lit_left);
	mCc_ast_expression *right_side = mCc_ast_new_expression_literal(lit_right);

	mCc_ast_expression *exp = mCc_ast_new_expression_binary_op(
	    MCC_AST_BINARY_OP_ADD, left_side, right_side);

	ASSERT_EQ(exp->type, MCC_AST_EXPRESSION_TYPE_BINARY_OP);
	ASSERT_EQ(exp->lhs->literal->i_value, 2);
	ASSERT_EQ(exp->rhs->literal->i_value, 4);

	mCc_ast_delete_expression(exp);
}

TEST(AstBuildExpression, CreateExpressionUnaryOp)
{
	mCc_ast_literal *lit_right = mCc_ast_new_literal_bool(false);

	mCc_ast_expression *right_side = mCc_ast_new_expression_literal(lit_right);

	mCc_ast_expression *exp =
	    mCc_ast_new_expression_unary_op(MCC_AST_UNARY_OP_NEGATION, right_side);

	ASSERT_EQ(exp->type, MCC_AST_EXPRESSION_TYPE_UNARY_OP);
	ASSERT_EQ(exp->unary_rhs->literal->b_value, false);

	mCc_ast_delete_expression(exp);
}
