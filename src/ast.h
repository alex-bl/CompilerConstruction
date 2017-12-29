#ifndef MC_AST_H
#define MC_AST_H

/* Forward Declarations */

struct mC_ast_node;
struct mC_ast_expression;
struct mC_ast_literal;

/* Data contained by every ast node. */
struct mC_ast_node
{
	/* TODO source location */
};

/* Operators */

enum mC_ast_binary_op
{
	MC_AST_BINARY_OP_ADD,
	MC_AST_BINARY_OP_SUB,
	MC_AST_BINARY_OP_MUL,
	MC_AST_BINARY_OP_DIV,
};

/* Expressions */

enum mC_ast_expression_type
{
	MC_AST_EXPRESSION_TYPE_LITERAL,
	MC_AST_EXPRESSION_TYPE_BINARY_OP,
	MC_AST_EXPRESSION_TYPE_PARENTH,
};

struct mC_ast_expression
{
	struct mC_ast_node node;
	enum   mC_ast_expression_type type;
	union
	{
		/* MC_AST_EXPRESSION_TYPE_LITERAL */
		struct mC_ast_literal *literal;

		/* MC_AST_EXPRESSION_TYPE_BINARY_OP */
		struct
		{
			struct mC_ast_expression *lhs;
			enum   mC_ast_binary_op  *op;
			struct mC_ast_expression *rhs;
		};

		/* MC_AST_EXPRESSION_TYPE_PARENTH */
		struct mC_ast_expression *expression;
	};
};

struct mC_ast_expression*
mC_ast_expression_new_literal_expression(struct mC_ast_literal* literal);

struct mC_ast_expression*
mC_ast_expression_new_parenth_expression(struct mC_ast_expression* expression);

struct mC_ast_expression*
mC_ast_expression_new_binary_op_expression(enum mC_ast_binary_op op,
                                           struct mC_ast_expression* lhs,
                                           struct mC_ast_expression* rhs);

void mC_ast_expression_delete(struct mC_ast_expression *expression);

/* Literals */

enum mC_ast_literal_type
{
	MC_AST_LITERAL_TYPE_INT,
	MC_AST_LITERAL_TYPE_FLOAT,
};

struct mC_ast_literal
{
	struct mC_ast_node node;
	enum   mC_ast_literal_type type;
	union
	{
		/* MC_AST_LITERAL_TYPE_INT */
		long i_value;

		/* MC_AST_LITERAL_TYPE_FLOAT */
		double f_value;
	};
};

struct mC_ast_literal*
mC_ast_literal_new_int_literal(long value);

struct mC_ast_literal*
mC_ast_literal_new_float_literal(double value);

void mC_ast_literal_delete(struct mC_ast_literal *literal);

#endif
