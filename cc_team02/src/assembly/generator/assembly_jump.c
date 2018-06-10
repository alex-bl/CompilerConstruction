#include "assembly_jump.h"

// TODO: where is jump-dest?
static char *get_jump_dest(struct mCc_tac_element *tac_elem)
{
	return tac_elem->tac_argument1->name;
}

void mCc_assembly_generate_jump_equals(FILE *out,
                                       struct mCc_assembly_data *data,
                                       struct mCc_tac_element *tac_elem)
{
	mCc_assembly_jump_equals(out, data, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_not_equals(FILE *out,
                                           struct mCc_assembly_data *data,
                                           struct mCc_tac_element *tac_elem)
{
	mCc_assembly_jump_not_equals(out, data, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_greater(FILE *out,
                                        struct mCc_assembly_data *data,
                                        struct mCc_tac_element *tac_elem)
{
	mCc_assembly_jump_greater(out, data, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_less(FILE *out, struct mCc_assembly_data *data,
                                     struct mCc_tac_element *tac_elem)
{
	mCc_assembly_jump_less(out, data, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_greater_equals(FILE *out,
                                               struct mCc_assembly_data *data,
                                               struct mCc_tac_element *tac_elem)
{
	mCc_assembly_jump_greater_equals(out, data, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_less_equals(FILE *out,
                                            struct mCc_assembly_data *data,
                                            struct mCc_tac_element *tac_elem)
{
	mCc_assembly_jump_less_equals(out, data, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_and(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
	// TODO: correct?
	mCc_assembly_jump_equals(out, data, get_jump_dest(tac_elem));
}

void mCc_assembly_generate_jump_or(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
	mCc_assembly_jump_not_equals(out, data, get_jump_dest(tac_elem));
}
