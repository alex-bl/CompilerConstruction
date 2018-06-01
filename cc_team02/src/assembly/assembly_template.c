#include "assembly_template.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*=== baisics */
void assembly_new_header(FILE *out, const char *file_name,
                         const char *next_function_label)
{
	fprintf(out, "\t.file\t%s\n", file_name);
	fprintf(out, "\t.text\t\n");
	fprintf(out, "\t.globl\t%s\n", next_function_label);
	fprintf(out, "\t.type\t%s,@function\n", next_function_label);
}

void assembly_new_function_def_enter(FILE *out, const char *function_label)
{
	fprintf(out, "%s:\n", function_label);
	fprintf(out, "\tpushl\t%%ebp\n");
	fprintf(out, "\tmovl\t%%esp, %%ebp\n");
}

// TODO: what is correct?
void assembly_new_function_def_leave(FILE *out, const char *function_label,
                                     const char *next_function_label)
{
	//	fprintf(out, "\tpopl\t%%edp\n");
	//	fprintf(out, "\tret\n");
	fprintf(out, "\taddl\t%%edx, %%eax\n");
	fprintf(out, "leave");
	fprintf(out, "ret");
	fprintf(out, "\t.size\%s, .-%s\n", function_label, function_label);
	fprintf(out, "\t.globl\t%s\n", next_function_label);
	fprintf(out, "\t.type\t%s, @function\n", next_function_label);
}

void assembly_main_function_enter(FILE *out)
{
	fprintf(out, "\tleal\t4(%%esp), %%ecx\n");
	fprintf(out, "\tandl\t$-16, %%esp\n");
	fprintf(out, "\tpushl\t-4(%%ecx)\n");
	fprintf(out, "\tpushl\t%%ebp\n");
	fprintf(out, "\tmovl\t%%esp, %%ebp\n");
	fprintf(out, "\tpushl\t%%ecx\n");
}

void assembly_main_function_leave(FILE *out)
{
	fprintf(out, "\tmovl\t-4(%%ebp), %%ecx\n");
	fprintf(out, "\tleave\n");
	fprintf(out, "\tleal\t-4(%%ecx), %%esp\n");
	fprintf(out, "\tret\n");
	fprintf(out, "\t.size\tmain, .-main\n");
	fprintf(out, "\t.ident\t\"GCC: (Ubuntu 7.3.0-16ubuntu3~16.04.1) 7.3.0\"\n");
	fprintf(out, "\t.section\t.note.GNU-stack,\"\",@progbits\n");
}

void assembly_new_string(FILE *out, int string_index, const char *str_value,
                         const char *next_function_label)
{
	fprintf(out, ".LC%d\n", string_index);
	fprintf(out, "\t.string\t\"%s\"\n", str_value);
	fprintf(out, "\t.text\n");
	fprintf(out, "\t.global\t%s\n", next_function_label);
	fprintf(out, "\t.type\t%s, @function\n", next_function_label);
}
