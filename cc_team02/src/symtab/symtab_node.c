#include "symtab_node.h"

#include "ast_declaration.h"
#include "ast_function.h"
#include "ast_identifier.h"
#include "symtab_types.h"

#include "log.h"
#include <assert.h>
#include <stdlib.h>

struct mCc_symtab_parameter_ref *
mCc_symtab_new_parameter_ref(struct mCc_ast_identifier *identifier)
{
	assert(identifier);
	struct mCc_symtab_parameter_ref *param_ref = malloc(sizeof(*param_ref));
	if (!param_ref) {
		log_error("Malloc failed: Could not aquire heap-space for "
		          "'mCc_symbol_table_node'.");
		return NULL;
	}
	param_ref->identifier = identifier;
	param_ref->next_parameter = NULL;
	return param_ref;
}

// TODO: review
struct mCc_symbol_table_node *
mCc_symtab_new_declaration_node(struct mCc_ast_declaration *declaration)
{
	assert(declaration);

	struct mCc_symbol_table_node *node = malloc(sizeof(*node));
	if (!node) {
		log_error("Malloc failed: Could not aquire heap-space for "
		          "'mCc_symbol_table_node'.");
		return NULL;
	}

	// distinguish between primitive declaration and array
	if (declaration->declaration_type == MCC_AST_DECLARATION_PRIMITIVE) {
		node->entry_type = MCC_SYM_TAB_IDENTIFIER_VARIABLE_PRIMITIVE;
		node->size = 0;
	} else {
		node->entry_type = MCC_SYM_TAB_IDENTIFIER_VARIABLE_ARRAY;
		node->size = declaration->size;
	}

	node->data_type = declaration->data_type;
	node->next_parameter = NULL;
	node->already_defined = false;

	return node;
}

/**
 *
 * @param function_def
 * @return
 */
struct mCc_symbol_table_node *
mCc_symtab_new_function_def_node(struct mCc_ast_function_def *function_def)
{
	assert(function_def);

	struct mCc_symbol_table_node *node = malloc(sizeof(*node));
	if (!node) {
		log_error("Malloc failed: Could not aquire heap-space for "
		          "'mCc_symbol_table_node'.");
		return NULL;
	}

	node->entry_type = MCC_SYM_TAB_IDENTIFIER_FUNCTION;
	node->data_type = function_def->return_type;
	node->already_defined = false;

	// has params?
	struct mCc_ast_declaration *parameter = function_def->first_parameter;

	if (parameter) {
		struct mCc_symtab_parameter_ref *first_param_node =
		    mCc_symtab_new_parameter_ref(
		        mCc_ast_get_declaration_identifier(parameter));

		first_param_node->next_parameter = NULL;
		struct mCc_symtab_parameter_ref *next_param_node = first_param_node;

		struct mCc_ast_declaration *next_param = parameter->next_declaration;

		while (next_param) {
			next_param_node->next_parameter = mCc_symtab_new_parameter_ref(
			    mCc_ast_get_declaration_identifier(next_param));

			next_param_node = next_param_node->next_parameter;
			next_param = next_param->next_declaration;
		}
		// concatenation
		node->next_parameter = first_param_node;
	} else {
		node->next_parameter = NULL;
	}

	return node;
}

void mCc_symtab_delete_symtab_parameter_ref(
    struct mCc_symtab_parameter_ref *ref)
{
	assert(ref);
	if (ref->next_parameter) {
		mCc_symtab_delete_symtab_parameter_ref(ref->next_parameter);
	}
	/*
	 * TODO: identifier is not freed, because it is the same address from the
	 * ast-identifier and it is freed there
	 */
	free(ref);
}

void mCc_symtab_delete_symtab_node(struct mCc_symbol_table_node *node)
{

	assert(node);

	switch (node->entry_type) {
	// currently no special treatment in case of freeing
	case MCC_SYM_TAB_IDENTIFIER_FUNCTION_PARAMETER:
	case MCC_SYM_TAB_IDENTIFIER_VARIABLE_ARRAY:
	case MCC_SYM_TAB_IDENTIFIER_VARIABLE_PRIMITIVE: free(node); break;
	case MCC_SYM_TAB_IDENTIFIER_FUNCTION:
		if (node->next_parameter) {
			mCc_symtab_delete_symtab_parameter_ref(node->next_parameter);
		}
		free(node);
		break;
	}
}
