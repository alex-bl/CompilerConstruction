#include "assembly_label.h"

#include <string.h>

#include "assembly_formatter.h"
#include "assembly_general.h"
#include "assembly_template.h"
#include "basic_tac.h"

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
	return tac_elem->tac_result->name;
}

static char *get_label_function(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result->name;
}

static char *get_label_float(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_result->name;
}

static struct mCc_tac_identifier *
get_float_val_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

static struct mCc_tac_identifier *
get_string_val_identifier(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1;
}

static char *get_string_label(struct mCc_tac_element *tac_elem)
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
	struct mCc_tac_identifier *identifier = get_float_val_identifier(tac_elem);
	mCc_assembly_new_float(out, identifier->f_val, get_label_float(tac_elem));
}

void mCc_assembly_label_string(FILE *out, struct mCc_assembly_data *data,
                               struct mCc_tac_element *tac_elem)
{
	struct mCc_tac_identifier *identifier = get_string_val_identifier(tac_elem);

	// NOTE: value is stored at name... strange -.-
	mCc_assembly_new_string_enter(out, get_string_label(tac_elem),
	                              identifier->name);
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

void mCc_assembly_label_after_else(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	print_label(out, get_label(tac_elem));
}

void mCc_assembly_label_while(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem)
{
	// maybe some special treatment for while-labels
	print_label(out, get_label(tac_elem));
}
