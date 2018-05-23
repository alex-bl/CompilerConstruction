#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "mCc/ast.h"
#include "mCc/parser.h"
#include "mCc_test/mCc_test_utils.h"
#include "parser_helper.h"
#include "symtab_check.h"
#include "symtab_error_print.h"

static struct mCc_ast_assignment *find_assignment(struct mCc_ast_program *entry)
{
	return entry->first_function_def->first_statement->next_statement
	    ->assignment;
}

static struct mCc_ast_assignment *
find_assignment_sec_fct(struct mCc_ast_program *entry)
{
	return entry->first_function_def->next_function_def->first_statement
	    ->next_statement->assignment;
}

static struct mCc_ast_assignment *
find_next_assignment(struct mCc_ast_program *entry)
{
	return entry->first_function_def->first_statement->next_statement
	    ->next_statement->assignment;
}

static struct mCc_ast_statement *
find_first_statement(struct mCc_ast_program *entry)
{
	return entry->first_function_def->first_statement;
}

static struct mCc_ast_assignment *
find_assignment_function_call(struct mCc_ast_program *entry)
{
	return entry->first_function_def->next_function_def->first_statement
	    ->next_statement->assignment;
}

//============================================ Main presence/absence
TEST(SemanticChecks, MainPresence)
{
	const char *simple_main = "void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, MainAbsence)
{
	const char *simple_main = "void main_not_valid(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	ASSERT_TRUE(simple_prog->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_NO_MAIN,
	          simple_prog->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidMainSignature)
{
	const char *simple_main = "int main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	ASSERT_TRUE(simple_prog->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_SIGNATURE,
	          simple_prog->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidMainSignatureParams)
{
	const char *simple_main = "void main(int a){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	ASSERT_TRUE(simple_prog->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_SIGNATURE,
	          simple_prog->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

//============================================ Identifier

TEST(SemanticChecks, IdentifierNoDef)
{
	const char *simple_main = "void main(){int a; a=not_defined();}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));

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

//============================================ Identifier

TEST(SemanticChecks, IdentifierAlreadyDefined)
{
	const char *simple_main = "void main(){int a; int a;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));

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

//============================================ Assignment

TEST(SemanticChecks, InvalidPrimitiveAssignment)
{
	const char *simple_main = "void main(){int a; a=false;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *invalid_assignment =
	    find_assignment(simple_prog);
	ASSERT_TRUE(invalid_assignment != NULL);
	ASSERT_TRUE(invalid_assignment->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE,
	          invalid_assignment->semantic_error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidArrayAssignment)
{
	const char *simple_main = "void main(){int[10] a; a[3] =\"2\";}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *invalid_assignment =
	    find_assignment(simple_prog);
	ASSERT_TRUE(invalid_assignment != NULL);
	ASSERT_TRUE(invalid_assignment->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE,
	          invalid_assignment->semantic_error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidAssignmentToArray)
{
	const char *simple_main = "void main(){int[10] a; a=2;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *invalid_assignment =
	    find_assignment(simple_prog);
	ASSERT_TRUE(invalid_assignment != NULL);

	ASSERT_TRUE(invalid_assignment->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_ASSIGNMENT,
	          invalid_assignment->semantic_error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

//============================================ Expression (type setting)

TEST(SemanticChecks, ExpressionSetTypeLiteral)
{

	const char *simple_main = "void main(){int a; a=2;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_assignment(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_INT,
	          assignment->assigned_expression->data_type);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ExpressionSetTypeParenth)
{
	const char *simple_main = "void main(){int a; a=(2+2);}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_assignment(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_INT,
	          assignment->assigned_expression->data_type);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ExpressionSetTypeBinary)
{
	const char *simple_main = "void main(){int a; a=2*3;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_assignment(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_INT,
	          assignment->assigned_expression->data_type);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ExpressionSetTypeBinaryBool)
{
	const char *simple_main = "void main(){bool a; a=(2>=3);}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_assignment(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL,
	          assignment->assigned_expression->data_type);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ExpressionSetTypeUnary)
{
	const char *simple_main = "void main(){bool a; a=!false;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_assignment(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL,
	          assignment->assigned_expression->data_type);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ExpressionSetTypeIdentifier)
{
	const char *simple_main = "void main(){bool a; bool b; b=!a;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_statement *first_stmt = find_first_statement(simple_prog);
	struct mCc_ast_assignment *assignment =
	    first_stmt->next_statement->next_statement->assignment;

	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL,
	          assignment->assigned_expression->data_type);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ExpressionSetTypeFunctionCall)
{
	const char *simple_main =
	    "string bo(){return \"1\";} void main(){string a; a=bo();}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment =
	    find_assignment_function_call(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_STRING,
	          assignment->assigned_expression->data_type);
	mCc_ast_delete_program(simple_prog);
}

//============================================ Expression (validation)

TEST(SemanticChecks, InvalidParentExpression)
{
	const char *simple_main = "void main(){int a; a=(2+2.1);}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_assignment(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_INCONSISTENT,
	          assignment->assigned_expression->data_type);

	struct mCc_validation_status_result *error =
	    assignment->assigned_expression->expression->semantic_error;
	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE, error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidBinaryExpression)
{
	const char *simple_main = "void main(){int a; a=2*\"3\";}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_assignment(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_INCONSISTENT,
	          assignment->assigned_expression->data_type);

	struct mCc_validation_status_result *error =
	    assignment->assigned_expression->semantic_error;
	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE, error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidUnaryOp)
{
	const char *simple_main = "void main(){bool a; a=!3;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_assignment(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_INCOMPATIBLE,
	          assignment->assigned_expression->data_type);

	struct mCc_validation_status_result *error =
	    assignment->assigned_expression->semantic_error;
	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE, error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidUnaryOpIdentifier)
{
	const char *simple_main = "void main(){bool a; int b; b=!a;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_statement *first_stmt = find_first_statement(simple_prog);
	struct mCc_ast_assignment *assignment =
	    first_stmt->next_statement->next_statement->assignment;

	ASSERT_EQ(MCC_AST_DATA_TYPE_BOOL,
	          assignment->assigned_expression->data_type);

	struct mCc_validation_status_result *error = assignment->semantic_error;
	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE, error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidExpressionFunctionCallUnknown)
{
	const char *simple_main =
	    "string bo(){return \"1\";} void main(){string a; a=bo_unknown();}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment =
	    find_assignment_function_call(simple_prog);

	ASSERT_EQ(MCC_AST_DATA_TYPE_UNKNOWN,
	          assignment->assigned_expression->data_type);

	struct mCc_validation_status_result *error =
	    assignment->assigned_expression->function_call->identifier
	        ->semantic_error;
	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_NO_DEF, error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidArrayAssignmentIndex)
{
	const char *simple_main = "void main(){int[10] a; a[3.14]=2;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *invalid_assignment =
	    find_assignment(simple_prog);
	ASSERT_TRUE(invalid_assignment != NULL);

	ASSERT_TRUE(invalid_assignment->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE,
	          invalid_assignment->semantic_error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidIdentifierExpressionArray)
{
	const char *simple_main = "void main(){int[10] a; int c; c=a+2;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment = find_next_assignment(simple_prog);
	ASSERT_TRUE(assignment != NULL);

	ASSERT_TRUE(assignment->assigned_expression->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_EXPR_IDENTIFIER,
	          assignment->assigned_expression->lhs->semantic_error
	              ->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidIdentifierExpressionFunction)
{
	const char *simple_main =
	    "int ret_int(){return 1;} void main(){int a; a=ret_int;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment =
	    find_assignment_sec_fct(simple_prog);
	ASSERT_TRUE(assignment != NULL);

	ASSERT_TRUE(assignment->assigned_expression->semantic_error != NULL);
	ASSERT_EQ(
	    MCC_VALIDATION_STATUS_INVALID_EXPR_IDENTIFIER,
	    assignment->assigned_expression->semantic_error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidIdentifierExpressionFunctionArr)
{
	const char *simple_main =
	    "int ret_int(){return 1;} void main(){int a; a=ret_int[2];}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment =
	    find_assignment_sec_fct(simple_prog);
	ASSERT_TRUE(assignment != NULL);

	ASSERT_TRUE(assignment->assigned_expression->semantic_error != NULL);
	ASSERT_EQ(
	    MCC_VALIDATION_STATUS_INVALID_EXPR_IDENTIFIER,
	    assignment->assigned_expression->semantic_error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

//============================================ Function (definition)

TEST(SemanticChecks, FunctionNoReturnVoid)
{
	const char *simple_main = "void my_void_func(){} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionEmptyReturnVoid)
{
	const char *simple_main = "void my_void_func(){return;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidFunctionReturnVoid)
{
	const char *simple_main = "void invalid_return(){return 1;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_function_def *invalid_function_def =
	    simple_prog->first_function_def;

	ASSERT_TRUE(invalid_function_def != NULL);
	ASSERT_TRUE(invalid_function_def->first_statement != NULL);

	struct mCc_validation_status_result *error =
	    invalid_function_def->first_statement->semantic_error;

	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_RETURN, error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidFunctionMissingReturn)
{
	const char *simple_main = "int invalid_return(){} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_function_def *invalid_function_def =
	    simple_prog->first_function_def;

	ASSERT_TRUE(invalid_function_def != NULL);

	struct mCc_validation_status_result *error =
	    invalid_function_def->semantic_error;

	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_RETURN, error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidFunctionEmptyReturn)
{
	const char *simple_main = "int invalid_return(){return;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_function_def *invalid_function_def =
	    simple_prog->first_function_def;

	ASSERT_TRUE(invalid_function_def != NULL);
	ASSERT_TRUE(invalid_function_def->first_statement != NULL);

	struct mCc_validation_status_result *error =
	    invalid_function_def->first_statement->semantic_error;

	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_RETURN, error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidFunctionReturnNonVoid)
{
	const char *simple_main = "float invalid_return(){return 1;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_function_def *invalid_function_def =
	    simple_prog->first_function_def;

	ASSERT_TRUE(invalid_function_def != NULL);
	ASSERT_TRUE(invalid_function_def->first_statement != NULL);

	struct mCc_validation_status_result *error =
	    invalid_function_def->first_statement->semantic_error;

	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_RETURN, error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefSimpleReturnValid)
{
	const char *simple_main = "int my_void_func(){return 1;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefForwardDeclaration)
{
	const char *simple_main = "int my_void_func(){return 1;} void main(){int "
	                          "a; int b; a=my_void_func(); "
	                          "b=my_void_func_2();} int "
	                          "my_void_func_2(){return 1;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefForwardDeclarationNested)
{
	const char *simple_main =
	    "int my_void_func(){return my_void_func_2();} void main(){int "
	    "a;  a=my_void_func();} int my_void_func_2(){return 1;}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefSimpleVoidReturnValid)
{
	const char *simple_main =
	    "void my_void_func(){if(1==2){return;}} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefModerateVoidReturnValid)
{
	const char *simple_main =
	    "void my_void_func(){if(1==2){return;} return;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefIfReturnValid)
{
	const char *simple_main =
	    "int my_void_func(){if(1==1){return 1;} return 2;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefIfElseReturnValid)
{
	const char *simple_main =
	    "int my_void_func(){if(1==1){return 1;} else{return 2;}} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefWhileReturnValid)
{
	const char *simple_main =
	    "int my_void_func(){while(1==1){return 1;} return 2;} void main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefIfElseNestedReturnValid)
{
	const char *simple_main =
	    "int my_void_func(){if(1==1){if(1==1){return "
	    "1;}else{return 2;}} else{if(1==1){return 2;}else{return 3;}}} void "
	    "main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefIfInvalid)
{
	const char *simple_main = "int my_void_func(){if(1==1){return 2;}} void "
	                          "main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));

	struct mCc_ast_statement *erroneous_stmt =
	    simple_prog->first_function_def->first_statement;

	ASSERT_TRUE(erroneous_stmt != NULL);
	ASSERT_TRUE(erroneous_stmt->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_MISSING_RETURN_PATH,
	          erroneous_stmt->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefIfVoidInvalid)
{
	const char *simple_main =
	    "void my_void_func(){if(1==1){return 2;} return;} void "
	    "main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));

	struct mCc_ast_statement *erroneous_stmt =
	    simple_prog->first_function_def->first_statement->if_statement;

	ASSERT_TRUE(erroneous_stmt != NULL);
	ASSERT_TRUE(erroneous_stmt->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_RETURN,
	          erroneous_stmt->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefIfElseNestedReturnInValid)
{
	const char *simple_main =
	    "int my_void_func(){if(1==1){if(1==1){return "
	    "1;}else{return 2;}} else{if(1==1){return 2;}else{}}} void "
	    "main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, FunctionDefIfInvalidElsePath)
{
	const char *simple_main =
	    "int my_void_func(){if(1==1){return 2;} else{return true;}} void "
	    "main(){}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));

	struct mCc_ast_statement *erroneous_stmt =
	    simple_prog->first_function_def->first_statement->else_statement;

	ASSERT_TRUE(erroneous_stmt != NULL);
	ASSERT_TRUE(erroneous_stmt->semantic_error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_RETURN,
	          erroneous_stmt->semantic_error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

//============================================ Function (call)

TEST(SemanticChecks, InvalidFunctionCallSignature)
{
	const char *simple_main =
	    "string bo(){return \"1\";} void main(){string a; a=bo(2);}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment =
	    find_assignment_function_call(simple_prog);

	ASSERT_TRUE(assignment != NULL);

	struct mCc_validation_status_result *error =
	    assignment->assigned_expression->function_call->semantic_error;

	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_SIGNATURE,
	          error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidFunctionCallType)
{
	const char *simple_main = "string bo(int a, float b){return \"1\";} void "
	                          "main(){string a; a=bo(2,2);}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_assignment *assignment =
	    find_assignment_function_call(simple_prog);

	ASSERT_TRUE(assignment != NULL);

	struct mCc_validation_status_result *error =
	    assignment->assigned_expression->function_call->semantic_error;

	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_PARAMETER,
	          error->validation_status);
	mCc_ast_delete_program(simple_prog);
}

//============================================ Statement

TEST(SemanticChecks, InvalidIfStatement)
{
	const char *simple_main = "void main(){if(3){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_statement *first_stmt = find_first_statement(simple_prog);

	ASSERT_TRUE(first_stmt != NULL);

	struct mCc_validation_status_result *error = first_stmt->semantic_error;
	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE, error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidIfStatementAdvanced)
{
	const char *simple_main = "void main(){if(3+4*6-8){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_statement *first_stmt = find_first_statement(simple_prog);

	ASSERT_TRUE(first_stmt != NULL);

	struct mCc_validation_status_result *error = first_stmt->semantic_error;
	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE, error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, InvalidWhileStatement)
{
	const char *simple_main = "void main(){while(3){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_NE(0, mCc_symtab_perform_semantic_checks(simple_prog));
	struct mCc_ast_statement *first_stmt = find_first_statement(simple_prog);

	ASSERT_TRUE(first_stmt != NULL);

	struct mCc_validation_status_result *error = first_stmt->semantic_error;
	ASSERT_TRUE(error != NULL);
	ASSERT_EQ(MCC_VALIDATION_STATUS_INVALID_TYPE, error->validation_status);

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ValidWhileStatementAdvancedCondition)
{
	const char *simple_main = "void main(){while(3>=2){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ValidWhileStatementAdvancedBooleanCondition)
{
	const char *simple_main = "void main(){if((3>=2) || (4!=3)){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ValidIfStatementSimpleBooleanCondition)
{
	const char *simple_main = "void main(){bool a; bool b; if(a && b){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ValidIfStatementFunctionCall)
{
	const char *simple_main =
	    "bool is_valid(){return true;} void main(){if(is_valid()){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ValidIfStatementArray)
{
	const char *simple_main = "bool is_valid(){return true;} void "
	                          "main(){bool[3] arr; if(arr[3]==true){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ValidNegUnaryOp)
{
	const char *simple_main = "bool is_valid(){int a; a=-3; return true;} void "
	                          "main(){bool[3] arr; if(arr[3]==true){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ValidIfStatementArrayInvalid)
{
	const char *simple_main = "bool is_valid(){return true;} void "
	                          "main(){bool[3] arr; if(arr[3]==\"2\"){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(1, mCc_symtab_perform_semantic_checks(simple_prog));

	mCc_ast_delete_program(simple_prog);
}

TEST(SemanticChecks, ValidIfStatementFunctionCallMultipleStatements)
{
	const char *simple_main = "bool is_valid(){int a; int b; string c; return "
	                          "true;} void main(){if(is_valid()){}}";
	struct mCc_parser_result result = mCc_parser_parse_string(simple_main);

	ASSERT_EQ(MCC_PARSER_TOP_LEVEL_PROGRAM, result.top_level_type);
	ASSERT_TRUE(&(result.program) != NULL);
	struct mCc_ast_program *simple_prog = result.program;

	ASSERT_EQ(0, mCc_symtab_perform_semantic_checks(simple_prog));

	mCc_ast_delete_program(simple_prog);
}
