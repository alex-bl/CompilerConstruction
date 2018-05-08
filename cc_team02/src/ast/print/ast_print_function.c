#include "mCc/ast/print/ast_print_function.h"

#include <assert.h>
#include <stdlib.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/general/print_helper.h"

void mCc_print_dot_function_def(struct mCc_ast_function_def *def, void *data)
{
	assert(def);
	assert(data);

	char label[LABEL_SIZE];
	snprintf(label, sizeof(label), "function-def: %s",
	         print_data_type(def->return_type));

	FILE *out = data;
	print_dot_node(out, def, label);
	// TODO:
	// print_dot_edge(out, def, def->return_type, "func: type");
	print_dot_edge(out, def, def->identifier, "identifier");
	print_dot_edge_if_dest_exists(out, def, def->first_parameter, "parameter");
	print_dot_edge_if_dest_exists(out, def, def->first_statement, "statement");
	print_dot_edge_if_dest_exists(out, def, def->next_function_def, "next");
}

void mCc_print_dot_function_call(struct mCc_ast_function_call *call, void *data)
{
	assert(call);
	assert(data);

	FILE *out = data;
	print_dot_node(out, call, "function_call()");
	print_dot_edge(out, call, call->identifier, "identifier");
	print_dot_edge_if_dest_exists(out, call, call->first_argument, "argument");
}
