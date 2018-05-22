#include "mCc/tac_print.h"

#include "basic_tac.h"

#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "mCc_test/mCc_test_utils.h"
#include "map.h"

//============================================ TAC
TEST(TACPrint, firstTest)
{
	char name[] = "ident_name";
	struct mCc_tac_identifier *ident1 = tac_new_identifier(name);

	struct mCc_tac_element *tac =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, NULL, NULL, ident1, MCC_TAC_TYPE_NO_TYPE, NULL);

	// ASSERT_TRUE(true);
	ASSERT_EQ(tac->tac_operation, MCC_TAC_OPARATION_EMPTY);

	// TODO more and more useful tests
	// mCc_tac_print_start_program(struct mCc_tac_element *tac, FILE *out);
	// ASSERT_EQ(, "operation: 0 - argument1: ident_name - argument2: NULL -
	// result: NULL\n");
	mCc_tac_delete(tac);
}
