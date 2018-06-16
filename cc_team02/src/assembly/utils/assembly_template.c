/**
 * Contains all the needed templates for assembly-generation (non functions,
 * e.g. a new file-header, etc...)
 */

#include "assembly_template.h"

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembly_formatter.h"

/*=== basics */
void mCc_assembly_new_header(FILE *out, const char *file_name,
                             const char *next_function_label)
{
	mCc_assembly_print_shift(out);
	fprintf(out, ".file\t\"%s\"", file_name);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	fprintf(out, ".text\t");
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	fprintf(out, ".globl\t%s", next_function_label);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	fprintf(out, ".type\t%s, @function", next_function_label);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_new_function_def_enter(FILE *out, const char *function_label)
{
	fprintf(out, "%s:", function_label);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_op(out, "pushl");
	fprintf(out, "%s", DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_op(out, "movl");
	fprintf(out, "%s, %s", DEFAULT_STACK_POINTER, DEFAULT_DATA_STACK_POINTER);
	mCc_assembly_print_nl(out);
}

// TODO: what is correct?
void mCc_assembly_new_function_def_leave(FILE *out, const char *function_label,
                                         const char *next_function_label)
{
	//	fprintf(out, "popl\t%%edp");
	//	fprintf(out, "ret");
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "addl");
	fprintf(out, "%s, %s", EDX_REG, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "leave");
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "ret");
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".size");
	fprintf(out, "%s, .-%s", function_label, function_label);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".globl");
	fprintf(out, "%s", next_function_label);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".type");
	fprintf(out, "%s, @function", next_function_label);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_main_function_enter(FILE *out)
{
	//TODO: is this really required or is main just a simple function?
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "leal");
//	fprintf(out, "4(%s), %s", DEFAULT_STACK_POINTER, ECX_REG);
//	mCc_assembly_print_nl(out);
//
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "andl");
//	fprintf(out, "$-16, %s", DEFAULT_STACK_POINTER);
//	mCc_assembly_print_nl(out);
//
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "pushl");
//	fprintf(out, "-4(%s)", ECX_REG);
//	mCc_assembly_print_nl(out);
//
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "pushl");
//	fprintf(out, "%s", DEFAULT_DATA_STACK_POINTER);
//	mCc_assembly_print_nl(out);
//
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "movl");
//	fprintf(out, "%s, %s", DEFAULT_STACK_POINTER, DEFAULT_DATA_STACK_POINTER);
//	mCc_assembly_print_nl(out);
//
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "pushl");
//	fprintf(out, "%s", ECX_REG);
//	mCc_assembly_print_nl(out);
	mCc_assembly_new_function_def_enter(out, "main");
}

//TODO: main must not be the last function -.-
void mCc_assembly_main_function_leave(FILE *out)
{
	//TODO: is this really required or is main just a simple function?
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "movl");
//	fprintf(out, "-4(%s), %s", DEFAULT_DATA_STACK_POINTER, ECX_REG);
//	mCc_assembly_print_nl(out);
//
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "leave");
//	mCc_assembly_print_nl(out);
//
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "leal");
//	fprintf(out, "-4(%s), %s", ECX_REG, DEFAULT_STACK_POINTER);
//	mCc_assembly_print_nl(out);
//
//	mCc_assembly_print_shift(out);
//	mCc_assembly_print_op(out, "ret");
//	mCc_assembly_print_nl(out);

//TODO: copied from function-def-leave
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "addl");
	fprintf(out, "%s, %s", EDX_REG, DEFAULT_ACCUMULATOR_OPERAND);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "leave");
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, "ret");
	mCc_assembly_print_nl(out);

//============================================

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".size");
	fprintf(out, "main, .-main");
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".ident");
	fprintf(out, "\"GCC: (Ubuntu 7.3.0-16ubuntu3~16.04.1) 7.3.0\"");
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".section");
	fprintf(out, ".note.GNU-stack,\"\",@progbits");
	mCc_assembly_print_nl(out);
}

void mCc_assembly_new_string_enter(FILE *out, const char *label,
                                   const char *str_value)
{

	fprintf(out, ".%s", label);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".string");
	fprintf(out, "\"%s\"", str_value);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_new_string_leave_with_function(
    FILE *out, const char *next_function_label)
{
	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".text");
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".global");
	fprintf(out, "%s", next_function_label);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".type");
	fprintf(out, "%s, @function", next_function_label);
	mCc_assembly_print_nl(out);
}

void mCc_assembly_new_float(FILE *out, float float_val, const char *label)
{

	fprintf(out, ".%s:", label);
	mCc_assembly_print_nl(out);

	mCc_assembly_print_shift(out);
	mCc_assembly_print_op(out, ".float");
	fprintf(out, "%f", float_val);
	mCc_assembly_print_nl(out);
	// fprintf(out,".align 4"); => really required?
}
