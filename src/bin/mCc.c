#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mCc/ast.h"
#include "mCc/parser.h"

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

	struct mC_ast_expression *expr = mC_parser_parse_file(in);
	if (!expr) {
		fclose(in);
		return EXIT_FAILURE;
	}

	/* TODO */

	mC_ast_delete_expression(expr);

	fclose(in);

	return EXIT_SUCCESS;
}
