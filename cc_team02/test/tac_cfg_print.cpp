#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "config.h"
#include "mCc/ast.h"
#include "mCc/tac.h"
#include "mCc/tac_cfg_print.h"
#include "mCc_test/mCc_test_utils.h"

/*===========================================================================
 * program tests*/

TEST(TacCfgPrintProgram, PrintProgramFunctionSimple)
{
	/*FILE *fp =
	    open_file(DOT_OUTPUT_DIR, DOT_PREFIX, file_name, DOT_FILE_SUFFIX);
	mCc_ast_print_dot_expression(fp, expr);

	fclose(fp);
	/*struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(
	        MCC_AST_DATA_TYPE_BOOL, "my_bool_function",
	        mCc_test_build_test_lit_expression_bool(true));

	struct mCc_ast_program *program = mCc_ast_new_program(function_def);

	struct mCc_tac_element *tac = mCc_tac_start_program(program);
	struct mCc_tac_cfg_element *cfg = mCc_tac_cfg_generate(tac);*/
	// mCc_tac_cfg_print(out_put, cfg);

	// test_print_and_free_ast_program(program, "PrintProgramFunctionSimple");
}

TEST(TacCfgPrintProgram, PrintProgramFunctionConcated)
{
	/*struct mCc_ast_function_def *function_def_1 =
	    mCc_test_build_test_function_def(
	        MCC_AST_DATA_TYPE_BOOL, "my_bool_function",
	        mCc_test_build_test_lit_expression_bool(true));

	struct mCc_ast_function_def *function_def_2 =
	    mCc_test_build_test_function_def(MCC_AST_DATA_TYPE_VOID,
	                                     "my_void_function", NULL);

	struct mCc_ast_function_def *function_def_3 =
	    mCc_test_build_test_function_def(
	        MCC_AST_DATA_TYPE_INT, "my_int_function",
	        mCc_test_build_test_lit_expression(10));

	// concat
	function_def_2->next_function_def = function_def_3;
	function_def_1->next_function_def = function_def_2;

	struct mCc_ast_program *program = mCc_ast_new_program(function_def_1);

	test_print_and_free_ast_program(program, "PrintProgramFunctionConcated");*/
}
