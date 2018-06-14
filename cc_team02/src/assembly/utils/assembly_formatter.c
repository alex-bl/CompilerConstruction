#include "assembly_formatter.h"

void mCc_assembly_print_shift(FILE *out)
{
	//TODO: nicer for stdout
	//fprintf(out, "\t");
	fprintf(out, "   ");
}

void mCc_assembly_print_nl(FILE *out)
{
	fprintf(out, "\n");
}

void mCc_assembly_print_op(FILE *out, const char *op)
{
	fprintf(out, "%s", op);
	mCc_assembly_print_shift(out);
}
