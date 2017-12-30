#ifndef MCC_AST_H
#define MCC_AST_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Forward Declarations */

struct mC_ast_node;
struct mC_ast_expression;
struct mC_ast_literal;

/* Data contained by every ast node. */
struct mC_ast_node {
	/* TODO source location */

	/* An empty struct messes up C and C++ interoperability. Remove this
	 * pitiful, unsed integer when you add another field. */
	int unused;
};

/* Operators */

enum mC_ast_binary_op {
	MC_AST_BINARY_OP_ADD,
	MC_AST_BINARY_OP_SUB,
	MC_AST_BINARY_OP_MUL,
	MC_AST_BINARY_OP_DIV,
};

/* Expressions */

enum mC_ast_expression_type {
	MC_AST_EXPRESSION_TYPE_LITERAL,
	MC_AST_EXPRESSION_TYPE_BINARY_OP,
	MC_AST_EXPRESSION_TYPE_PARENTH,
};

struct mC_ast_expression {
	struct mC_ast_node node;
	enum mC_ast_expression_type type;
	union {
		/* MC_AST_EXPRESSION_TYPE_LITERAL */
		struct mC_ast_literal *literal;

		/* MC_AST_EXPRESSION_TYPE_BINARY_OP */
		struct {
			enum mC_ast_binary_op op;
			struct mC_ast_expression *lhs;
			struct mC_ast_expression *rhs;
		};

		/* MC_AST_EXPRESSION_TYPE_PARENTH */
		struct mC_ast_expression *expression;
	};
};

struct mC_ast_expression *
mC_ast_new_expression_literal(struct mC_ast_literal *literal);

struct mC_ast_expression *
mC_ast_new_expression_parenth(struct mC_ast_expression *expression);

struct mC_ast_expression *
mC_ast_new_expression_binary_op(enum mC_ast_binary_op op,
                                struct mC_ast_expression *lhs,
                                struct mC_ast_expression *rhs);

void mC_ast_delete_expression(struct mC_ast_expression *expression);

/* Literals */

enum mC_ast_literal_type {
	MC_AST_LITERAL_TYPE_INT,
	MC_AST_LITERAL_TYPE_FLOAT,
};

struct mC_ast_literal {
	struct mC_ast_node node;
	enum mC_ast_literal_type type;
	union {
		/* MC_AST_LITERAL_TYPE_INT */
		long i_value;

		/* MC_AST_LITERAL_TYPE_FLOAT */
		double f_value;
	};
};

struct mC_ast_literal *mC_ast_new_literal_int(long value);

struct mC_ast_literal *mC_ast_new_literal_float(double value);

void mC_ast_delete_literal(struct mC_ast_literal *literal);

#ifdef __cplusplus
}
#endif

#endif
