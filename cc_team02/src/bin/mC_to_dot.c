#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"
#include "mCc/ast_print.h"
#include "mCc/parser.h"

int main(void)
{
//	struct mCc_ast_expression *expr = NULL;
//
//	/* parsing phase */
//	{
//		struct mCc_parser_result result = mCc_parser_parse_file(stdin);
//		if (result.status != MCC_PARSER_STATUS_OK) {
//			return EXIT_FAILURE;
//		}
//		expr = result.expression;
//	}

	struct mCc_ast_literal *lit_left = mCc_ast_new_literal_int(4);
	struct mCc_ast_literal *lit_right = mCc_ast_new_literal_int(1);

	struct mCc_ast_expression *expression_binary_op = mCc_ast_new_expression_binary_op(
	    MCC_AST_BINARY_OP_MUL, mCc_ast_new_expression_literal(lit_left),
	    mCc_ast_new_expression_literal(lit_right));

	mCc_ast_print_dot_expression(stdout, expression_binary_op);

	mCc_ast_delete_expression(expression_binary_op);

	return EXIT_SUCCESS;
}
