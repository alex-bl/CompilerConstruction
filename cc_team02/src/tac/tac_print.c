#include "mCc/tac_print.h"

#include "basic_tac.h"
#include <assert.h>
#include <stddef.h>

static const char *print_tac_op(enum mCc_tac_operation tac_operation)
{
	switch (tac_operation) {
	case MCC_TAC_OPARATION_EMPTY:
		return "EMPTY";
	// BINARY_OP
	case MCC_TAC_OPARATION_BINARY_OP_ADD_INT: return "ADD_INT";
	case MCC_TAC_OPARATION_BINARY_OP_ADD_FLOAT: return "ADD_FLOAT";

	case MCC_TAC_OPARATION_BINARY_OP_SUB_INT: return "SUB_INT";
	case MCC_TAC_OPARATION_BINARY_OP_SUB_FLOAT: return "SUB_FLOAT";

	case MCC_TAC_OPARATION_BINARY_OP_MUL_INT: return "MUL_INT";
	case MCC_TAC_OPARATION_BINARY_OP_MUL_FLOAT: return "MUL_FLOAT";

	case MCC_TAC_OPARATION_BINARY_OP_DIV_INT: return "DIV_INT";
	case MCC_TAC_OPARATION_BINARY_OP_DIV_FLOAT: return "DIV_FLOAT";

	case MCC_TAC_OPARATION_BINARY_AND: return "BINARY_AND";
	case MCC_TAC_OPARATION_BINARY_OR:
		return "BINARY_OR";

		// UNARY
	case MCC_TAC_OPARATION_UNARY_MINUS_INT: return "UNARY_MINUS_INT";
	case MCC_TAC_OPARATION_UNARY_MINUS_FLOAT: return "UNARY_MINUS_FLOAT";
	case MCC_TAC_OPARATION_UNARY_NEGATION:
		return "UNARY_NEGATION";

	// ASSIGN
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_INT: return "ASSIGN_INT";
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_FLOAT: return "ASSIGN_FLOAT";
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_BOOL: return "ASSIGN_BOOL";
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_STRING: return "ASSIGN_STRING";

	case MCC_TAC_OPARATION_ASSIGN_ARRAY_INT: return "ASSIGN_INT_ARRAY";
	case MCC_TAC_OPARATION_ASSIGN_ARRAY_FLOAT: return "ASSIGN_FLOAT_ARRAY";
	case MCC_TAC_OPARATION_ASSIGN_ARRAY_BOOL: return "ASSIGN_BOOL_ARRAY";
	case MCC_TAC_OPARATION_ASSIGN_ARRAY_STRING:
		return "ASSIGN_STRING_ARRAY";

	// COMPARE: (only one compair needed (result internally stored into cmp?
	// reg))
	case MCC_TAC_OPARATION_EQUALS_INT: return "EQUALS_INT";
	case MCC_TAC_OPARATION_EQUALS_FLOAT: return "EQUALS_FLOAT";
	case MCC_TAC_OPARATION_EQUALS_BOOL: return "EQUALS_BOOL";

	case MCC_TAC_OPARATION_NOT_EQUALS_INT: return "NOT_EQUALS_INT";
	case MCC_TAC_OPARATION_NOT_EQUALS_FLOAT: return "NOT_EQUALS_FLOAT";
	case MCC_TAC_OPARATION_NOT_EQUALS_BOOL: return "NOT_EQUALS_BOOL";

	case MCC_TAC_OPARATION_GREATER_INT: return "GREATER_INT";
	case MCC_TAC_OPARATION_GREATER_FLOAT: return "GREATER_FLOAT";

	case MCC_TAC_OPARATION_LESS_INT: return "LESS_INT";
	case MCC_TAC_OPARATION_LESS_FLOAT: return "LESS_FLOAT";

	case MCC_TAC_OPARATION_GREATER_EQUALS_INT: return "GREATER_EQUALS_INT";
	case MCC_TAC_OPARATION_GREATER_EQUALS_FLOAT: return "GREATER_EQUALS_FLOAT";

	case MCC_TAC_OPARATION_LESS_EQUALS_INT: return "LESS_EQUALS_INT";
	case MCC_TAC_OPARATION_LESS_EQUALS_FLOAT:
		return "LESS_EQUALS_FLOAT";

	// JUMP
	case MCC_TAC_OPARATION_JUMP_EQUALS: return "JUMP_EQUALS";
	case MCC_TAC_OPARATION_JUMP_NOT_EQUALS: return "JUMP_NOT_EQUALS";
	case MCC_TAC_OPARATION_JUMP_GREATER: return "JUMP_GREATER";
	case MCC_TAC_OPARATION_JUMP_LESS: return "JUMP_LESS";
	case MCC_TAC_OPARATION_JUMP_GRATER_EQUALS: return "JUMP_GREATER_EQUALS";
	case MCC_TAC_OPARATION_JUMP_LESS_EQUALS: return "JUMP_LESS_EQUALS";
	case MCC_TAC_OPARATION_JUMP_AND: return "JUMP_AND";
	case MCC_TAC_OPARATION_JUMP_OR: return "JUMP_OR";
	case MCC_TAC_OPARATION_JUMP: return "JUMP";
	case MCC_TAC_OPARATION_JUMP_FALSE:
		return "JUMP_FALSE";

	// RETURN
	case MCC_TAC_OPARATION_RETURN_PRIMITIVE_VOID:
		return "RETURN_PRIMITIVE_VOID";
	case MCC_TAC_OPARATION_RETURN_PRIMITIVE_INT: return "RETURN_PRIMITIVE_INT";
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_FLOAT:
		return "RETURN_PRIMITIVE_FLOAT";
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_BOOL:
		return "RETURN_PRIMITIVE_BOOL";
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_STRING:
		return "RETURN_PRIMITIVE_STRING";

	case MCC_TAC_OPARATION_RETURN_ARRAY_INT: return "RETURN_ARRAY_INT";
	case MCC_TAC_OPARATION_RETURN_ARRAY_FLOAT: return "RETURN_ARRAY_FLOAT";
	case MCC_TAC_OPARATION_RETURN_ARRAY_BOOL: return "RETURN_ARRAY_BOOL";
	case MCC_TAC_OPARATION_RETURN_ARRAY_STRING:
		return "RETURN_ARRAY_STRING";

	// PARAMETER
	case MCC_TAC_OPARATION_PARAM_INT_PRIMITIVE: return "PARAM_PRIMITIVE_INT";
	case MCC_TAC_OPARATION_PARAM_FLOAT_PRIMITIVE:
		return "PARAM_PRIMITIVE_FLOAT";
	case MCC_TAC_OPARATION_PARAM_BOOL_PRIMITIVE: return "PARAM_PRIMITIVE_BOOL";
	case MCC_TAC_OPARATION_PARAM_STRING_PRIMITIVE:
		return "PARAM_PRIMITIVE_STRING";
	case MCC_TAC_OPARATION_PARAM_INT_ARRAY: return "PARAM_ARRAY_INT";
	case MCC_TAC_OPARATION_PARAM_FLOAT_ARRAY: return "PARAM_ARRAY_FLOAT";
	case MCC_TAC_OPARATION_PARAM_BOOL_ARRAY: return "PARAM_ARRAY_BOOL";
	case MCC_TAC_OPARATION_PARAM_STRING_ARRAY: return "PARAM_ARRAY_STRING";

	case MCC_TAC_OPARATION_CALL:
		return "CALL";

	// LABEL
	case MCC_TAC_OPARATION_LABEL_FUNCTION: return "LABEL_FUNCTION";
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_INT: return "PSEUDO_ASSIGN_INT";
	case MCC_TAC_OPARATION_LABEL_BOOL: return "LABEL BOOL";
	case MCC_TAC_OPARATION_LABEL_FLOAT: return "LABEL_FLOAT";
	case MCC_TAC_OPARATION_LABEL_IF: return "LABEL_IF";
	case MCC_TAC_OPARATION_LABEL_ELSE: return "LABEL_ELSE";
	case MCC_TAC_OPARATION_LABEL_AFTER_ELSE: return "LABEL_AFTER_ELSE";
	case MCC_TAC_OPARATION_LABEL_WHILE: return "LABEL_WHILE";
	case MCC_TAC_OPARATION_LABEL_STRING:
		return "LABEL_STRING";

	// ARGUMENT
	case MCC_TAC_OPARATION_LABEL_ARGUMENT: return "LABEL_ARGUMENT";
	case MCC_TAC_OPARATION_ARGUMENT_LIST_START:
		return "STAR_ARGUMENT_LIST";

	// FUNCTION DEF
	case MCC_TAC_OPARATION_FUNCTION_CALL: return "FUNCTION_CALL";
	case MCC_TAC_OPARATION_START_FUNCTION_DEF: return "FUNCTION_DEF_START";
	case MCC_TAC_OPARATION_END_FUNCTION_DEF:
		return "FUNCTION_DEF_END";

	// DECLARATION
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT:
		return "DECLARATION_INT_PRIMITIVE";
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_FLOAT:
		return "DECLARATION_FLOAT_PRIMITIVE";
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL:
		return "DECLARATION_BOOL_PRIMITIVE";
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_STRING:
		return "DECLARATION_STRING_PRIMITIVE";
	case MCC_TAC_OPARATION_DECLARE_ARRAY_INT: return "DECLARATION_INT_ARRAY";
	case MCC_TAC_OPARATION_DECLARE_ARRAY_FLOAT:
		return "DECLARATION_FLOAT_ARRAY";
	case MCC_TAC_OPARATION_DECLARE_ARRAY_BOOL: return "DECLARATION_BOOL_ARRAY";
	case MCC_TAC_OPARATION_DECLARE_ARRAY_STRING:
		return "DECLARATION_STRING_ARRAY";

		// LITERAL
	case MCC_TAC_OPARATION_LITERAL: return "LITERAL";
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
		case MCC_IDENTIFIER_TAC_TYPE_VAR:
		case MCC_IDENTIFIER_TAC_TYPE_STRING:
			fprintf(out, "%20s", tac_identifier->name);
			break;
		}
	} else {
		fprintf(out, "%20s", "-");
	}
}

static const char *get_element_type_as_string(enum mCc_tac_type element_type)
{
	switch (element_type) {
	case MCC_TAC_TYPE_NO_TYPE: return "NO_TYPE";
	case MCC_TAC_TYPE_INTEGER: return "INTEGER";
	case MCC_TAC_TYPE_BOOL: return "BOOL";
	case MCC_TAC_TYPE_FLOAT: return "FLOAT";
	case MCC_TAC_TYPE_STRING: return "STRING";
	}
	return "UNKNOWN";
}

static void print_element_type(enum mCc_tac_type element_type, FILE *out)
{
	fprintf(out, "%10s", get_element_type_as_string(element_type));
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
		fprintf(out, "op: %25s", print_tac_op(tac->tac_operation));
		fprintf(out, " | ");
		print_tac_arg(tac->tac_argument1, out);
		fprintf(out, " | ");
		print_tac_arg(tac->tac_argument2, out);
		fprintf(out, " | ");
		print_tac_arg(tac->tac_result, out);
		fprintf(out, " | ");
		print_element_type(tac->tac_type, out);
		fprintf(out, " |\n");

		tac = tac->tac_next_element;
	}
}
