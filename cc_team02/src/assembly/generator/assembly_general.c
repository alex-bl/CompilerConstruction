#include "assembly_general.h"

#include <assert.h>
#include <stdio.h>

void mCc_assembly_load_int_from_stack(FILE *out, int stack_offset,
                                      const char *dest)
{
	fprintf(out, "\tmovl -%d(%%ebp), %s\n", stack_offset, dest);
}

// pops actual float-val from stack to dest
void mCc_assembly_load_float_from_stack(FILE *out, int stack_offset)
{
	fprintf(out, "\tflds\t-%d(%%ebp)\n", stack_offset);
}

void mCc_assembly_load_int_val_to_register(FILE *out, long int_val,
                                           const char *dest)
{
	fprintf(out, "\tmovl $%ld, %s\n", int_val, dest);
}

void mCc_assembly_store_float_val(FILE *out, float float_val, int float_counter)
{
	fprintf(out, ".LC%d:\n", float_counter);
	fprintf(out, "\t.float %f\n", float_val);
	// required?
	//	fprintf(out,"\talign 4\n");

	/*
	 * .LC1:
	    .long	1124344296
	    .align 4
	 *
	 */
}

void mCc_assembly_allocate_int_on_stack(FILE *out, size_t space)
{
	fprintf(out, "\tsubl $%ld, %%esp\n", space);
}

void mCc_assembly_allocate_float_on_stack(FILE *out, size_t space)
{
	fprintf(out, "\tsubl $%ld, %%esp\n", space);
}

// stack_offset needs to be negative?
void mCc_assembly_push_int_on_stack(FILE *out, int stack_offset,
                                    const char *dest)
{
	fprintf(out, "\tmovl %s, -%d(%%ebp)\n", dest, stack_offset);
}

// pushes float on floating-point-stack
void mCc_assembly_push_float_on_stack(FILE *out, int stack_offset)
{
	fprintf(out, "\tfstps -%d(%%ebp)\n", stack_offset);
}
