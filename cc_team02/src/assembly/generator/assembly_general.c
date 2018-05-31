#include <assert.h>
#include <stdio.h>

void mCc_assembly_load_int_from_stack(FILE *out, int stack_offset,
                                      const char *dest)
{
	fprintf(out, "\tmovl %d(%%ebp), %s", stack_offset, dest);
}

void mCc_assembly_load_float_from_stack(FILE *out, int stack_offset,
                                        const char *dest)
{
	fprintf(out, "\tfstps -%d(%s)", stack_offset, dest);
}

void mCc_assembly_load_int_val_to_register(FILE *out, int int_val,
                                           const char *dest)
{
	fprintf(out, "\tmovl $%d, %s", int_val, dest);
}

void mCc_assembly_load_float_val_to_register(FILE *out, int int_val,
                                             const char *dest)
{
	//?
}

void mCc_assembly_allocate_int_on_stack(FILE *out, size_t space)
{
	fprintf(out, "\tsubl $%ld, %%esp", space);
}

void mCc_assembly_allocate_float_on_stack(FILE *out, size_t space) {
	fprintf(out, "\tsubl $%ld, %%esp", space);
}

// stack_offset needs to be negative?
void mCc_assembly_push_int_on_stack(FILE *out, int stack_offset,
                                    const char *dest)
{
	fprintf(out, "\tmovl %s, %d(%%ebp)", dest, stack_offset);
}

void mCc_assembly_push_float_on_stack(FILE *out, int stack_offset,
                                      const char *dest)
{
	fprintf(out,"\tflds	%d(%ebp)",stack_offset);
}
