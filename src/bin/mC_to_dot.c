#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"
#include "mCc/parser.h"

int main(void)
{
	struct mC_ast_expression *expr = mC_parser_parse_file(stdin);
	if (!expr) {
		return EXIT_FAILURE;
	}

	FILE *out = stdout;
	mC_ast_print_dot_begin(out);
	mC_ast_print_dot_expression(out, expr);
	mC_ast_print_dot_end(out);

	mC_ast_delete_expression(expr);

	return EXIT_SUCCESS;
}
