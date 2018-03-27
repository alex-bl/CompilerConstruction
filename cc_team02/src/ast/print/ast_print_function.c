#include "mCc/ast/print/ast_print_function.h"
#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/visit/ast_visit_function.h"
#include <assert.h>
#include <stdlib.h>

static const char *print_dot_return_type(enum mCc_ast_function_return_type type)
{
	switch (type) {
	case MCC_AST_FUNCTION_RETURN_TYPE_VOID: return "void";
	case MCC_AST_FUNCTION_RETURN_TYPE_INT: return "int";
	case MCC_AST_FUNCTION_RETURN_TYPE_FLOAT: return "float";
	case MCC_AST_FUNCTION_RETURN_TYPE_BOOL: return "bool";
	case MCC_AST_FUNCTION_RETURN_TYPE_STRING: return "string";
	}
	return "unknown type";
}

void mCc_print_dot_function_def(struct mCc_ast_function_def *def, void *data)
{
	assert(def);
	assert(data);

	char label[LABEL_SIZE];
	snprintf(label, sizeof(label), "function-def: %s",
	         print_dot_return_type(def->return_type));

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
