#include <stdbool.h>
#include <string.h>

#include "log.h"
#include "mCc/ast.h"
#include "mCc/ast/basis/ast_data_type.h"
#include "mCc/symtab/validator/validator.h"

enum mCc_ast_data_type typecheck_get_type(struct mCc_ast_expression *expr,
                                          void *error)
{
	switch (expr->type) {
	case MCC_AST_EXPRESSION_TYPE_LITERAL: return expr->literal->type; break;
	case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
		enum mCc_ast_data_type lhs_type = typecheck_get_type(expr->lhs, error);
		enum mCc_ast_data_type rhs_type = typecheck_get_type(expr->rhs, error);
		if (lhs_type == rhs_type) {
			return lhs_type;
		}
		error = strup("Expected 'type', but have 'other_type'");
		return MCC_AST_DATA_TYPE_INCONSISTENT;
		//TODO: what to return?
		break;
	case MCC_AST_EXPRESSION_TYPE_PARENTH:
		return typecheck_get_type(expr->expression, error);
		break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
		return expr->identifier->symtab_info->data_type;
		break;
	case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
		return expr->array_identifier->symtab_info->data_type;
		break;
	case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
		return expr->function_call->identifier->symtab_info->data_type;
		break;
	case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
		return typecheck_get_type(expr->unary_rhs, error);
		break;
	}

	//TODO: needed?
	bool typecheck_type_is_valid(enum mCc_ast_data_type expected_type,
	                             struct mCc_ast_expression * expr)
	{

		switch (expr->type) {
		case MCC_AST_EXPRESSION_TYPE_LITERAL:
			return expr->literal->type == expected_type;
			break;
		case MCC_AST_EXPRESSION_TYPE_BINARY_OP:
			return typecheck_type_is_valid(expected_type, expr->lhs) &&
			       typecheck_type_is_valid(expected_type, expr->rhs);
			break;
		case MCC_AST_EXPRESSION_TYPE_PARENTH:
			return typecheck_type_is_valid(expected_type, expr->expression);
			break;
		case MCC_AST_EXPRESSION_TYPE_IDENTIFIER:
			return expr->identifier->symtab_info->data_type == expected_type;
			break;
		case MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY:
			return expr->array_identifier->symtab_info->data_type ==
			       expected_type;
			break;
		case MCC_AST_EXPRESSION_TYPE_CALL_EXPR:
			return expr->function_call->identifier->symtab_info->data_type ==
			       expected_type;
			break;
		case MCC_AST_EXPRESSION_TYPE_UNARY_OP:
			return typecheck_type_is_valid(expected_type, expr->unary_rhs);
			break;
		}

		log_error("Should this ever happen?");
		return false;
	}
