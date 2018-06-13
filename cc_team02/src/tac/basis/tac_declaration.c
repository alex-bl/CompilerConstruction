#include "tac_declaration.h"

#include <assert.h>

#include "basic_tac.h"

// TODO put helper function on an higher base -> better reachable from other
// functions  or not!
enum mCc_tac_operation tac_helper_data_type_to_tac_declaration_primitive(
    enum mCc_ast_data_type data_type)
{
	switch (data_type) {
	case MCC_AST_DATA_TYPE_INT:
		return MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT;
		break;
	case MCC_AST_DATA_TYPE_FLOAT:
		return MCC_TAC_OPARATION_DECLARE_PRIMITIVE_FLOAT;
		break;
	case MCC_AST_DATA_TYPE_BOOL:
		return MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL;
		break;
	case MCC_AST_DATA_TYPE_STRING:
		return MCC_TAC_OPARATION_DECLARE_PRIMITIVE_STRING;
		break;
	default: return MCC_TAC_OPARATION_EMPTY; break;
	}
}

enum mCc_tac_operation
tac_helper_data_type_to_tac_declaration_array(enum mCc_ast_data_type data_type)
{
	switch (data_type) {
	case MCC_AST_DATA_TYPE_INT:
		return MCC_TAC_OPARATION_DECLARE_ARRAY_INT;
		break;
	case MCC_AST_DATA_TYPE_FLOAT:
		return MCC_TAC_OPARATION_DECLARE_ARRAY_FLOAT;
		break;
	case MCC_AST_DATA_TYPE_BOOL:
		return MCC_TAC_OPARATION_DECLARE_ARRAY_BOOL;
		break;
	case MCC_AST_DATA_TYPE_STRING:
		return MCC_TAC_OPARATION_DECLARE_ARRAY_STRING;
		break;
	default: return MCC_TAC_OPARATION_EMPTY; break;
	}
}

// x:= y
struct mCc_tac_element *
mCc_tac_declaration_primitive(struct mCc_ast_declaration *declaration,
                              struct mCc_tac_element *previous_tac)
{
	assert(declaration);
	assert(previous_tac);

	// puts scope level behind the variable name and return tac_identifier
	struct mCc_tac_identifier *name_identifier =
	    mCc_helper_concat_name_and_scope(
	        declaration->identifier->identifier_name,
	        declaration->identifier->symtab_info->scope_level);

	struct mCc_tac_element *tac =
	    tac_new_element(tac_helper_data_type_to_tac_declaration_primitive(
	                        declaration->data_type),
	                    NULL, NULL, name_identifier, MCC_TAC_TYPE_NO_TYPE, 0);
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

	// puts scope level behind the variable name and return tac_identifier
	struct mCc_tac_identifier *name_identifier =
	    mCc_helper_concat_name_and_scope(
	        declaration->identifier->identifier_name,
	        declaration->identifier->symtab_info->scope_level);

	struct mCc_tac_element *tac = tac_new_element(
	    tac_helper_data_type_to_tac_declaration_array(declaration->data_type),
	    NULL, tac_new_identifier_int((unsigned int)(declaration->size)),
	    name_identifier, MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac);
	return tac;
}
