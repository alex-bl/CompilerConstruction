#include "tac_declaration.h"

#include <assert.h>

#include "basic_tac.h"

//TODO put helper function on an higher base -> better reachable from other functions
//or not!
char *helper_data_type_to_char(enum mCc_ast_data_type data_type)
{
	/*MCC_AST_DATA_TYPE_VOID,
	MCC_AST_DATA_TYPE_INT,
	MCC_AST_DATA_TYPE_FLOAT,
	MCC_AST_DATA_TYPE_BOOL,
	MCC_AST_DATA_TYPE_STRING,
	MCC_AST_DATA_TYPE_INCONSISTENT,
	// if incompatible for semantic checks
	MCC_AST_DATA_TYPE_INCOMPATIBLE,
	// needed if unknown identifier was processed
	MCC_AST_DATA_TYPE_UNKNOWN
	*/
	char *return_char;
	switch (data_type) {
	case MCC_AST_DATA_TYPE_VOID: return_char = "void"; break;
	case MCC_AST_DATA_TYPE_INT: return_char = "int"; break;
	case MCC_AST_DATA_TYPE_FLOAT: return_char = "float"; break;
	case MCC_AST_DATA_TYPE_BOOL: return_char = "bool"; break;
	case MCC_AST_DATA_TYPE_STRING: return_char = "string"; break;
	case MCC_AST_DATA_TYPE_INCONSISTENT: return_char = "inconsistent"; break;
	case MCC_AST_DATA_TYPE_INCOMPATIBLE: return_char = "incompatible"; break;
	case MCC_AST_DATA_TYPE_UNKNOWN: return_char = "unknow"; break;
	}
	return return_char;
}

// x:= y
struct mCc_tac_element *
mCc_tac_declaration_primitive(struct mCc_ast_declaration *declaration,
                              struct mCc_tac_element *previous_tac)
{
	assert(declaration);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_LABLE,
	    tac_new_identifier(helper_data_type_to_char(declaration->data_type)),
	    NULL, tac_new_identifier(declaration->identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}

// y[i]:=x
struct mCc_tac_element *
mCc_tac_declaration_array(struct mCc_ast_declaration *declaration,
                          struct mCc_tac_element *previous_tac)
{
	assert(declaration);
	assert(previous_tac);

	struct mCc_tac_element *tac = tac_new_element(
	    MCC_TAC_OPARATION_LABLE,
	    tac_new_identifier(helper_data_type_to_char(declaration->data_type)),
	    tac_new_identifier((char *)&declaration->size),
	    tac_new_identifier(declaration->array_identifier->identifier_name));
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
