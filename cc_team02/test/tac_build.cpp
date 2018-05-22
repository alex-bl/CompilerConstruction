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
	char name[] = "ident_name";
	struct mCc_tac_identifier *ident1 = tac_new_identifier(name);

	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, ident1, ident1, ident1);

	// ASSERT_TRUE(true);
	ASSERT_EQ(tac->tac_operation, MCC_TAC_OPARATION_EMPTY);
	ASSERT_EQ(tac->tac_argument1->name, name);

	mCc_tac_delete_identifier(ident1);
	mCc_tac_delete(tac);
}

TEST(TAC, ConnectionBetweenTACs)
{
	char name[] = "ident_name";
	struct mCc_tac_identifier *ident1 = tac_new_identifier(name);

	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, ident1, ident1, ident1);

	struct mCc_tac_element *tac2 =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, ident1, ident1, ident1);

	mCc_tac_connect_tac_entry(tac, tac2);

	ASSERT_EQ(tac->tac_next_element, tac2);
	ASSERT_EQ(tac->tac_next_element->tac_result, tac2->tac_result);

	mCc_tac_delete_identifier(ident1);
	mCc_tac_delete(tac);
}

TEST(TAC, TACFloatLiteralExpression)
{
	char name[] = "ident_name";
	struct mCc_tac_identifier *ident1 = tac_new_identifier(name);

	struct mCc_tac_element *previous_tac =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, ident1, ident1, ident1);

	struct mCc_ast_literal *literal = mCc_ast_new_literal_float(12.3);

	struct mCc_ast_expression *expression =
	    mCc_ast_new_expression_literal(literal);

	struct mCc_tac_element *tac =
	    mCc_tac_expression_literal(expression, previous_tac);

	ASSERT_EQ(tac->tac_operation, MCC_TAC_OPARATION_EMPTY);
	ASSERT_EQ(tac->tac_result->name, (char *)&expression->literal->f_value);

	mCc_tac_delete_identifier(ident1);
	mCc_ast_delete_literal(literal);
	mCc_ast_delete_expression(expression);
	mCc_tac_delete(previous_tac);
	mCc_tac_delete(tac);
}

TEST(TAC, TACIntLiteralExpression)
{
	char name[] = "ident_name";
	struct mCc_tac_identifier *ident1 = tac_new_identifier(name);

	struct mCc_tac_element *previous_tac =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, ident1, ident1, ident1);

	struct mCc_ast_literal *literal = mCc_ast_new_literal_int(4);

	struct mCc_ast_expression *expression =
	    mCc_ast_new_expression_literal(literal);

	struct mCc_tac_element *tac =
	    mCc_tac_expression_literal(expression, previous_tac);

	ASSERT_EQ(tac->tac_operation, MCC_TAC_OPARATION_EMPTY);
	ASSERT_EQ(tac->tac_result->name, (char *)&expression->literal->i_value);

	mCc_tac_delete_identifier(ident1);
	mCc_ast_delete_literal(literal);
	mCc_ast_delete_expression(expression);
	mCc_tac_delete(previous_tac);
	mCc_tac_delete(tac);
}
