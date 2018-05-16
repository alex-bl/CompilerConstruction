#include <stdbool.h>
#include <stddef.h>

#include "basic_tac.h"
#include "mCc/tac.h"

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
}

TEST(TAC, TACTest) {

}
