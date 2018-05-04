#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "log.h"
#include "mCc/ast.h"
#include "mCc/general/parser_helper.h"
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
	struct mCc_ast_program *buildins = NULL;

	FILE *buildin_file = fopen(PATH_BUILDINS, "r");
	/* deal with build-ins */
	{
		struct mCc_parser_result buildins_parsed =
		    mCc_parser_parse_file(buildin_file);
		fclose(buildin_file);

		buildins = buildins_parsed.program;
		buildins->is_library = true;
	}

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

		// include buildins
		mCc_parser_include_functions(buildins, prog);
	}

	/* build symbol-table */
	{
		bool semantic_check_successfull =
		    mCc_symtab_perform_semantic_checks(prog);

		if (!semantic_check_successfull) {
			/* TODO:
			 * - create print infrastructure and print
			 */
			printf("Semantic errors detected");
		}
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
	mCc_ast_delete_program(buildins);

	return EXIT_SUCCESS;
}
