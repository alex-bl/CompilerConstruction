#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "log.h"
#include "mCc/ast.h"
#include "mCc/parser.h"
#include "mCc/semantic_check.h"

void print_usage(const char *prg)
{
	printf("usage: %s <FILE>\n\n", prg);
	printf("  <FILE>        Input filepath or - for stdin\n");
}

void build_log_file_name(char file_name_buf[])
{
	time_t timer;
	struct tm *tm_info;
	char buffer[TIME_BUF_SIZE];

	time(&timer);
	tm_info = localtime(&timer);

	strftime(buffer, TIME_BUF_SIZE, "%Y-%m-%d", tm_info);
	snprintf(file_name_buf, FILE_NAME_BUF_SIZE, "%s%s-mCc.log",
	         LOG_FILE_PATH_BASE_DIR, buffer);
}

void config_logging()
{
	// always log to log-file
	char file_path[FILE_NAME_BUF_SIZE];
	build_log_file_name(file_path);

	FILE *log_file = fopen(file_path, "a");

	if (log_file == NULL) {
		log_error(
		    "Cannot open log-file. Logging to stdout instead (if enabled)");
	} else {
		log_set_fp(fopen(file_path, "a"));
	}

	// enable log on stdout
	log_set_quiet(LOG_QUIET);
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		print_usage(argv[0]);
		return EXIT_FAILURE;
	}

	config_logging();

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
	FILE *out_put = stdout;

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
			fprintf(out_put, "Semantic errors detected:\n");
			fprintf(out_put, "================================================="
			                 "=========================================\n");
			mCc_symtab_print_semantic_errors(prog, out_put);
			fprintf(out_put, "================================================="
			                 "=========================================\n");
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
