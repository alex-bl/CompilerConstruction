#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"
#include "mCc/ast_print.h"
#include "mCc/parser.h"

int main(void)
{
	struct mCc_ast_expression *expr = NULL;

	/* parsing phase */
	{
		struct mCc_parser_result result = mCc_parser_parse_file(stdin);
		if (result.status != MCC_PARSER_STATUS_OK) {
			return EXIT_FAILURE;
		}
		expr = result.expression;
	}

	mCc_ast_print_dot_expression(stdout, expr);

	mCc_ast_delete_expression(expr);

	return EXIT_SUCCESS;
}
