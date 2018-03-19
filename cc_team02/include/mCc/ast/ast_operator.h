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
};

enum mCc_ast_unary_op {
	MCC_AST_UNARY_OP_MINUS,
	MCC_AST_UNARY_OP_NEGATION,
};

#ifdef __cplusplus
}
#endif

#endif
