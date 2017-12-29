#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"
#include "mCc/parser.h"

int main(int argc, char *argv[])
{
	FILE *in = stdin;

	struct mC_ast_expression *expr = mC_parser_run(in);
	if (!expr) {
		return EXIT_FAILURE;
	}

	/* Print AST for graphviz. */
	{
		FILE *out = stdout;
		mC_ast_dot_print_begin(out);
		mC_ast_dot_print_expression(out, expr);
		mC_ast_dot_print_end(out);
	}

	mC_ast_expression_delete(expr);

	return EXIT_SUCCESS;
}
