#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "assembly_arithmetic_op.h"
#include "assembly_data.h"
#include "assembly_offset.h"
#include "assembly_utils.h"
#include "basic_tac.h"
#include "config.h"
#include "mCc/ast.h"
#include "mCc/parser.h"
#include "mCc/semantic_check.h"
#include "mCc/tac.h"
#include "mCc_test/mCc_test_utils.h"
#include "parser_helper.h"

struct mCc_tac_element *build_test_tac_elem(char *name)
{
	struct mCc_tac_identifier *result_identifier = tac_new_identifier(name);
	struct mCc_tac_element *tac_element =
	    tac_new_element(MCC_TAC_OPARATION_EMPTY, NULL, NULL, result_identifier,
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	return tac_element;
}

static struct mCc_tac_identifier *build_test_identifier(char *name,
                                                        int stack_offset)
{
	struct mCc_tac_identifier *identifier = tac_new_identifier(name);
	identifier->stack_offset = stack_offset;
	return identifier;
}

static struct mCc_tac_identifier *
get_tac_arg_1(struct mCc_tac_element *tac_element)
{
	return tac_element->tac_argument1;
}

static struct mCc_tac_identifier *
get_tac_result(struct mCc_tac_element *tac_element)
{
	return tac_element->tac_result;
}

static struct mCc_tac_identifier *
get_tac_element_identifier(struct mCc_tac_element *start_element,
                           int nr_of_element,
                           struct mCc_tac_identifier *get_identifier(
                               struct mCc_tac_element *tac_element))
{
	struct mCc_tac_element *next_element = start_element;
	int i = 0;

	while (next_element) {
		if (nr_of_element == i) {
			return get_identifier(next_element);
		}
		i++;
		next_element = next_element->tac_next_element;
	}

