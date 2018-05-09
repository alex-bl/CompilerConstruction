#ifndef MCC_AST_OPERATOR_H
#define MCC_AST_OPERATOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------------------- Operators */

enum mCc_ast_binary_op {
	MCC_AST_BINARY_OP_ADD,
	MCC_AST_BINARY_OP_SUB,
	MCC_AST_BINARY_OP_MUL,
	MCC_AST_BINARY_OP_DIV,
	MCC_AST_BINARY_OP_LESS_THAN,
	MCC_AST_BINARY_OP_GREATER_THAN,
	MCC_AST_BINARY_OP_LESS_OR_EQUALS_THAN,
	MCC_AST_BINARY_OP_GREATER_OR_EQUALS_THAN,
	MCC_AST_BINARY_OP_AND,
	MCC_AST_BINARY_OP_OR,
	MCC_AST_BINARY_OP_EQUALS,
	MCC_AST_BINARY_OP_NOT_EQUALS
};

enum mCc_ast_unary_op {
	MCC_AST_UNARY_OP_MINUS,
	MCC_AST_UNARY_OP_NEGATION,
};

#ifdef __cplusplus
}
#endif

#endif
