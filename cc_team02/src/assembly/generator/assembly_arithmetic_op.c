#include "assembly_arithmetic_op.h"
#include "assembly_template.h"

#include <assert.h>

void mCc_assembly_generate_add(FILE *out, struct mCc_tac_element *tac_elem)
{
	assert(out);
	assert(tac_elem);
	const char *operant_1 = tac_elem->tac_argument1->name;
	const char *operant_2 = tac_elem->tac_argument2->name;

	assembly_add_integers(out, operant_1, operant_2);
}

void mCc_assembly_generate_sub(FILE *out, struct mCc_tac_element *tac_elem)
{
	assert(out);
	assert(tac_elem);
	const char *operant_1 = tac_elem->tac_argument1->name;
	const char *operant_2 = tac_elem->tac_argument2->name;

	assembly_sub_integers(out, operant_1, operant_2);
}

void mCc_assembly_generate_mul(FILE *out, struct mCc_tac_element *tac_elem)
{
	assert(out);
	assert(tac_elem);
	const char *operant_1 = tac_elem->tac_argument1->name;
	const char *operant_2 = tac_elem->tac_argument2->name;

	assembly_mul_integers(out, operant_1, operant_2);
}

void mCc_assembly_generate_div(FILE *out, struct mCc_tac_element *tac_elem)
{
	assert(out);
	assert(tac_elem);
	const char *operant_1 = tac_elem->tac_argument1->name;
	const char *operant_2 = tac_elem->tac_argument2->name;

	assembly_div_integers(out, operant_1, operant_2);
}
