#include "assembly_arithmetic_op.h"
#include "assembly_general.h"
#include "assembly_template.h"

#include <assert.h>

// TODO: Überprüfe, ob %eax auch richtig verwendet wurde!!!

void load_from_int_tac_identifier(FILE *out,
                                  struct mCc_tac_identifier *identifier,
                                  const char *target_reg)
{
	//	if (identifier->type == MCC_IDENTIFIER_TAC_TYPE_INTEGER) {
	//		mCc_assembly_load_int_val_to_register(out, identifier->i_val,
	//		                                      target_reg);
	//	} else {
	//		mCc_assembly_load_int_from_stack(out, identifier->stack_offset,
	//		                                 target_reg);
	//	}
	/*
	 * TODO: redo that thing
	 */
}

// TODO: REVIEW!!
void load_from_float_tac_identifier(FILE *out,
                                    struct mCc_tac_identifier *identifier,
                                    int float_counter)
{
	//	if (identifier->type == MCC_IDENTIFIER_TAC_TYPE_FLOAT) {
	//		mCc_assembly_store_float_val(out, identifier->f_val, float_counter);
	//		mCc_assembly_push_float_on_stack(out, identifier->stack_offset);
	//	} else {
	//		mCc_assembly_load_float_from_stack(out, identifier->stack_offset);
	//	}
	/*
	 * TODO: redo that thing
	 */
}

static void handle_assembly_int_op_add_sub_mul(FILE *out,
                                               struct mCc_tac_element *tac_elem,
                                               const char *op)
{
	//	assert(out);
	//	assert(tac_elem);
	//
	//	load_from_int_tac_identifier(out, tac_elem->tac_argument1, "%ecx");
	//	load_from_int_tac_identifier(out, tac_elem->tac_argument2, "%edx");
	//	fprintf(out, "\t%sl %%ecx,%%edx\n", op);
	//	mCc_assembly_push_int_on_stack(out, tac_elem->tac_result->stack_offset,
	//	                               "%edx");
	/*
	 * TODO: redo that thing
	 */
}

// TODO: float-var-counter required?
static void
handle_assembly_float_arithmetic_op(FILE *out, struct mCc_tac_element *tac_elem,
                                    const char *op)
{
	//	assert(out);
	//	assert(tac_elem);
	//
	//	load_from_float_tac_identifier(out, tac_elem->tac_argument1,0);
	//	load_from_float_tac_identifier(out, tac_elem->tac_argument2,1);
	//	fprintf(out, "\tf%ss -%d(%%edp)\n", op,
	//	        tac_elem->tac_argument2->stack_offset);
	//	mCc_assembly_push_float_on_stack(out,
	//tac_elem->tac_result->stack_offset);
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_add_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	//	handle_assembly_int_op_add_sub_mul(out, tac_elem, "add");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_add_float(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
	//	handle_assembly_float_arithmetic_op(out, tac_elem, "add");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_sub_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	// handle_assembly_int_op_add_sub_mul(out, tac_elem, "sub");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_sub_float(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
	// handle_assembly_float_arithmetic_op(out, tac_elem, "sub");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_mul_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	// handle_assembly_int_op_add_sub_mul(out, tac_elem, "mul");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_mul_float(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
	// handle_assembly_float_arithmetic_op(out, tac_elem, "mul");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_div_int(FILE *out, struct mCc_tac_element *tac_elem)
{
	//	assert(out);
	//	assert(tac_elem);
	//	// divident needs to be %eax?
	//	load_from_int_tac_identifier(out, tac_elem->tac_argument1, "%eax");
	//	// is this correct this way?
	//	fprintf(out, "\tcltd\n");
	//	// divisor
	//	load_from_int_tac_identifier(out, tac_elem->tac_argument2, "%ecx");
	//	fprintf(out, "\tidivl %%ecx\n");
	//	mCc_assembly_push_int_on_stack(out, tac_elem->tac_result->stack_offset,
	//	                               "%ecx");
	/*
	 * TODO: redo that thing
	 */
}

void mCc_assembly_generate_div_float(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
	// handle_assembly_float_arithmetic_op(out, tac_elem, "div");
	/*
	 * TODO: redo that thing
	 */
}
