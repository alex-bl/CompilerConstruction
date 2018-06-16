
#include "tac_utils.h"

enum mCc_tac_type
mCc_tac_map_from_ast_data_type(enum mCc_ast_data_type ast_data_type)
{

	switch (ast_data_type) {
	case MCC_AST_DATA_TYPE_INT: return MCC_TAC_TYPE_INTEGER; break;
	case MCC_AST_DATA_TYPE_FLOAT: return MCC_TAC_TYPE_FLOAT; break;
	case MCC_AST_DATA_TYPE_BOOL: return MCC_TAC_TYPE_BOOL; break;
	case MCC_AST_DATA_TYPE_STRING: return MCC_TAC_TYPE_STRING; break;
	default: return MCC_TAC_TYPE_NO_TYPE; break;
	}

	return MCC_TAC_TYPE_NO_TYPE;
}
