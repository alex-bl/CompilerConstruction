#include "tac_literal.h"

#include <assert.h>
#include <stdlib.h>

#include "basic_tac.h"

//literals are not needed? -> get generated in the tac_expression

//TODO recursive structure
/*struct mCc_tac_element *
mCc_tac_literal_int(struct mCc_ast_literal *literal,
                    struct mCc_tac_element *previous_tac)
{
	assert(literal);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, tac_new_identifier((char *)&literal->i_value),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

//TODO recursive structure
struct mCc_tac_element *
mCc_tac_literal_float(struct mCc_ast_literal *literal,
                      struct mCc_tac_element *previous_tac)
{
	assert(literal);
	assert(previous_tac);

	// tac_new_element(MCC_TAC_OPERATION_EMPTY, tac_new_identifier((char
	// *)&literal->f_value), NULL, NULL);
	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, tac_new_identifier((char *)&literal->b_value),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

//TODO recursive structure
struct mCc_tac_element *
mCc_tac_literal_bool(struct mCc_ast_literal *literal,
                     struct mCc_tac_element *previous_tac)
{
	assert(literal);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, tac_new_identifier((char *)&literal->b_value),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

//TODO recursive structure
struct mCc_tac_element *
mCc_tac_literal_string(struct mCc_ast_literal *literal,
                       struct mCc_tac_element *previous_tac)
{
	assert(literal);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, tac_new_identifier((char *)&literal->s_value),
	    NULL, NULL);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}*/

//->DELETE?
