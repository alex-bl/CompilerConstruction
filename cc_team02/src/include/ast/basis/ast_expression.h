#ifndef MCC_AST_EXPRESSION_H
#define MCC_AST_EXPRESSION_H

#include <stdbool.h>

#include "ast_data_type.h"
#include "ast_function.h"
#include "ast_identifier.h"
#include "ast_literal.h"
#include "ast_node.h"
#include "ast_operator.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_ast_expression_type {
	MCC_AST_EXPRESSION_TYPE_LITERAL,
	MCC_AST_EXPRESSION_TYPE_BINARY_OP,
	MCC_AST_EXPRESSION_TYPE_PARENTH,
	/*newly added*/
	MCC_AST_EXPRESSION_TYPE_IDENTIFIER,
	MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY,
	MCC_AST_EXPRESSION_TYPE_CALL_EXPR,
	MCC_AST_EXPRESSION_TYPE_UNARY_OP
};

struct mCc_ast_expression {
	struct mCc_ast_node node;

	enum mCc_ast_expression_type type;
	struct mCc_ast_expression *next_expr;
	bool is_function_parameter;

	// to ease the semantic checks later
	enum mCc_ast_data_type data_type;

	// for semantic checks
	struct mCc_validation_status_result *semantic_error;

	union {
		/* MCC_AST_EXPRESSION_TYPE_LITERAL */
		struct mCc_ast_literal *literal;

		/* MCC_AST_EXPRESSION_TYPE_BINARY_OP */
		struct {
			enum mCc_ast_binary_op op;
			struct mCc_ast_expression *lhs;
			struct mCc_ast_expression *rhs;
		};

		/* MCC_AST_EXPRESSION_TYPE_PARENTH */
		struct mCc_ast_expression *expression;

		/* MCC_AST_EXPRESSION_TYPE_UNARY_OP */
		struct {
			enum mCc_ast_unary_op unary_op;
			struct mCc_ast_expression *unary_rhs;
		};

		/* MCC_AST_EXPRESSION_TYPE_IDENTIFIER */
		struct mCc_ast_identifier *identifier;

		/* MCC_AST_EXPRESSION_TYPE_IDENTIFIER_ARRAY */
		struct {
			struct mCc_ast_identifier *array_identifier;
			struct mCc_ast_expression *array_index_expression;
		};

		/* MCC_AST_EXPRESSION_TYPE_CALL_EXPR */
		struct mCc_ast_function_call *function_call;
	};
};

struct mCc_ast_expression *
mCc_ast_new_expression_literal(struct mCc_ast_literal *literal);

struct mCc_ast_expression *
mCc_ast_new_expression_binary_op(enum mCc_ast_binary_op op,
                                 struct mCc_ast_expression *lhs,
                                 struct mCc_ast_expression *rhs);

struct mCc_ast_expression *
mCc_ast_new_expression_parenth(struct mCc_ast_expression *expression);

struct mCc_ast_expression *
mCc_ast_new_expression_unary_op(enum mCc_ast_unary_op op,
                                struct mCc_ast_expression *expression);

struct mCc_ast_expression *
mCc_ast_new_expression_identifier(struct mCc_ast_identifier *identifier);

struct mCc_ast_expression *mCc_ast_new_expression_array_identifier(
    struct mCc_ast_identifier *array_identifier,
    struct mCc_ast_expression *array_index_expression);

struct mCc_ast_expression *mCc_ast_new_expression_function_call(
    struct mCc_ast_function_call *function_call);

void mCc_ast_delete_expression(struct mCc_ast_expression *expression);

#ifdef __cplusplus
}
#endif

#endif
