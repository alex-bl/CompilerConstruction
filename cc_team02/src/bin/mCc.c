#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "config.h"
#include "log.h"
#include "mCc/ast.h"
#include "mCc/ast_print.h"
#include "mCc/parser.h"
#include "mCc/semantic_check.h"
#include "mCc/tac.h"
#include "mCc/tac_print.h"

/*Argp: Inspired by
 * https://www.gnu.org/software/libc/manual/html_node/Argp-Example-4.html#Argp-Example-4*/
const char *argp_program_version = "mCc 1.6.2";
const char *argp_program_bug_address = "directly to the members of team02";

/* Program documentation */
static char doc[] = "mCc -- A compiler for the mC-language";

/* A description of the arguments */
static char args_doc[] = "INPUT_FILE or '-' for stdin";

/* Available options */
static struct argp_option options[] = {
	{ .name = "dot",
	  .key = 'd',
	  .flags = 0,
	  .group = 0,
	  .doc = "Print the AST in dot-notation\t(default=false)" },
	{ .name = "tac",
	  .key = 't',
	  .flags = 0,
	  .group = 0,
	  .doc = "Print the Three-adress-code\t(default=false)" },
	{ .name = "stdoutLog",
	  .key = 'l',
	  .flags = 0,
	  .group = 0,
	  .doc = "Log to stdout\t\t\t(default=false)" },
	{ .name = "fileLog",
	  .key = 'f',
	  .flags = 0,
	  .group = 0,
	  .doc = "Log into <project_dir>/log/\t(default=false)" },
	{ 0 }
};

/* Used by main to communicate with parse_opt */
struct arguments {
	char *args[1];
	bool to_dot;
	bool print_tac;
	bool log_on_stdout;
	bool file_log;
};

/* Parse a single option */
static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	/* Get the input argument from argp_parse */
	struct arguments *arguments = state->input;

	switch (key) {
	case 'd': arguments->to_dot = true; break;
	case 't': arguments->print_tac = true; break;
	case 'l': arguments->log_on_stdout = true; break;
	case 'f': arguments->file_log = true; break;
	case ARGP_KEY_ARG:
		if (state->arg_num >= 1)
			/* Too many arguments */
			argp_usage(state);
		arguments->args[state->arg_num] = arg;
		break;
	case ARGP_KEY_END:
		if (state->arg_num < 1)
			/* Not enough arguments */
			argp_usage(state);
		break;
	default: return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

/* The argp parser */
static struct argp argp = {
	.options = options, .parser = parse_opt, .args_doc = args_doc, .doc = doc
};

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

void config_logging(bool log_to_stdout, bool log_to_file)
{
	if (log_to_file) {
		char file_path[FILE_NAME_BUF_SIZE];
		build_log_file_name(file_path);

		FILE *log_file = fopen(file_path, "a");

		if (log_file == NULL) {
			log_error(
			    "Cannot open log-file. Logging to stdout instead (if enabled)");
		} else {
			log_set_fp(fopen(file_path, "a"));
		}
	}

	// enable log on stdout
	log_set_quiet(!log_to_stdout);
}

int main(int argc, char *argv[])
{
	struct arguments arguments;

	/* Default values: Disable all logging + printing */
	arguments.to_dot = false;
	arguments.print_tac = false;
	arguments.log_on_stdout = false;
	arguments.file_log = false;

	/* Parse arguments */
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	config_logging(arguments.log_on_stdout, arguments.file_log);

	/* Determine input source */
	FILE *in;
	if (strcmp("-", arguments.args[0]) == 0) {
		in = stdin;
	} else {
		in = fopen(arguments.args[0], "r");
		if (!in) {
			perror("fopen");
			return EXIT_FAILURE;
		}
	}

	struct mCc_ast_program *prog = NULL;
	struct mCc_ast_program *buildins = NULL;

	FILE *buildin_file = fopen(PATH_BUILDINS, "r");
	FILE *out_put = stdout;

	/* Deal with build-ins */
	{
		struct mCc_parser_result buildins_parsed =
		    mCc_parser_parse_file(buildin_file);
		fclose(buildin_file);

		buildins = buildins_parsed.program;
		buildins->is_library = true;
	}

	/* Parsing phase */
	{
		struct mCc_parser_result result = mCc_parser_parse_file(in);
		fclose(in);

		// wrong top-level
		if (result.top_level_type != MCC_PARSER_TOP_LEVEL_PROGRAM &&
		    result.status == MCC_PARSER_STATUS_OK) {
			result.status = MCC_PARSER_STATUS_INVALID_TOP_LEVEL;
		}

		if (result.status != MCC_PARSER_STATUS_OK) {
			mCc_parser_print_status(stderr, result);
			mCc_parser_destroy_parser(result);
			return EXIT_FAILURE;
		}

		prog = result.program;

		/* Include buildins */
		mCc_parser_include_functions(buildins, prog);
	}

	/*    TODO
	 * - run semantic checks		[done]
	 * - create three-address code	[done]
	 */

	/* Build symbol-table */
	{
		int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);

		if (nr_of_semantic_errors > 0) {
			fprintf(out_put, "================================================="
			                 "=========================================\n");
			fprintf(out_put, "Semantic checking finished with errors:\n");
			fprintf(out_put, "================================================="
			                 "=========================================\n");
			mCc_symtab_print_semantic_errors(prog, out_put);
			fprintf(out_put, "================================================="
			                 "=========================================\n");
			fprintf(out_put, "%d error(s) reported\n", nr_of_semantic_errors);
			fprintf(out_put, "================================================="
			                 "=========================================\n");
			mCc_ast_delete_program(prog);
			mCc_ast_delete_program(buildins);

			return EXIT_FAILURE;
		}
	}

	/*    TODO
	 * - do some optimisations
	 * - output assembly code
	 * - invoke backend compiler
	 */

	if (arguments.to_dot) {
		mCc_ast_print_dot_program(out_put, prog);
	}
	if (arguments.print_tac) {
		// TAC
		struct mCc_tac_element *tac = mCc_tac_start_program(prog);
		// TAC print
		mCc_tac_print_start_program(tac, out_put);

		mCc_tac_delete(tac);
	}

	/* cleanup */
	mCc_ast_delete_program(prog);
	mCc_ast_delete_program(buildins);

	return EXIT_SUCCESS;
}
