#ifndef MCC_AST_DATA_TYPE_H
#define MCC_AST_DATA_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/*enum mCc_ast_data_type {
	// use void only for functions!
	MCC_AST_DATA_TYPE_VOID,
	MCC_AST_DATA_TYPE_INT,
	MCC_AST_DATA_TYPE_FLOAT,
	MCC_AST_DATA_TYPE_BOOL,
	MCC_AST_DATA_TYPE_STRING
};*/

/*
 * Types of TAC:
 * Assignment statement: x:= y op z
 * Assignment statement: x:= op z
 * copy statement: x:= y
 * Unconditional jump: goto L
 * Conditional jump: if x relop y goto L
 * Procedural call: param x call p return y
 */

enum mCc_tac_operation {
	MCC_TAC_OPARATION_JUMP,
	MCC_TAC_OPARATION_JUMPFALSE,
	MCC_TAC_OPARATION_ADDITION,
	MCC_TAC_OPARATION_SUBTRACTION,
	MCC_TAC_OPARATION_LABLE,
	MCC_TAC_OPARATION_GREATERTHAN,
	MCC_TAC_OPARATION_LESSTHAN,
	MCC_TAC_OPARATION_ASSIGN,
};

#ifdef __cplusplus
}
#endif

#endif
