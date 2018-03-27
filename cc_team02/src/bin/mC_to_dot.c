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
	struct mCc_ast_identifier *identifier = mCc_ast_new_identifier("my_bool_function");
	struct mCc_ast_literal *return_expr_lit = mCc_ast_new_literal_bool(true);
	struct mCc_ast_expression *return_expression =
	    mCc_ast_new_expression_literal(return_expr_lit);

	struct mCc_ast_statement *return_statement =
	    mCc_ast_new_return_statement(return_expression);

	struct mCc_ast_function_def *function_def =
	    mCc_ast_new_non_parameterized_function_def(
	        identifier, MCC_AST_FUNCTION_RETURN_TYPE_FLOAT, return_statement);


	mCc_ast_print_dot_function_def(stdout, function_def);
	mCc_ast_delete_function_def(function_def);

	return EXIT_SUCCESS;
}
