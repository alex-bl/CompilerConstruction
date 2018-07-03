#include <stdbool.h>
#include <stddef.h>

#include "basic_tac.h"
#include "mCc/tac.h"
#include "tac_expression.h"

#include "gtest/gtest.h"

#include "mCc_test/mCc_test_utils.h"
#include "map.h"

//============================================ TAC
TEST(TAC, BasicTAC)
{
	char name[] = "test";
	struct mCc_tac_identifier *ident1 =
	    tac_new_identifier(name);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, NULL, NULL, ident1, MCC_TAC_TYPE_NO_TYPE, 0);

	// ASSERT_TRUE(true);
	ASSERT_EQ(tac->tac_operation, MCC_TAC_OPARATION_EMPTY);
	ASSERT_STREQ(tac->tac_result->name, name);

	mCc_tac_delete(tac);
}

TEST(TAC, ConnectionBetweenTACs)
{
	char name[] = "ident_name";
	struct mCc_tac_identifier *ident1 = tac_new_identifier(name);
	struct mCc_tac_identifier *ident2 = tac_new_identifier(name);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, NULL, NULL, ident1, MCC_TAC_TYPE_NO_TYPE, 0);

	struct mCc_tac_element *tac2 = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, NULL, NULL, ident2, MCC_TAC_TYPE_NO_TYPE, 0);

	mCc_tac_connect_tac_entry(tac, tac2);

	ASSERT_EQ(tac->tac_next_element, tac2);
	ASSERT_EQ(tac->tac_next_element->tac_result, tac2->tac_result);

	mCc_tac_delete(tac);
}

TEST(TAC, TACFloatLiteralExpression)
{
	char name[] = "ident_name";
	struct mCc_tac_identifier *ident1 = tac_new_identifier(name);

	struct mCc_tac_element *previous_tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, NULL, NULL, ident1, MCC_TAC_TYPE_NO_TYPE, 0);

	struct mCc_ast_literal *literal = mCc_ast_new_literal_float(12.3);

	struct mCc_ast_expression *expression =
	    mCc_ast_new_expression_literal(literal);

	ASSERT_EQ(previous_tac->tac_operation, MCC_TAC_OPARATION_EMPTY);
	//ASSERT_EQ(tac->tac_result->f_val, expression->literal->f_value);

	//mCc_ast_delete_literal(literal);
	mCc_ast_delete_expression(expression);
	mCc_tac_delete(previous_tac);
	//mCc_tac_delete(tac);
}

TEST(TAC, TACIntLiteralExpression)
{
	char name[] = "ident_name";
	struct mCc_tac_identifier *ident1 = tac_new_identifier(name);

	struct mCc_tac_element *previous_tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, NULL, NULL, ident1, MCC_TAC_TYPE_NO_TYPE, 0);

	struct mCc_ast_literal *literal = mCc_ast_new_literal_int(4);

	struct mCc_ast_expression *expression =
	    mCc_ast_new_expression_literal(literal);

	ASSERT_EQ(previous_tac->tac_operation, MCC_TAC_OPARATION_EMPTY);
	//ASSERT_EQ(tac->tac_result->i_val, expression->literal->i_value);

	//mCc_ast_delete_literal(literal);
	mCc_ast_delete_expression(expression);
	mCc_tac_delete(previous_tac);
	// mCc_tac_delete(tac);
}
