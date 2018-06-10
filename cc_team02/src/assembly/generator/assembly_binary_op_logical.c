#include "assembly_binary_op_logical.h"
#include "assembly_utils.h"

/*==================================== equals*/

void mCc_assembly_equals_int(FILE *out, struct mCc_assembly_data *data,
                             struct mCc_tac_element *tac_elem)
{
	int pos_operand_1 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument1, data->current_stack_pos);
	int pos_operand_2 = mCc_assembly_calc_stack_position(
	    tac_elem->tac_argument2, data->current_stack_pos);
	mCc_assembly_compare_int(out, pos_operand_1, pos_operand_2);
	//TODO: compare-flag auslesen + result reinspeichern?
}

void mCc_assembly_equals_float(FILE *out, struct mCc_assembly_data *data,
                               struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_equals_bool(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem)
{
}

/*==================================== not equals*/

void mCc_assembly_not_equals_int(FILE *out, struct mCc_assembly_data *data,
                                 struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_not_equals_float(FILE *out, struct mCc_assembly_data *data,
                                   struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_not_equals_bool(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem)
{
}

/*==================================== greater*/

void mCc_assembly_greater_int(FILE *out, struct mCc_assembly_data *data,
                              struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_greater_float(FILE *out, struct mCc_assembly_data *data,
                                struct mCc_tac_element *tac_elem)
{
}

/*==================================== less*/

void mCc_assembly_less_int(FILE *out, struct mCc_assembly_data *data,
                           struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_less_float(FILE *out, struct mCc_assembly_data *data,
                             struct mCc_tac_element *tac_elem)
{
}

/*==================================== greater equals*/
void mCc_assembly_greater_equals_int(FILE *out,
                                     struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_greater_equals_float(FILE *out,
                                       struct mCc_tac_element *tac_elem)
{
}

/*==================================== less equals*/
void mCc_assembly_less_equals_int(FILE *out, struct mCc_assembly_data *data,
                                  struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_less_equals_float(FILE *out, struct mCc_assembly_data *data,
                                    struct mCc_tac_element *tac_elem)
{
}

/*==================================== and/or */
void mCc_assembly_and(FILE *out, struct mCc_assembly_data *data,
                      struct mCc_tac_element *tac_elem)
{
}

void mCc_assembly_or(FILE *out, struct mCc_assembly_data *data,
                     struct mCc_tac_element *tac_elem)
{
}
