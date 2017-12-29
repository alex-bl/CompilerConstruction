#include <stdio.h>
#include <stdlib.h>

#include "../ast.h"

#include "../parser.tab.h"

int main(void)
{
	struct mC_ast_expression *ast = mC_parser_run();

	//printf("Result: %ld\n", result);
	return EXIT_SUCCESS;
}
