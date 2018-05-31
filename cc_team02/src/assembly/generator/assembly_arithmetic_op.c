#include "assembly_arithmetic_op.h"
#include "assembly_template.h"

#include <assert.h>

// TODO: Überprüfe, ob %eax auch richtig verwendet wurde!!!

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

static handle_assembly_op_add_sub_mul(FILE *out,
                                      struct mCc_tac_element *tac_elem,
                                      const char *op)
{
	assert(out);
	assert(tac_elem);

	handle_tac_identifier(out, tac_elem->tac_argument1, "%eax");
	handle_tac_identifier(out, tac_elem->tac_argument2, "%ecx");
	fprintf(out, "\t%sl %%ecx,%%eax", op);
	fprintf(out, "\tmovl %%eax,-%d(%%ebp)", tac_elem->tac_result->stack_offset);
}

void mCc_assembly_generate_add_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "add");
}

void mCc_assembly_generate_add_float(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "add");
}


void mCc_assembly_generate_sub_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "sub");
}

void mCc_assembly_generate_sub_float(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "sub");
}


void mCc_assembly_generate_mul_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "mul");
}

void mCc_assembly_generate_mul_float(FILE *out, struct mCc_tac_element *tac_elem)
{
	handle_assembly_op_add_sub_mul(out, tac_elem, "mul");
}


void mCc_assembly_generate_div_int(FILE *out, struct mCc_tac_element *tac_elem)
{

}

void mCc_assembly_generate_div_float(FILE *out, struct mCc_tac_element *tac_elem)
{

}
