#include "tac_statement.h"

#include <assert.h>

#include "ast_expression.h"
#include "basic_tac.h"
#include "tac_assignment.h"
#include "tac_declaration.h"
#include "tac_expression.h"

struct mCc_tac_element *
helper_get_tac_of_statement(struct mCc_ast_statement *statement,
                            struct mCc_tac_element *previous_tac)
{
	assert(statement);

	struct mCc_tac_element *statement_tac;
	switch (statement->statement_type) {
	case MCC_AST_STATEMENT_IF:
		statement_tac = mCc_tac_statement_if(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_WHILE:
		statement_tac = mCc_tac_statement_while(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_RETURN:
		statement_tac = mCc_tac_statement_return(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_DECLARATION:
		statement_tac = mCc_tac_statement_declaration(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_ASSIGNMENT:
		statement_tac = mCc_tac_statement_assignment(statement, previous_tac);
		break;
	case MCC_AST_STATEMENT_EXPRESSION:
		statement_tac = mCc_tac_statement_expression(statement, previous_tac);
		break;
	}
	// mCc_tac_connect_tac_entry(previous_tac, statement_tac);
	return statement_tac;
}

struct mCc_tac_element *
mCc_tac_statement_if(struct mCc_ast_statement *statement,
                     struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(statement->condition_expression);
	assert(previous_tac);

	// defining lables to jump to
	struct mCc_tac_identifier *lable_before_if =
	    mCc_tac_create_new_lable_identifier();

	struct mCc_tac_identifier *lable_before_else =
	    mCc_tac_create_new_lable_identifier();

	struct mCc_tac_identifier *lable_after_else =
	    mCc_tac_create_new_lable_identifier();

	// setting lable as tac element
	struct mCc_tac_element *tac_lable_before_if =
	    tac_new_element(MCC_TAC_OPARATION_LABEL_IF, NULL, NULL, lable_before_if,
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_lable_before_if);

	struct mCc_tac_element *tac_condition = helper_get_tac_of_expression(
	    statement->condition_expression, tac_lable_before_if);
	previous_tac = tac_condition;

	// jump to else, if condition is false
	struct mCc_tac_element *tac_if_condition = tac_new_element(
	    MCC_TAC_OPARATION_JUMP_NOT_EQUALS,
	    mCc_tac_create_from_tac_identifier(tac_condition->tac_result), NULL,
	    mCc_tac_create_from_tac_identifier(lable_before_else),
	    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_if_condition);

	struct mCc_ast_statement *ast_if_statement = statement->if_statement;
	// take condition as previous tac element, if there is no if statement,
	// otherwise it will be overwritten
	previous_tac = tac_if_condition;
	while (ast_if_statement != NULL) {
		previous_tac =
		    helper_get_tac_of_statement(ast_if_statement, previous_tac);
		ast_if_statement = ast_if_statement->next_statement;
	}

	// jump after else -> if the if is executed the else is skipped
	struct mCc_tac_element *tac_if_condition2 = tac_new_element(
	    MCC_TAC_OPARATION_JUMP,
	    mCc_tac_create_from_tac_identifier(tac_condition->tac_result), NULL,
	    mCc_tac_create_from_tac_identifier(lable_after_else),
	    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_if_condition2);

	struct mCc_tac_element *tac_lable_before_else =
	    tac_new_element(MCC_TAC_OPARATION_LABEL_ELSE, NULL, NULL,
	                    lable_before_else, MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(tac_if_condition2, tac_lable_before_else);

	previous_tac = tac_lable_before_else;
	struct mCc_ast_statement *ast_else_statement = statement->else_statement;
	while (ast_else_statement != NULL) {
		previous_tac =
		    helper_get_tac_of_statement(ast_else_statement, previous_tac);
		ast_else_statement = ast_else_statement->next_statement;
	}

	struct mCc_tac_element *tac_lable_after_else =
	    tac_new_element(MCC_TAC_OPARATION_LABEL_AFTER_ELSE, NULL, NULL,
	                    lable_after_else, MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_lable_after_else);

	return tac_lable_after_else;
}

struct mCc_tac_element *
mCc_tac_statement_while(struct mCc_ast_statement *statement,
                        struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(statement->condition_expression);
	assert(previous_tac);

	// defining lables to jump to
	struct mCc_tac_identifier *lable_before_while =
	    mCc_tac_create_new_lable_identifier();

	struct mCc_tac_identifier *lable_after_while =
	    mCc_tac_create_new_lable_identifier();

	// setting lable as tac element
	struct mCc_tac_element *tac_lable_before_while =
	    tac_new_element(MCC_TAC_OPARATION_LABEL_WHILE, NULL, NULL, lable_before_while,
	                    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_lable_before_while);

	struct mCc_tac_element *tac_condition = helper_get_tac_of_expression(
	    statement->loop_condition_expression, tac_lable_before_while);
	previous_tac = tac_condition;

	// jump after loop if condition is false
	struct mCc_tac_element *tac_loop_condition = tac_new_element(
	    MCC_TAC_OPARATION_JUMP_NOT_EQUALS,
	    mCc_tac_create_from_tac_identifier(tac_condition->tac_result), NULL,
	    mCc_tac_create_from_tac_identifier(lable_after_while),
	    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_loop_condition);

	struct mCc_ast_statement *ast_while_statement = statement->while_statement;
	// take condition as previous tac element, if there is no if statement,
	// otherwise it will be overwritten
	previous_tac = tac_loop_condition;
	while (ast_while_statement != NULL) {
		previous_tac =
		    helper_get_tac_of_statement(ast_while_statement, previous_tac);
		ast_while_statement = ast_while_statement->next_statement;
	}

	// jump after else -> if the if is executed the else is skipped
	struct mCc_tac_element *tac_while_condition2 = tac_new_element(
	    MCC_TAC_OPARATION_JUMP,
	    mCc_tac_create_from_tac_identifier(tac_condition->tac_result), NULL,
	    mCc_tac_create_from_tac_identifier(lable_before_while),
	    MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(previous_tac, tac_while_condition2);

	struct mCc_tac_element *tac_lable_after_while =
	    tac_new_element(MCC_TAC_OPARATION_LABEL_WHILE, NULL, NULL,
	                    lable_after_while, MCC_TAC_TYPE_NO_TYPE, 0);
	mCc_tac_connect_tac_entry(tac_while_condition2, tac_lable_after_while);

	return tac_lable_after_while;
}

enum mCc_tac_operation tac_helper_get_return_tac_operation(
    enum mCc_tac_operation return_expression_operation)
{
	switch (return_expression_operation) {
	case MCC_TAC_OPARATION_BINARY_OP_ADD_INT:
	case MCC_TAC_OPARATION_BINARY_OP_SUB_INT:
	case MCC_TAC_OPARATION_BINARY_OP_MUL_INT:
	case MCC_TAC_OPARATION_BINARY_OP_DIV_INT:
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_INT:
	case MCC_TAC_OPARATION_EQUALS_INT:
	case MCC_TAC_OPARATION_NOT_EQUALS_INT:
	case MCC_TAC_OPARATION_GREATER_INT:
	case MCC_TAC_OPARATION_LESS_INT:
	case MCC_TAC_OPARATION_GREATER_EQUALS_INT:
	case MCC_TAC_OPARATION_LESS_EQUALS_INT:
	case MCC_TAC_OPARATION_UNARY_MINUS_INT:
	case MCC_TAC_OPARATION_RETURN_PRIMITIVE_INT:
	case MCC_TAC_OPARATION_PARAM_INT_PRIMITIVE:
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_INT:
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_FLOAT:
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_BOOL:
	case MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_STRING:
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT:
		return MCC_TAC_OPARATION_RETURN_PRIMITIVE_INT;
		break;
	case MCC_TAC_OPARATION_BINARY_OP_ADD_FLOAT:
	case MCC_TAC_OPARATION_BINARY_OP_SUB_FLOAT:
	case MCC_TAC_OPARATION_BINARY_OP_MUL_FLOAT:
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_FLOAT:
	case MCC_TAC_OPARATION_EQUALS_FLOAT:
	case MCC_TAC_OPARATION_NOT_EQUALS_FLOAT:
	case MCC_TAC_OPARATION_GREATER_FLOAT:
	case MCC_TAC_OPARATION_LESS_FLOAT:
	case MCC_TAC_OPARATION_GREATER_EQUALS_FLOAT:
	case MCC_TAC_OPARATION_LESS_EQUALS_FLOAT:
	case MCC_TAC_OPARATION_UNARY_MINUS_FLOAT:
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_FLOAT:
	case MCC_TAC_OPARATION_PARAM_FLOAT_PRIMITIVE:
	case MCC_TAC_OPARATION_LABEL_FLOAT:
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_FLOAT:
		return MCC_TAC_OPARATION_RETURN_PREMITIVE_FLOAT;
		break;
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_BOOL:
	case MCC_TAC_OPARATION_EQUALS_BOOL:
	case MCC_TAC_OPARATION_NOT_EQUALS_BOOL:
	case MCC_TAC_OPARATION_BINARY_AND:
	case MCC_TAC_OPARATION_BINARY_OR:
	case MCC_TAC_OPARATION_UNARY_NEGATION:
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_BOOL:
	case MCC_TAC_OPARATION_PARAM_BOOL_PRIMITIVE:
	case MCC_TAC_OPARATION_LABEL_BOOL:
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL:
		return MCC_TAC_OPARATION_RETURN_PREMITIVE_BOOL;
		break;
	case MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_STRING:
	case MCC_TAC_OPARATION_RETURN_PREMITIVE_STRING:
	case MCC_TAC_OPARATION_PARAM_STRING_PRIMITIVE:
	case MCC_TAC_OPARATION_LABEL_STRING:
	case MCC_TAC_OPARATION_DECLARE_PRIMITIVE_STRING:
		return MCC_TAC_OPARATION_RETURN_PREMITIVE_STRING;
		break;
	case MCC_TAC_OPARATION_RETURN_ARRAY_INT:
	case MCC_TAC_OPARATION_PARAM_INT_ARRAY:
	case MCC_TAC_OPARATION_DECLARE_ARRAY_INT:
		return MCC_TAC_OPARATION_RETURN_ARRAY_INT;
		break;
	case MCC_TAC_OPARATION_RETURN_ARRAY_FLOAT:
	case MCC_TAC_OPARATION_PARAM_FLOAT_ARRAY:
	case MCC_TAC_OPARATION_DECLARE_ARRAY_FLOAT:
		return MCC_TAC_OPARATION_RETURN_ARRAY_FLOAT;
		break;
	case MCC_TAC_OPARATION_RETURN_ARRAY_BOOL:
	case MCC_TAC_OPARATION_PARAM_BOOL_ARRAY:
	case MCC_TAC_OPARATION_DECLARE_ARRAY_BOOL:
		return MCC_TAC_OPARATION_RETURN_ARRAY_BOOL;
		break;
	case MCC_TAC_OPARATION_RETURN_ARRAY_STRING:
	case MCC_TAC_OPARATION_PARAM_STRING_ARRAY:
	case MCC_TAC_OPARATION_DECLARE_ARRAY_STRING:
		return MCC_TAC_OPARATION_RETURN_ARRAY_STRING;
		break;
	default: return MCC_TAC_OPARATION_EMPTY; break;
	}
}

struct mCc_tac_element *
mCc_tac_statement_return(struct mCc_ast_statement *statement,
                         struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(previous_tac);

	if (statement->return_expression != NULL) {
		struct mCc_tac_element *tac_return_expression =
		    helper_get_tac_of_expression(statement->return_expression,
		                                 previous_tac);
		enum mCc_tac_operation return_operation =
		    tac_helper_get_return_tac_operation(
		        tac_return_expression->tac_operation);
		struct mCc_tac_element *tac =
		    tac_new_element(return_operation, NULL, NULL,
		                    mCc_tac_create_from_tac_identifier(
		                        tac_return_expression->tac_result),
		                    MCC_TAC_TYPE_NO_TYPE, 0);
		mCc_tac_connect_tac_entry(tac_return_expression, tac);
		return tac;
	} else {
		return previous_tac;
	}
}

struct mCc_tac_element *
mCc_tac_statement_declaration(struct mCc_ast_statement *statement,
                              struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(statement->declaration);
	assert(previous_tac);

	struct mCc_tac_element *tac_declaration;
	if (statement->declaration->declaration_type ==
	    MCC_AST_DECLARATION_PRIMITIVE) {
		tac_declaration =
		    mCc_tac_declaration_primitive(statement->declaration, previous_tac);
	} else if (statement->declaration->declaration_type ==
	           MCC_AST_DECLARATION_ARRAY) {
		tac_declaration =
		    mCc_tac_declaration_array(statement->declaration, previous_tac);
	}
	return tac_declaration;
}

struct mCc_tac_element *
mCc_tac_statement_assignment(struct mCc_ast_statement *statement,
                             struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(statement->assignment);
	assert(previous_tac);

	struct mCc_tac_element *tac_assignment;
	if (statement->assignment->assignment_type ==
	    MCC_AST_ASSIGNMENT_PRIMITIVE) {
		tac_assignment =
		    mCc_tac_assignment_primitive(statement->assignment, previous_tac);
	} else if (statement->assignment->assignment_type ==
	           MCC_AST_ASSIGNMENT_ARRAY) {
		tac_assignment =
		    mCc_tac_assignment_array(statement->assignment, previous_tac);
	}
	return tac_assignment;
}

struct mCc_tac_element *
mCc_tac_statement_expression(struct mCc_ast_statement *statement,
                             struct mCc_tac_element *previous_tac)
{
	assert(statement);
	assert(statement->expression);
	assert(previous_tac);

	struct mCc_tac_element *tac_expression =
	    helper_get_tac_of_expression(statement->expression, previous_tac);

	return tac_expression;
}
