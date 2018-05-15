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
	struct mCc_ast_program *buildins = NULL;

	FILE *buildin_file = fopen(PATH_BUILDINS, "r");
	FILE *out_put = stdout;
	log_set_quiet(1);

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
		struct mCc_parser_result result = mCc_parser_parse_file(stdin);

		if (result.status != MCC_PARSER_STATUS_OK) {
			mCc_parser_print_status(stdout, result);
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
			fprintf(out_put, "Semantic errors detected:\n");
			fprintf(out_put, "================================================="
			                 "=========================================\n");
			mCc_symtab_print_semantic_errors(prog, out_put);
			fprintf(out_put, "================================================="
			                 "=========================================\n");
		} else {
			mCc_ast_print_dot_program(stdout, prog);
		}
	}

	mCc_ast_delete_program(prog);
	mCc_ast_delete_program(buildins);

	return EXIT_SUCCESS;
}
