#include "mCc/tac/basis/tac_literal.h"

#include <assert.h>
#include <stdlib.h>

#include "mCc/tac/basis/basic_tac.h"

void mCc_tac_literal_int(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, literal->i_value, NULL, NULL);
}

void mCc_tac_literal_float(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, literal->f_value, NULL, NULL);
}

void mCc_tac_literal_bool(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, literal->b_value, NULL, NULL);
}

void mCc_tac_literal_string(struct mCc_ast_literal *literal, void *data)
{
	assert(literal);
	assert(data);

	tac_new_element(MCC_TAC_OPERATION_EMPTY, literal->s_value, NULL, NULL);
}
