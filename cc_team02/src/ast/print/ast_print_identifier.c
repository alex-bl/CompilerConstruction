#include "ast_print_identifier.h"

#include <assert.h>
#include <stdlib.h>

#include "ast_basic_printing.h"

void mCc_print_dot_identifier(struct mCc_ast_identifier *identifier, void *data)
{
	assert(identifier);
	assert(data);

	char label[LABEL_SIZE] = { 0 };
	snprintf(label, sizeof(label), "%s", identifier->identifier_name);

	FILE *out = data;
	print_dot_node(out, identifier, label);
}