	return NULL;
}

//==================================================== Assembly utils
TEST(AssemblyUtils, CalcIntSpace)
{
	size_t expected = 8;
	ASSERT_EQ(expected, mCc_assembly_calc_int_space(2));
}

TEST(AssemblyUtils, CalcBoolSpace)
{
	size_t expected = 8;
	ASSERT_EQ(expected, mCc_assembly_calc_bool_space(2));
}

TEST(AssemblyUtils, CalcFloatSpace)
{
	size_t expected = 8;
	ASSERT_EQ(expected, mCc_assembly_calc_float_space(2));
}

TEST(AssemblyUtils, CalcStringSpace)
{
	size_t expected = 8;
	ASSERT_EQ(expected, mCc_assembly_calc_string_space(NULL));
}

TEST(AssemblyUtils, CalcParamSpace)
{
	char name[] = "test";
	struct mCc_tac_element *test_elem = build_test_tac_elem(name);
	size_t expected = 0;
	ASSERT_EQ(expected, mCc_assembly_calc_param_space(test_elem));
	mCc_tac_element_delete(test_elem);
}

TEST(AssemblyUtils, CalcStackPosParam)
{
	char name[] = "test";
	struct mCc_tac_identifier *test_identifier = build_test_identifier(name, 8);
	ASSERT_EQ(8, mCc_assembly_calc_stack_pos_param(test_identifier));
	mCc_tac_delete_identifier(test_identifier);
}

TEST(AssemblyUtils, GetStackPosLocalVar)
{
	char name[] = "test";
	struct mCc_tac_identifier *test_identifier = build_test_identifier(name, 4);
	test_identifier->is_param = false;
	ASSERT_EQ(-4, mCc_assembly_calc_stack_position(test_identifier, 0));
	mCc_tac_delete_identifier(test_identifier);
}

TEST(AssemblyUtils, GetStackPosParam)
{
	char name[] = "test";
	struct mCc_tac_identifier *test_identifier = build_test_identifier(name, 8);
	test_identifier->is_param = true;
	ASSERT_EQ(8, mCc_assembly_calc_stack_position(test_identifier, 0));
	mCc_tac_delete_identifier(test_identifier);
}

TEST(AssemblyUtils, GetNextFunctionLabel)
{
	char name[] = "first_func";
	struct mCc_tac_identifier *result_identifier =
	    build_test_identifier(name, 4);

	struct mCc_tac_element *tac_element = tac_new_element(
	    MCC_TAC_OPARATION_EMPTY, NULL, NULL, NULL, MCC_TAC_TYPE_NO_TYPE, 0);

	struct mCc_tac_element *tac_element_label =
	    tac_new_element(MCC_TAC_OPARATION_LABEL_FUNCTION, NULL, NULL,
	                    result_identifier, MCC_TAC_TYPE_NO_TYPE, 0);

	mCc_tac_connect_tac_entry(tac_element, tac_element_label);

	ASSERT_STREQ("first_func",
	             mCc_assembly_get_next_function_label(tac_element));
	mCc_tac_delete(tac_element);
}

TEST(AssemblyUtils, AdjustStackPointer)
{
	struct mCc_assembly_data assembly_data;
	assembly_data.current_stack_pos = 0;
	mCc_assembly_adjust_stack_pointer(4, &assembly_data);
	ASSERT_EQ(4, assembly_data.current_stack_pos);
}

TEST(AssemblyUtils, CreateNewArgListElement)
{
	struct mCc_assembly_argument_list *elem =
	    mCc_assembly_create_new_arg_list_elem(0);

	ASSERT_TRUE(elem != NULL);
	ASSERT_EQ(0, elem->open_scope);
	ASSERT_TRUE(elem->next == NULL);

	mCc_assembly_free_arg_list_elem(elem);
}

TEST(AssemblyUtils, PrependArgListElementEmptyHead)
{
	char name[] = "test";
	struct mCc_tac_element *tac_elem = build_test_tac_elem(name);

	struct mCc_assembly_argument_list *new_head =
	    mCc_assembly_prepend_arg_list_elem(NULL, tac_elem, 0);

	ASSERT_TRUE(new_head != NULL);
	ASSERT_EQ(0, new_head->open_scope);
	ASSERT_TRUE(new_head->next == NULL);

	mCc_assembly_free_arg_list_elem(new_head);
	mCc_tac_element_delete(tac_elem);
}

TEST(AssemblyUtils, PrependArgListElementExistingHead)
{

	struct mCc_assembly_argument_list *old_head =
	    mCc_assembly_create_new_arg_list_elem(0);

	ASSERT_TRUE(old_head != NULL);

	char name[] = "test";
	struct mCc_tac_element *tac_elem = build_test_tac_elem(name);

	struct mCc_assembly_argument_list *new_head =
	    mCc_assembly_prepend_arg_list_elem(old_head, tac_elem, 0);

	ASSERT_TRUE(new_head != NULL);
	ASSERT_EQ(0, new_head->open_scope);
	ASSERT_TRUE(new_head->next == old_head);

	mCc_assembly_free_arg_list_elem(new_head);
	mCc_assembly_free_arg_list_elem(old_head);

	mCc_tac_element_delete(tac_elem);
}

TEST(AssemblyUtils, FreeArgListElement)
{
	struct mCc_assembly_argument_list *elem =
	    mCc_assembly_create_new_arg_list_elem(0);
	mCc_assembly_free_arg_list_elem(elem);
}

//==================================================== Assembly offset

TEST(AssemblyOffset, Simple)
{
	//======================== setup
	const char *simple_main = "void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(simple_prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(simple_prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *function_label =
	    get_tac_element_identifier(tac, 1, get_tac_result);
	ASSERT_TRUE(function_label != NULL);
	ASSERT_EQ(0, function_label->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(simple_prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, SimpleVar)
{
	//======================== setup
	const char *simple_main = "void main(){int a;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(simple_prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(simple_prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *declaration =
	    get_tac_element_identifier(tac, 3, get_tac_result);
	ASSERT_TRUE(declaration != NULL);
	ASSERT_EQ(4, declaration->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(simple_prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, MoreVars)
{
	//======================== setup
	const char *prog_to_parse = "void main(){int a; int b;}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *declaration =
	    get_tac_element_identifier(tac, 4, get_tac_result);
	ASSERT_TRUE(declaration != NULL);
	ASSERT_EQ(8, declaration->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, ArraySimple)
{
	//======================== setup
	const char *prog_to_parse = "void main(){int[100] a;}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *declaration =
	    get_tac_element_identifier(tac, 3, get_tac_result);
	ASSERT_TRUE(declaration != NULL);
	ASSERT_EQ(400, declaration->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, ArrayWithVar)
{
	//======================== setup
	const char *prog_to_parse = "void main(){int[100] a; int b;}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *declaration =
	    get_tac_element_identifier(tac, 4, get_tac_result);
	ASSERT_TRUE(declaration != NULL);
	ASSERT_EQ(404, declaration->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, MultipleArrays)
{
	//======================== setup
	const char *prog_to_parse = "void main(){int[100] a; int[100] b;}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *declaration =
	    get_tac_element_identifier(tac, 4, get_tac_result);
	ASSERT_TRUE(declaration != NULL);
	ASSERT_EQ(800, declaration->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, ParamSimple)
{
	//======================== setup
	const char *prog_to_parse = "void test(int a){} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *param =
	    get_tac_element_identifier(tac, 3, get_tac_arg_1);
	ASSERT_TRUE(param != NULL);
	ASSERT_EQ(8, param->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, ParamMultiple)
{
	//======================== setup
	const char *prog_to_parse = "void test(int a, int b){} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *param =
	    get_tac_element_identifier(tac, 4, get_tac_arg_1);
	ASSERT_TRUE(param != NULL);
	ASSERT_EQ(12, param->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, ParamArray)
{
	//======================== setup
	const char *prog_to_parse =
	    "void test(bool d, int[100] b, int a){} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *param =
	    get_tac_element_identifier(tac, 4, get_tac_arg_1);
	ASSERT_TRUE(param != NULL);
	ASSERT_EQ(12, param->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, ParamAfterArray)
{
	//======================== setup
	const char *prog_to_parse =
	    "void test(int c, bool d, int[100] b, int a){} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *param =
	    get_tac_element_identifier(tac, 6, get_tac_arg_1);
	ASSERT_TRUE(param != NULL);
	ASSERT_EQ(20, param->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, LocalVarWithParam)
{
	//======================== setup
	const char *prog_to_parse = "void test(int c){int a;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *param =
	    get_tac_element_identifier(tac, 4, get_tac_result);
	ASSERT_TRUE(param != NULL);
	ASSERT_EQ(4, param->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, LocalVarSecondFunction)
{
	//======================== setup
	const char *prog_to_parse = "void test(){int a;} void main(){int a;}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *param =
	    get_tac_element_identifier(tac, 7, get_tac_result);
	ASSERT_TRUE(param != NULL);
	ASSERT_EQ(4, param->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}

TEST(AssemblyOffset, LocalSecondVarSecondFunction)
{
	//======================== setup
	const char *prog_to_parse = "void test(){int a;} void main(){int a; bool b;}";
	struct mCc_parser_result result = mCc_parser_parse_string(prog_to_parse);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *prog = result.program;
	int nr_of_semantic_errors = mCc_symtab_perform_semantic_checks(prog);
	ASSERT_EQ(0, nr_of_semantic_errors);

	struct mCc_tac_element *tac = mCc_tac_start_program(prog);
	ASSERT_TRUE(tac != NULL);
	mCc_assembly_calculate_stack_offsets(tac);
	//======================== test

	struct mCc_tac_identifier *param =
	    get_tac_element_identifier(tac, 8, get_tac_result);
	ASSERT_TRUE(param != NULL);
	ASSERT_EQ(8, param->stack_offset);

	//======================== cleanup
	mCc_ast_delete_program(prog);
	mCc_tac_delete(tac);
}
