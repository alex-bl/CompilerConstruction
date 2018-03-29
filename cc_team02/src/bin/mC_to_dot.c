#include <stdio.h>
#include <stdlib.h>

#include "mCc/ast.h"
#include "mCc/ast_print.h"
#include "mCc/parser.h"

int main(void)
{
	// original content of this file

	//	struct mCc_ast_expression *expr = NULL;
	//
	//		/* parsing phase */
	//		{
	//			struct mCc_parser_result result = mCc_parser_parse_file(stdin);
	//			if (result.status != MCC_PARSER_STATUS_OK) {
	//				return EXIT_FAILURE;
	//			}
	//			expr = result.expression;
	//		}
	//
	//		mCc_ast_print_dot_expression(stdout, expr);
	//
	//		mCc_ast_delete_expression(expr);
	//
	//	return EXIT_SUCCESS;

	// just for testing/debugging purposes

	struct mCc_ast_expression *lit_left =
	    mCc_ast_new_expression_literal(mCc_ast_new_literal_int(42));
	struct mCc_ast_expression *lit_right =
	    mCc_ast_new_expression_literal(mCc_ast_new_literal_float(3.14));
	struct mCc_ast_expression *lit_right_unary =
	    mCc_ast_new_expression_unary_op(
	        MCC_AST_UNARY_OP_MINUS,
	        mCc_ast_new_expression_literal(mCc_ast_new_literal_int(192)));
	struct mCc_ast_expression *plus = mCc_ast_new_expression_binary_op(
	    MCC_AST_BINARY_OP_MUL, lit_right_unary, lit_right);

	struct mCc_ast_expression *parenth = mCc_ast_new_expression_parenth(plus);

	struct mCc_ast_expression *mul = mCc_ast_new_expression_binary_op(
	    MCC_AST_BINARY_OP_MUL, lit_left, parenth);

	mCc_ast_print_dot_expression(stdout, mul);
	mCc_ast_delete_expression(mul);

	return EXIT_SUCCESS;
}
