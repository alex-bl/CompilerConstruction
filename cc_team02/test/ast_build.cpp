#include "gtest/gtest.h"

#include "mCc/ast.h"
#include <stdbool.h>
#include <stddef.h>

TEST(AstBuilder, CreateInt)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_int(12);

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_INT);
	ASSERT_EQ(lit->i_value, 12);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuilder, CreateFloat)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_float(1.2);

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_FLOAT);
	ASSERT_EQ(lit->f_value, 1.2);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuilder, CreateBool)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_bool(true);

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_BOOL);
	ASSERT_EQ(lit->b_value, true);

	mCc_ast_delete_literal(lit);
}

TEST(AstBuilder, CreateString)
{
	mCc_ast_literal *lit = mCc_ast_new_literal_string("test");

	ASSERT_EQ(lit->type, MCC_AST_LITERAL_TYPE_STRING);
	ASSERT_EQ(lit->s_value, "test");

	mCc_ast_delete_literal(lit);
}
