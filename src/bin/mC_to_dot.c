#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"
#include "mCc/parser.h"

int main(void)
{
	struct mC_ast_expression *expr = mC_parser_run(stdin);
	if (!expr) {
		return EXIT_FAILURE;
	}

	FILE *out = stdout;
	mC_ast_dot_print_begin(out);
	mC_ast_dot_print_expression(out, expr);
	mC_ast_dot_print_end(out);

	mC_ast_expression_delete(expr);

	return EXIT_SUCCESS;
}
