#include "mCc/tac_print.h"

#include "basic_tac.h"
#include <assert.h>
#include <stddef.h>

static const char *print_tac_op(enum mCc_tac_operation tac_operation)
{
	switch (tac_operation) {
	case MCC_TAC_OPARATION_EMPTY: return "EMPTY";
	case MCC_TAC_OPARATION_BINARY_OP_ADD_INT: return "ADD_I";
	case MCC_TAC_OPARATION_BINARY_OP_ADD_FLOAT: return "ADD_F";
	case MCC_TAC_OPARATION_BINARY_OP_SUB_INT: return "SUB_I";
	case MCC_TAC_OPARATION_BINARY_OP_SUB_FLOAT: return "SUB_F";
	case MCC_TAC_OPARATION_BINARY_OP_MUL_INT: return "MUL_I";
	case MCC_TAC_OPARATION_BINARY_OP_MUL_FLOAT: return "MUL_F";
	case MCC_TAC_OPARATION_BINARY_OP_DIV_INT: return "DIV_I";
	case MCC_TAC_OPARATION_BINARY_OP_DIV_FLOAT: return "DIV_F";
	case MCC_TAC_OPARATION_BINARY_OP_LESS_THAN: return "LT\t";
	case MCC_TAC_OPARATION_BINARY_OP_GREATER_THAN: return "GT\t";
	case MCC_TAC_OPARATION_BINARY_OP_LESS_OR_EQUALS_THAN: return "LTE";
	case MCC_TAC_OPARATION_BINARY_OP_GREATER_OR_EQUALS_THAN: return "GTE";
	case MCC_TAC_OPARATION_BINARY_OP_AND: return "AND\t";
	case MCC_TAC_OPARATION_BINARY_OP_OR: return "OR\t";
	case MCC_TAC_OPARATION_BINARY_OP_EQUALS: return "EQ";
	case MCC_TAC_OPARATION_BINARY_OP_NOT_EQUALS: return "NE\t";
	case MCC_TAC_OPARATION_UNARY_OP_MINUS: return "MINUS";
	case MCC_TAC_OPARATION_UNARY_OP_NEGATION: return "NEG\t";
	case MCC_TAC_OPARATION_COPY: return "COPY";
	case MCC_TAC_OPARATION_UNCONDITIONAL_JUMP: return "JUMP UNCOND";
	case MCC_TAC_OPARATION_CONDITIONAL_JUMP: return "JUMP COND";
	case MCC_TAC_OPARATION_PROCEDURAL_CALL: return "CALL";
	case MCC_TAC_OPARATION_RETURN: return "RETURN";
	case MCC_TAC_OPARATION_INDEXING: return "INDEX";
	case MCC_TAC_OPARATION_LABLE: return "LABEL";
	case MCC_TAC_OPARATION_FUNCTION_DEF: return "DEF\t";
	case MCC_TAC_OPARATION_FUNCTION_PARAMETER: return "PARAM";
	}
	return "unknown";
}

static void print_tac_arg(struct mCc_tac_identifier *tac_identifier, FILE *out)
{
	if (tac_identifier) {
		switch (tac_identifier->type) {
		case MCC_IDENTIFIER_TAC_TYPE_INTEGER:
			fprintf(out, "%20ld", tac_identifier->i_val);
			break;
		case MCC_IDENTIFIER_TAC_TYPE_FLOAT:
			fprintf(out, "%20lf", tac_identifier->f_val);
			break;
		case MCC_IDENTIFIER_TAC_TYPE_BOOL:
			fprintf(out, "%20s", (tac_identifier->b_val) ? "true" : "false");
			break;
		case MCC_IDENTIFIER_TAC_TYPE_STRING:
			fprintf(out, "%20s", tac_identifier->name);
			break;
		}
	} else {
		fprintf(out, "%20s","-");
	}
}

/*
 * should be the "top"
 * is "global"
 */
void mCc_tac_print_start_program(struct mCc_tac_element *tac, FILE *out)
{
	assert(tac);
	assert(out);

	fprintf(out, "Printing TAC-table:\n");

	while (tac != NULL) {
		fprintf(out, "op: %s", print_tac_op(tac->tac_operation));
		fprintf(out, "\t| ");
		print_tac_arg(tac->tac_argument1, out);
		fprintf(out, " | ");
		print_tac_arg(tac->tac_argument2, out);
		fprintf(out, " | ");
		print_tac_arg(tac->tac_result, out);
		fprintf(out, " |\n");

		tac = tac->tac_next_element;
	}
}
