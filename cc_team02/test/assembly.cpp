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

TEST(AssemblyGeneration, SimpleIntegerAdd)
{
	FILE *fp = build_assembly_file("add_literals");

	struct mCc_tac_identifier *lhs = tac_new_identifier_int(10);
	struct mCc_tac_identifier *rhs = tac_new_identifier_int(20);
	char name[]="t0";
	struct mCc_tac_identifier *result = tac_new_identifier(name);
	result->stack_offset = 4;

	struct mCc_tac_element *binary_op =
	    tac_new_element(MCC_TAC_OPARATION_BINARY_OP_ADD_INT, lhs, rhs, result,
	                    MCC_TAC_TYPE_INTEGER, 0);

	mCc_assembly_generate_add_int(fp, binary_op);

	mCc_tac_delete(binary_op);
	close_assembly_file(fp);
}
