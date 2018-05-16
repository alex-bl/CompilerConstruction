#include "ast_print_function.h"

#include <assert.h>
#include <stdlib.h>

#include "ast_basic_printing.h"
#include "print_helper.h"

void mCc_print_dot_function_def(struct mCc_ast_function_def *def, void *data)
{
	assert(def);
	assert(data);

	char label[LABEL_SIZE];
	snprintf(label, sizeof(label), "function-def: %s",
	         mCc_ast_print_data_type(def->return_type));

	FILE *out = data;
	mCc_ast_print_dot_node(out, def, label);
	// TODO:
	// mCc_ast_print_dot_edge(out, def, def->return_type, "func: type");
	mCc_ast_print_dot_edge(out, def, def->identifier, "identifier");
	mCc_ast_print_dot_edge_if_dest_exists(out, def, def->first_parameter,
	                                      "parameter");
	mCc_ast_print_dot_edge_if_dest_exists(out, def, def->first_statement,
	                                      "statement");
	mCc_ast_print_dot_edge_if_dest_exists(out, def, def->next_function_def,
	                                      "next");
}

void mCc_print_dot_function_call(struct mCc_ast_function_call *call, void *data)
{
	assert(call);
	assert(data);

	FILE *out = data;
	mCc_ast_print_dot_node(out, call, "function_call()");
	mCc_ast_print_dot_edge(out, call, call->identifier, "identifier");
	mCc_ast_print_dot_edge_if_dest_exists(out, call, call->first_argument,
	                                      "argument");
}
