#include "assembly_arithmetic_op.h"
#include "assembly_template.h"

#include <assert.h>

//TODO: Überprüfe, ob %eax auch richtig verwendet wurde!!!

void handle_tac_identifier(FILE *out, struct mCc_tac_identifier *identifier,
                           const char *target_reg)
{
	if (identifier->type == MCC_IDENTIFIER_TAC_TYPE_INTEGER) {
		fprintf("\taddl $%ld,%s", identifier->i_val, target_reg);
	} else {
		fprintf(out, "\tmovl -%d(%%ebp), %s", identifier->stack_offset,
		        target_reg);
	}
}

void mCc_assembly_generate_add(FILE *out, struct mCc_tac_element *tac_elem)
{
	assert(out);
	assert(tac_elem);

	handle_tac_identifier(out,tac_elem->tac_argument1,"%eax");
	handle_tac_identifier(out,tac_elem->tac_argument2,"%ecx");
	fprintf(out,"\taddl %%ecx,%%eax");
	fprintf(out,"\tmovl %%eax,-%d(%%ebp)",tac_elem->tac_result->stack_offset);
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
