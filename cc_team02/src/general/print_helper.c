#include "mCc/general/print_helper.h"

const char *print_data_type(enum mCc_ast_data_type type)
{
	switch (type) {
	case MCC_AST_DATA_TYPE_VOID: return "void";
	case MCC_AST_DATA_TYPE_INT: return "int";
	case MCC_AST_DATA_TYPE_FLOAT: return "float";
	case MCC_AST_DATA_TYPE_BOOL: return "bool";
	case MCC_AST_DATA_TYPE_STRING: return "string";
	case MCC_AST_DATA_TYPE_INCONSISTENT: return "inconsistent";
	}
	return "unknown type";
}
