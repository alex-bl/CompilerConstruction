#include "print_helper.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "config.h"

const char *print_data_type(enum mCc_ast_data_type type)
{
	switch (type) {
	case MCC_AST_DATA_TYPE_VOID: return "void";
	case MCC_AST_DATA_TYPE_INT: return "int";
	case MCC_AST_DATA_TYPE_FLOAT: return "float";
	case MCC_AST_DATA_TYPE_BOOL: return "bool";
	case MCC_AST_DATA_TYPE_STRING: return "string";
	case MCC_AST_DATA_TYPE_INCONSISTENT: return "inconsistent";
	case MCC_AST_DATA_TYPE_UNKNOWN: return "unknown";
	case MCC_AST_DATA_TYPE_INCOMPATIBLE: return "incompatible";
	}
	return "unknown type";
}

void print_signature(struct mCc_ast_identifier *identifier, char *buffer)
{
	assert(identifier->symtab_info);
	struct mCc_symtab_parameter_ref *next_parameter =
	    identifier->symtab_info->next_parameter;
	char intermediate_buffer[ERROR_MSG_BUF_SIZE / 2];

	// TODO: does param-ref has symtab-info at this stage?
	while (next_parameter) {
		const char *param_type =
		    print_data_type(next_parameter->identifier->symtab_info->data_type);
		const char *format;
		if (next_parameter->next_parameter) {
			format = "%s, ";
		} else {
			format = "%s";
		}

		snprintf(intermediate_buffer, strlen(param_type) + 1, format,
		         param_type);
		next_parameter = next_parameter->next_parameter;
	}

	snprintf(buffer, ERROR_MSG_BUF_SIZE / 2, "(%s)", intermediate_buffer);
}

const char *mCc_ast_print_binary_op(enum mCc_ast_binary_op op)
{
	switch (op) {
	case MCC_AST_BINARY_OP_ADD: return "+";
	case MCC_AST_BINARY_OP_SUB: return "-";
	case MCC_AST_BINARY_OP_MUL: return "*";
	case MCC_AST_BINARY_OP_DIV: return "/";
	case MCC_AST_BINARY_OP_LESS_THAN: return "<";
	case MCC_AST_BINARY_OP_GREATER_THAN: return ">";
	case MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN: return "<=";
	case MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN: return ">=";
	case MCC_AST_BINARY_OP_AND: return "&&";
	case MCC_AST_BINARY_OP_OR: return "||";
	case MCC_AST_BINARY_OP_EQUALS: return "==";
	case MCC_AST_BINARY_OP_NOT_EQUALS: return "!=";
	}
	return "unknown op";
}

const char *mCc_ast_print_unary_op(enum mCc_ast_unary_op op)
{
	switch (op) {
	case MCC_AST_UNARY_OP_MINUS: return "-";
	case MCC_AST_UNARY_OP_NEGATION: return "!";
	}
	return "unknown op";
}
