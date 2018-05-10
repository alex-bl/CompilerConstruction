#ifndef MCC_AST_BASIC_TAC_H
#define MCC_AST_BASIC_TAC_H

#include <stdio.h>
#include "mCc/ast/basis/ast_data_type.h"

#define LABEL_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Types of TAC:
 * Assignment statement: x:= y op z
 * Assignment statement: x:= op z
 * copy statement: x:= y
 * Unconditional jump: goto L
 * Conditional jump: if x relop y goto L
 * Procedural call: param x call p return y
 * Return statement: return y
 * Indexing statement: x:=y[i] or y[i]:=x
 * Address assignment: x:=&y (not in our language?)
 */

enum mCc_tac_operation {
	MCC_TAC_OPERATION_EMPTY,
	MCC_TAC_OPARATION_BINARY_OP_ADD,
	MCC_TAC_OPARATION_BINARY_OP_SUB,
	MCC_TAC_OPARATION_BINARY_OP_MUL,
	MCC_TAC_OPARATION_BINARY_OP_DIV,
	MCC_TAC_OPARATION_BINARY_OP_LESS_THAN,
	MCC_TAC_OPARATION_BINARY_OP_GREATER_THAN,
	MCC_TAC_OPARATION_BINARY_OP_LESS_OR_EQUALS_THAN,
	MCC_TAC_OPARATION_BINARY_OP_GREATER_OR_EQUALS_THAN,
	MCC_TAC_OPARATION_BINARY_OP_AND,
	MCC_TAC_OPARATION_BINARY_OP_OR,
	MCC_TAC_OPARATION_BINARY_OP_EQUALS,
	MCC_TAC_OPARATION_BINARY_OP_NOT_EQUALS,
	MCC_TAC_OPARATION_UNARY_OP_MINUS,
	MCC_TAC_OPARATION_UNARY_OP_NEGATION,
	MCC_TAC_OPARATION_COPY,
	MCC_TAC_OPARATION_UNCONDITIONAL_JUMP,
	MCC_TAC_OPARATION_CONDITIONAL_JUMP,
	MCC_TAC_OPARATION_PROCEDURAL_CALL,
	MCC_TAC_OPARATION_RETURN,
	MCC_TAC_OPARATION_INDEXING,
};

//void mCc_tac_delete_operation(enum mCc_tac_operation *operation);

struct mCc_tac_element {
	enum mCc_tac_operation tac_operation;
	struct mCc_tac_identifier *tac_argument1;
	struct mCc_tac_identifier *tac_argument2;
	struct mCc_tac_identifier *tac_result;
	struct mCc_tac_next_elment* tac_next_element;
};

struct mCc_tac_element *tac_new_element(enum mCc_tac_operation operation, struct mCc_tac_identifier *argument1,
		struct mCc_tac_identifier *argument2, struct mCc_tac_identifier *result);


struct mCc_tac_identifier {
	char *name;
};

void mCc_tac_delete_identifier(struct mCc_tac_identifier *identifier);



/*void tac_begin(FILE *out);

void tac_end(FILE *out);

void tac_node(FILE *out, const void *node, const char *label);

void tac_edge(FILE *out, const void *src_node, const void *dst_node,
                    const char *label);

void tac_edge_if_dest_exists(FILE *out, const void *src_node,
                                   const void *dst_node, const char *label);

const char *print_data_type(enum mCc_ast_data_type type);*/

#ifdef __cplusplus
}
#endif

#endif
