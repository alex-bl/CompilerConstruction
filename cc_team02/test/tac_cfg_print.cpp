#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "basic_tac.h"
#include "config.h"
#include "mCc/ast.h"
#include "mCc/parser.h"
#include "mCc/semantic_check.h"
#include "mCc/tac.h"
#include "mCc_test/mCc_test_utils.h"
//#include "parser_helper.h"
#include "mCc/tac_cfg_print.h"

/*===========================================================================
 * program tests*/

TEST(TacCfgPrintFunction, PrintCFGSimpleFunction)
{

	struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(
	        MCC_AST_DATA_TYPE_BOOL, "my_bool_function",
	        mCc_test_build_test_lit_expression_bool(true));

	struct mCc_ast_program *program = mCc_ast_new_program(function_def);

	struct mCc_tac_element *tac = mCc_tac_start_program(program);
	struct mCc_tac_cfg_element *cfg = mCc_tac_cfg_generate(tac);

	FILE *fp = open_file(CFG_DOT_TEST_OUTPUT_DIR, DOT_PREFIX,
	                     "PrintCFGSimpleFunction", DOT_FILE_SUFFIX);
	mCc_tac_cfg_print(fp, cfg);
	fclose(fp);
}

TEST(TacCfgPrintFunction, PrintCFGFunction)
{
	//======================== setup
	const char *prog_to_parse =
	    "void test(){int a;} void main(){int a; bool b;}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);

	struct mCc_tac_cfg_element *cfg = mCc_tac_cfg_generate(tac);
	// mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	FILE *fp = open_file(CFG_DOT_TEST_OUTPUT_DIR, DOT_PREFIX,
	                     "PrintCFGFunction", DOT_FILE_SUFFIX);
	mCc_tac_cfg_print(fp, cfg);
	fclose(fp);

	/*struct mCc_tac_identifier *param =
	    get_tac_element_identifier(tac, 8, get_tac_result);
	ASSERT_TRUE(param != NULL);
	ASSERT_EQ(8, param->stack_offset);*/

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}
