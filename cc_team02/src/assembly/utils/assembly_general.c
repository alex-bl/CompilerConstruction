#include "assembly_general.h"

#include <assert.h>
#include <stdio.h>

/*=========================================================== stack ops*/
/*
 * All literals are treated as variables (get their own tmp-label)
 */
void mCc_assembly_load_int(FILE *out, int tac_offset, const char *dest)
{
	/*
	 * TODO: calc "real" offset
	 */
	fprintf(out, "\tmovl %d(%%ebp), %s\n", tac_offset, dest);
}

// pops actual float-val from stack to dest
void mCc_assembly_load_float(FILE *out, int tac_offset)
{
	/*
	 * TODO: calc "real" offset
	 */
	fprintf(out, "\tflds\t%d(%%ebp)\n", tac_offset);
}

// stack_offset needs to be negative?
void mCc_assembly_push_int(FILE *out, int tac_offset, const char *dest)
{
	/*
	 * TODO: calc "real" offset
	 */
	fprintf(out, "\tmovl %s, %d(%%ebp)\n", dest, tac_offset);
}

// pushes float on floating-point-stack
void mCc_assembly_push_float(FILE *out, int tac_offset)
{
	/*
	 * TODO: calc "real" offset
	 */
	fprintf(out, "\tfstps -%d(%%ebp)\n", tac_offset);
}

/*============================================================= allocation */
void mCc_assembly_allocate_int_on_stack(FILE *out, int nr_of)
{
	/*
	 * TODO:
	 * - use space-calc-functions from assembly_utils
	 */
	// fprintf(out, "\tsubl $%ld, %%esp\n", space);
}

void mCc_assembly_allocate_float_on_stack(FILE *out, int nr_of) {}

void mCc_assembly_allocate_bool_on_stack(FILE *out, int nr_of) {}

void mCc_assembly_allocate_string_on_stack(FILE *out, int nr_of) {}

/*============================================================= return */

void mCc_assembly_prepare_return(FILE *out, int tac_offset)
{
	/*
	 * TODO:
	 * - use DEFAULT_RETURN_REG, DEFAULT_STACK_POINTER
	 * - use movl	<offset>(%ebp), (%eax)
	 */
}

/*============================================================= arithmetics */

void mCc_assembly_add_int(FILE *out)
{
	/*
	 * TODO:
	 * - values already loaded to registers
	 */
}

void mCc_assembly_add_float(FILE *out)
{
	/*
	 * TODO:
	 * - values already loaded to registers
	 */
}

void mCc_assembly_sub_int(FILE *out)
{
	/*
	 * TODO:
	 * - values already loaded to registers
	 */
}

void mCc_assembly_sub_float(FILE *out)
{
	/*
	 * TODO:
	 * - values already loaded to registers
	 */
}

void mCc_assembly_mul_int(FILE *out)
{
	/*
	 * TODO:
	 * - values already loaded to registers
	 */
}

void mCc_assembly_mul_float(FILE *out)
{
	/*
	 * TODO:
	 * - values already loaded to registers
	 */
}

void mCc_assembly_div_int(FILE *out)
{
	/*
	 * TODO:
	 * - values already loaded to registers
	 */
}

void mCc_assembly_div_float(FILE *out)
{
	/*
	 * TODO:
	 * - values already loaded to registers
	 */
}

/*============================================================= assignment */

/*=============================================================
 * logical-binary-ops */

/*============================================================= unary-ops */

/*============================================================= jumps */

/*============================================================= params */

/*============================================================= call */

/*============================================================= if/while */
