#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "mCc/ast.h"
#include "mCc/general/parser_helper.h"
#include "mCc/parser.h"
#include "mCc/symtab/symtab_error_print.h"
#include "mCc/symtab_check.h"
#include "mCc_test/mCc_test_utils.h"

//============================================ Main presence/absence
TEST(SemanticChecks, MainPresence)
{
	const char *simple_main = "void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_TRUE(mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, MainAbsence)
{
	const char *simple_main = "void main_not_valid(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_FALSE(mCc_symtab_perform_semantic_checks(simple_prog));
	ASSERT_TRUE(simple_prog->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_NO_MAIN,
	          simple_prog->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

//============================================ Main presence/absence

TEST(SemanticChecks, IdentifierNoDef)
{
	const char *simple_main = "void main(){int a; a=not_defined();}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_FALSE(mCc_symtab_perform_semantic_checks(simple_prog));

	struct mCc_ast_assignment *assignment =
	    simple_prog->first_function_def->first_statement->next_statement
	        ->assignment;
	ASSERT_TRUE(assignment->identifier != NULL);

	struct mCc_ast_identifier *identifier_fct_call =
	    assignment->assigned_expression->function_call->identifier;

	ASSERT_TRUE(identifier_fct_call != NULL);
	ASSERT_TRUE(identifier_fct_call->semantic_error != NULL);

	ASSERT_EQ(MCC_VALIDATION_STATUS_NO_DEF,
	          identifier_fct_call->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, IdentifierAlreadyDefined)
{
	const char *simple_main = "void main(){int a; int a;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_FALSE(mCc_symtab_perform_semantic_checks(simple_prog));

	struct mCc_ast_declaration *duplicate_declaration =
	    simple_prog->first_function_def->first_statement->next_statement
	        ->declaration;

	struct mCc_ast_identifier *identifier_assignment =
	    duplicate_declaration->identifier;

	ASSERT_TRUE(identifier_assignment != NULL);
	ASSERT_TRUE(identifier_assignment->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_NOT_UNIQUE,
	          identifier_assignment->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}
