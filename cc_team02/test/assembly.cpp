#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "assembly_arithmetic_op.h"
#include "basic_tac.h"
#include "config.h"
#include "mCc/ast.h"
#include "mCc/parser.h"
#include "mCc/tac.h"
#include "mCc_test/mCc_test_utils.h"
#include "parser_helper.h"

static FILE *build_assembly_file(const char *file_name)
{
	return open_file(ASSEMBLY_TEST_OUTPUT_DIR, ASSEMBLY_PREFIX, file_name,
	                 ASSEMBLY_FILE_SUFFIX);
}

static void close_assembly_file(FILE *file)
{
	fclose(file);
}

static struct mCc_tac_identifier *test_build_tac_identifier(char *name,
                                                            int offset)
{
	struct mCc_tac_identifier *result = tac_new_identifier(name);
	result->stack_offset = offset;
	return result;
}

static struct mCc_tac_element *
generate_literal_int_tac_binary_op(enum mCc_tac_operation operation,
                                   int lhs_val, int rhs_val, int offset)
{
	struct mCc_tac_identifier *lhs = tac_new_identifier_int(lhs_val);
	struct mCc_tac_identifier *rhs = tac_new_identifier_int(rhs_val);
	char name[] = "t0";
	struct mCc_tac_identifier *result = test_build_tac_identifier(name, offset);
	struct mCc_tac_element *binary_op =
	    tac_new_element(operation, lhs, rhs, result, MCC_TAC_TYPE_INTEGER, 0);

	return binary_op;
}

static struct mCc_tac_element *
generate_var_int_tac_binary_op(enum mCc_tac_operation operation)
{
	char lhs_name[] = "t0";
	char rhs_name[] = "t1";
	char result_name[] = "t2";

	struct mCc_tac_identifier *lhs = test_build_tac_identifier(lhs_name, 4);
	struct mCc_tac_identifier *rhs = test_build_tac_identifier(rhs_name, 8);
	struct mCc_tac_identifier *result =
	    test_build_tac_identifier(result_name, 12);

	struct mCc_tac_element *binary_op =
	    tac_new_element(operation, lhs, rhs, result, MCC_TAC_TYPE_INTEGER, 0);

	return binary_op;
}

static struct mCc_tac_element *
generate_misc_int_tac_binary_op(enum mCc_tac_operation operation)
{
	char lhs_name[] = "t0";
	char result_name[] = "t2";

	struct mCc_tac_identifier *lhs = test_build_tac_identifier(lhs_name, 4);
	struct mCc_tac_identifier *rhs = tac_new_identifier_int(24);
	struct mCc_tac_identifier *result =
	    test_build_tac_identifier(result_name, 8);

	struct mCc_tac_element *binary_op =
	    tac_new_element(operation, lhs, rhs, result, MCC_TAC_TYPE_INTEGER, 0);

	return binary_op;
}

static void test_int_arithmetic_op_literals(
    const char *output_file, struct mCc_tac_element *tac_element,
    void(generation_fct)(FILE *out, struct mCc_tac_element *tac_elem))
{
	FILE *fp = build_assembly_file(output_file);
	generation_fct(fp, tac_element);
	mCc_tac_delete(tac_element);
	close_assembly_file(fp);
}

TEST(AssemblyGeneration, AddIntegerLiterals)
{
	struct mCc_tac_element *binary_op = generate_literal_int_tac_binary_op(
	    MCC_TAC_OPARATION_BINARY_OP_ADD_INT, 10, 20, 4);

	test_int_arithmetic_op_literals("add_int_literals", binary_op,
	                                mCc_assembly_generate_add_int);
}

TEST(AssemblyGeneration, AddIntegerVariables)
{
	struct mCc_tac_element *binary_op =
	    generate_var_int_tac_binary_op(MCC_TAC_OPARATION_BINARY_OP_ADD_INT);

	test_int_arithmetic_op_literals("add_int_var", binary_op,
	                                mCc_assembly_generate_add_int);
}

TEST(AssemblyGeneration, AddIntegerMisc)
{
	struct mCc_tac_element *binary_op =
	    generate_misc_int_tac_binary_op(MCC_TAC_OPARATION_BINARY_OP_ADD_INT);

	test_int_arithmetic_op_literals("add_int_misc", binary_op,
	                                mCc_assembly_generate_add_int);
}

TEST(AssemblyGeneration, SubIntegerLiterals)
{
	struct mCc_tac_element *binary_op = generate_literal_int_tac_binary_op(
	    MCC_TAC_OPARATION_BINARY_OP_SUB_INT, 10, 20, 4);

	test_int_arithmetic_op_literals("sub_int_literals", binary_op,
	                                mCc_assembly_generate_sub_int);
}

TEST(AssemblyGeneration, SubIntegerVariables)
{
	struct mCc_tac_element *binary_op =
	    generate_var_int_tac_binary_op(MCC_TAC_OPARATION_BINARY_OP_SUB_INT);

	test_int_arithmetic_op_literals("sub_int_var", binary_op,
	                                mCc_assembly_generate_sub_int);
}

TEST(AssemblyGeneration, SubIntegerMisc)
{
	struct mCc_tac_element *binary_op =
	    generate_misc_int_tac_binary_op(MCC_TAC_OPARATION_BINARY_OP_SUB_INT);

	test_int_arithmetic_op_literals("sub_int_misc", binary_op,
	                                mCc_assembly_generate_sub_int);
}

TEST(AssemblyGeneration, MulIntegerLiterals)
{
	struct mCc_tac_element *binary_op = generate_literal_int_tac_binary_op(
	    MCC_TAC_OPARATION_BINARY_OP_MUL_INT, 10, 20, 4);

	test_int_arithmetic_op_literals("mul_int_literals", binary_op,
	                                mCc_assembly_generate_mul_int);
}

TEST(AssemblyGeneration, MulIntegerVariables)
{
	struct mCc_tac_element *binary_op =
	    generate_var_int_tac_binary_op(MCC_TAC_OPARATION_BINARY_OP_MUL_INT);

	test_int_arithmetic_op_literals("mul_int_var", binary_op,
	                                mCc_assembly_generate_mul_int);
}

TEST(AssemblyGeneration, MulIntegerMisc)
{
	struct mCc_tac_element *binary_op =
	    generate_misc_int_tac_binary_op(MCC_TAC_OPARATION_BINARY_OP_MUL_INT);

	test_int_arithmetic_op_literals("mul_int_misc", binary_op,
	                                mCc_assembly_generate_mul_int);
}

TEST(AssemblyGeneration, DivIntegerLiterals)
{
	struct mCc_tac_element *binary_op = generate_literal_int_tac_binary_op(
	    MCC_TAC_OPARATION_BINARY_OP_DIV_INT, 10, 20, 4);

	test_int_arithmetic_op_literals("div_int_literals", binary_op,
	                                mCc_assembly_generate_div_int);
}

TEST(AssemblyGeneration, DivIntegerVariables)
{
	struct mCc_tac_element *binary_op =
	    generate_var_int_tac_binary_op(MCC_TAC_OPARATION_BINARY_OP_DIV_INT);

	test_int_arithmetic_op_literals("div_int_var", binary_op,
	                                mCc_assembly_generate_div_int);
}

TEST(AssemblyGeneration, DivIntegerMisc)
{
	struct mCc_tac_element *binary_op =
	    generate_misc_int_tac_binary_op(MCC_TAC_OPARATION_BINARY_OP_DIV_INT);

	test_int_arithmetic_op_literals("div_int_misc", binary_op,
	                                mCc_assembly_generate_div_int);
}
