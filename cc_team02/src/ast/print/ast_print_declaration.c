#include <assert.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_declaration.h"
#include "mCc/ast/visit/ast_visit_declaration.h"

const char *mCc_ast_print_literal_type(enum mCc_ast_literal_type type)
{
	switch (type) {
	case MCC_AST_LITERAL_TYPE_INT: return "int";
	case MCC_AST_LITERAL_TYPE_FLOAT: return "float";
	case MCC_AST_LITERAL_TYPE_BOOL: return "bool";
	case MCC_AST_LITERAL_TYPE_STRING: return "string";
	}
	return "unknown type";
}

void
mCc_print_dot_declaration_type(struct mCc_ast_declaration *declaration,
                               void *data)
{
	assert(declaration);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "dec type: %s",
	         mCc_ast_print_literal_type(declaration->declaration_type));

	FILE *out = data;
	print_dot_node(out, declaration, label);
}

void
mCc_print_dot_declaration_primitive(struct mCc_ast_declaration *declaration,
                                    void *data)
{
	assert(declaration);
	assert(data);

	FILE *out = data;
	print_dot_node(out, declaration, "declaration");
	print_dot_edge(out, declaration, declaration->identifier,
	               "declaration: identifier");
}

void
mCc_print_dot_declaration_array(struct mCc_ast_declaration *declaration,
                                void *data)
{

	assert(declaration);
	assert(data);

	FILE *out = data;
	print_dot_node(out, declaration, "declaration arr");
	print_dot_edge(out, declaration, declaration->array_identifier,
	               "declaration arr: identifier");
	//TODO: correct?
//	print_dot_edge(out, declaration,declaration->size,
//	               "declaration arr: size");
}
