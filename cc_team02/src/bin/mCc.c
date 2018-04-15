#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mCc/ast.h"
#include "mCc/parser.h"
#include "mCc/symtab_build.h"

void print_usage(const char *prg)
{
	printf("usage: %s <FILE>\n\n", prg);
	printf("  <FILE>        Input filepath or - for stdin\n");
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	/* determine input source */
	FILE *in;
	if (strcmp("-", argv[1]) == 0) {
		in = stdin;
	} else {
		in = fopen(argv[1], "r");
		if (!in) {
			perror("fopen");
			return EXIT_FAILURE;
		}
	}

	struct mCc_ast_program *prog = NULL;

	/* parsing phase */
	{
		struct mCc_parser_result result = mCc_parser_parse_file(in);
		fclose(in);

		if (result.status != MCC_PARSER_STATUS_OK) {
			mCc_parser_print_status(stderr, result);
			mCc_parser_destroy_parser(result);
			return EXIT_FAILURE;
		}
		prog = result.program;
	}

	/* build symbol-table */
	{
		struct mCc_validation_status_result *validation_result =
		    mCc_symtab_build_program(prog);
		/* print */
		mCc_validator_print_validation_result(validation_result, stdout);
		/* delete validation-result */
		mCc_validator_delete_validation_result(validation_result);
	}

	/*    TODO
	 * - run semantic checks
	 * - create three-address code
	 * - do some optimisations
	 * - output assembly code
	 * - invoke backend compiler
	 */

	/* cleanup */
	mCc_ast_delete_program(prog);

	return EXIT_SUCCESS;
}
