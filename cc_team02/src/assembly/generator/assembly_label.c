#include "assembly_label.h"
#include "assembly_formatter.h"

static void print_label_without_dot(FILE *out, const char *label)
{
	fprintf(out, "%s:", label);
	mCc_assembly_print_nl(out);
}

static void print_label(FILE *out, const char *label)
{
	fprintf(out, ".");
	print_label_without_dot(out, label);
}

static char *get_label(struct mCc_tac_element *tac_elem)
{
	// TODO: at argument_1?
	return tac_elem->tac_argument1->name;
}

static char *get_label_function(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result->name;
}

void mCc_assembly_label_function(FILE *out, struct mCc_assembly_data *data,
                                 struct mCc_tac_element *tac_elem)
{
	print_label_without_dot(out, get_label_function(tac_elem));
}

void mCc_assembly_label_float(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem)
{
	// maybe some special treatment for float-labels
	print_label(out, get_label(tac_elem));
}

void mCc_assembly_label_string(FILE *out, struct mCc_assembly_data *data,
                               struct mCc_tac_element *tac_elem)
{
	// maybe some special treatment for string-labels
	print_label(out, get_label(tac_elem));
}

void mCc_assembly_label_if(FILE *out, struct mCc_assembly_data *data,
                           struct mCc_tac_element *tac_elem)
{
	// maybe some special treatment for if-labels
	print_label(out, get_label(tac_elem));
}

void mCc_assembly_label_else(FILE *out, struct mCc_assembly_data *data,
                             struct mCc_tac_element *tac_elem)
{
	// maybe some special treatment for else-labels
	print_label(out, get_label(tac_elem));
}

void mCc_assembly_label_while(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem)
{
	// maybe some special treatment for while-labels
	print_label(out, get_label(tac_elem));
}
