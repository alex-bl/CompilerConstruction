#include "mCc/ast/print/ast_print_declaration.h"
#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/visit/ast_visit_declaration.h"
#include <assert.h>

static const char *mCc_ast_print_literal_type(enum mCc_ast_literal_type type)
{
	switch (type) {
	case MCC_AST_LITERAL_TYPE_INT: return "int";
	case MCC_AST_LITERAL_TYPE_FLOAT: return "float";
	case MCC_AST_LITERAL_TYPE_BOOL: return "bool";
	case MCC_AST_LITERAL_TYPE_STRING: return "string";
	}
	return "unknown type";
}

void mCc_print_dot_declaration_primitive(
    struct mCc_ast_declaration *declaration, void *data)
{
	assert(declaration);
	assert(data);

	char label[LABEL_SIZE];
	snprintf(label, sizeof(label), "declaration: %s",
	         mCc_ast_print_literal_type(declaration->data_type));

	FILE *out = data;
	print_dot_node(out, declaration, label);
	print_dot_edge(out, declaration, declaration->identifier, "identifier");
	print_dot_edge_if_dest_exists(out, declaration,
	                              declaration->next_declaration, "next");
}

void mCc_print_dot_declaration_array(struct mCc_ast_declaration *declaration,
                                     void *data)
{
	assert(declaration);
	assert(data);

	char label_declaration[LABEL_SIZE];
	snprintf(
	    label_declaration, sizeof(label_declaration), "declaration: %s[%lu]",
	    mCc_ast_print_literal_type(declaration->data_type), declaration->size);

	FILE *out = data;
	print_dot_node(out, declaration, label_declaration);
	print_dot_edge(out, declaration, declaration->array_identifier,
	               "identifier");
	print_dot_edge_if_dest_exists(out, declaration,
	                              declaration->next_declaration, "next");
}
