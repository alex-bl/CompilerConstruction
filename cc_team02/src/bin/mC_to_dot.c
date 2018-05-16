#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "mCc/ast.h"
#include "mCc/ast_print.h"
#include "mCc/parser.h"
#include "mCc/semantic_check.h"

int main(void)
{
	struct mCc_ast_program *prog = NULL;

	FILE *out_put = stdout;
	log_set_quiet(1);

	/* parsing phase */
	{
		struct mCc_parser_result result = mCc_parser_parse_file(stdin);

		if (result.status != MCC_PARSER_STATUS_OK) {
			mCc_parser_print_status(out_put, result);
			mCc_parser_destroy_parser(result);
			return EXIT_FAILURE;
		}
		prog = result.program;
	}

	mCc_ast_print_dot_program(out_put, prog);
	mCc_ast_delete_program(prog);

	return EXIT_SUCCESS;
}
