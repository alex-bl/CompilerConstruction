#include <assert.h>
#include <stdlib.h>

#include "mCc/ast.h"
#include "mCc/parser.h"

int main(int argc, char *argv[])
{
	const long repetitions = argc >= 2 ? atol(argv[1]) : 100000;

	const char input[] = "192 + 3.14";

	for (long i = 0; i < repetitions; i++) {
		struct mCc_parser_result result = mCc_parser_parse_string(input);

		assert(result.status == MCC_PARSER_STATUS_OK);

		mCc_ast_delete_expression(result.expression);
	}

	return EXIT_SUCCESS;
}
