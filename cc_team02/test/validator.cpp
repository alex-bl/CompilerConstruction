#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "mCc/ast.h"
#include "symbol_table.h"
#include "validator.h"
#include "validator_helper.h"
#include "mCc_test/mCc_test_utils.h"
#include "map.h"

//============================================ validator helper
TEST(ValidatorHelper, FindReturnStatement)
{
	struct mCc_ast_expression *return_expr =
	    mCc_test_build_test_lit_expression(10);

	ASSERT_TRUE(return_expr != NULL);

	struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(MCC_AST_DATA_TYPE_INT, "func",
	                                     return_expr);

	ASSERT_TRUE(function_def != NULL);

	struct mCc_ast_statement *return_statement =
	    mCc_validator_find_return_statement(function_def);

	ASSERT_TRUE(return_statement != NULL);
	ASSERT_EQ(MCC_AST_STATEMENT_RETURN, return_statement->statement_type);
	ASSERT_EQ(MCC_AST_EXPRESSION_TYPE_LITERAL,
	          return_statement->return_expression->type);
	ASSERT_EQ(10, return_statement->return_expression->literal->i_value);

	mCc_ast_delete_function_def(function_def);
}

TEST(ValidatorHelper, FindReturnStatementEmpty)
{
	struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(MCC_AST_DATA_TYPE_INT, "func", NULL);

	ASSERT_TRUE(function_def != NULL);

	struct mCc_ast_statement *return_statement =
	    mCc_validator_find_return_statement(function_def);

	EXPECT_EQ(NULL, return_statement);

	mCc_ast_delete_function_def(function_def);
}

//============================================ validator
TEST(Validator, NewValidationStatusResult)
{
	struct mCc_validation_status_result *validation_result =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type"));

	ASSERT_TRUE(validation_result != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE,
	          validation_result->validation_status);
	ASSERT_STREQ("Invalid type", validation_result->error_msg);
	EXPECT_EQ(NULL, validation_result->next);

	mCc_validator_delete_validation_result(validation_result);
}

TEST(Validator, NewValidationStatusResultConcatted)
{
	struct mCc_validation_status_result *validation_result =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type"));

	struct mCc_validation_status_result *validation_result_next =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type next"));

	ASSERT_TRUE(validation_result != NULL);
	ASSERT_TRUE(validation_result_next != NULL);

	validation_result->next = validation_result_next;

	ASSERT_TRUE(validation_result->next != NULL);
	ASSERT_STREQ("Invalid type next", validation_result->next->error_msg);

	mCc_validator_delete_validation_result(validation_result);
}

TEST(Validator, AppendSemanticError)
{
	struct mCc_validation_status_result *validation_result =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type"));

	struct mCc_validation_status_result *validation_result_next =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type next"));

	ASSERT_TRUE(validation_result != NULL);
	ASSERT_TRUE(validation_result_next != NULL);

	mCc_validator_append_semantic_error(validation_result,
	                                    validation_result_next);

	ASSERT_TRUE(validation_result->next != NULL);
	ASSERT_STREQ("Invalid type next", validation_result->next->error_msg);

	mCc_validator_delete_validation_result(validation_result);
}

TEST(Validator, AppendSemanticErrorThreeStage)
{
	struct mCc_validation_status_result *validation_result =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type"));

	struct mCc_validation_status_result *validation_result_next =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type next"));

	struct mCc_validation_status_result *validation_result_third =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type third"));

	ASSERT_TRUE(validation_result != NULL);
	ASSERT_TRUE(validation_result_next != NULL);
	ASSERT_TRUE(validation_result_third != NULL);

	mCc_validator_append_semantic_error(validation_result,
	                                    validation_result_next);
	mCc_validator_append_semantic_error(validation_result,
	                                    validation_result_third);

	ASSERT_TRUE(validation_result->next->next != NULL);
	ASSERT_STREQ("Invalid type third",
	             validation_result->next->next->error_msg);

	mCc_validator_delete_validation_result(validation_result);
}

// just for completeness :D
TEST(Validator, DeleteValidationResult)
{
	struct mCc_validation_status_result *validation_result =
	    mCc_validator_new_validation_result(MCC_VALIDATION_STATUS_INVALID_TYPE,
	                                        strdup("Invalid type"));
	mCc_validator_delete_validation_result(validation_result);
}
