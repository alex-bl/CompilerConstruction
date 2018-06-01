#include "assembly_arithmetic_op.h"
#include "assembly_general.h"
#include "assembly_template.h"

#include <assert.h>

// TODO: Überprüfe, ob %eax auch richtig verwendet wurde!!!

void load_from_tac_identifier(FILE *out, struct mCc_tac_identifier *identifier,
                              const char *target_reg)
{
	if (identifier->type == MCC_IDENTIFIER_TAC_TYPE_INTEGER) {
		mCc_assembly_load_int_val_to_register(out, identifier->i_val,
		                                      target_reg);
	} else {
		mCc_assembly_load_int_from_stack(out, identifier->stack_offset,
		                                 target_reg);
	}
}

static void handle_assembly_op_add_sub_mul(FILE *out,
                                      struct mCc_tac_element *tac_elem,
                                      const char *op)
{
	assert(out);
	assert(tac_elem);

	load_from_tac_identifier(out, tac_elem->tac_argument1, "%eax");
	load_from_tac_identifier(out, tac_elem->tac_argument2, "%ecx");
	fprintf(out, "\t%sl %%ecx,%%eax\n", op);
	mCc_assembly_push_int_on_stack(out, tac_elem->tac_result->stack_offset,
	                               "%eax");
}

void mCc_assembly_generate_add_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "add");
}

void mCc_assembly_generate_add_float(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_generate_sub_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "sub");
}

void mCc_assembly_generate_sub_float(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_generate_mul_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "mul");
}

void mCc_assembly_generate_mul_float(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_generate_div_int(FILE *out, struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_generate_div_float(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
}
