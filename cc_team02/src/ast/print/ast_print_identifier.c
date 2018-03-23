#include <assert.h>
#include <stdlib.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_identifier.h"
#include "mCc/ast/visit/ast_visit_identifier.h"

static void print_dot_identifier(struct mCc_ast_identifier *identifier,
                                 void *data)
{
	assert(identifier);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "%s", identifier->identifier_name);

	FILE *out = data;
	print_dot_node(out, identifier, label);
}

static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

		.identifier = print_dot_identifier
	};
}

void mCc_ast_print_dot_identifier(FILE *out,
                                  struct mCc_ast_identifier *identifier)
{
	assert(out);
	assert(identifier);

	print_dot_begin(out);

	struct mCc_ast_visitor visitor = print_dot_visitor(out);
	mCc_ast_visit_identifier(identifier, &visitor);

	print_dot_end(out);
}
