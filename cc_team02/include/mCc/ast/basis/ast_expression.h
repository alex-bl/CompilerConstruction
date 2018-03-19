#ifndef MCC_AST_EXPRESSION_H
#define MCC_AST_EXPRESSION_H

#include "mCc/ast/basis/ast_node.h"
#include "mCc/ast/basis/ast_operator.h"
#include "mCc/ast/basis/ast_literal.h"


#ifdef __cplusplus
extern "C" {
#endif

enum mCc_ast_expression_type {
	MCC_AST_EXPRESSION_TYPE_LITERAL,
	MCC_AST_EXPRESSION_TYPE_BINARY_OP,
	MCC_AST_EXPRESSION_TYPE_PARENTH,
	/*newly added*/
	MCC_AST_EXPRESSION_TYPE_IDENTIFIER,
	MCC_AST_EXPRESSION_TYPE_CALL_EXPR,
	MCC_AST_EXPRESSION_TYPE_UNARY_OP
};

struct mCc_ast_expression {
	struct mCc_ast_node node;

	enum mCc_ast_expression_type type;
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

/*added*/
struct mCc_ast_expression *
mCc_ast_new_expression_unary_op(struct mCc_ast_expression *expression);

void mCc_ast_delete_expression(struct mCc_ast_expression *expression);

#ifdef __cplusplus
}
#endif

#endif
