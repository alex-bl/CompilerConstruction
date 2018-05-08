#ifndef MCC_AST_BASIC_TAC_H
#define MCC_AST_BASIC_TAC_H

#include <stdio.h>
#include "../basis/ast_data_type.h"

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
	MCC_TAC_OPARATION_JUMP,
	MCC_TAC_OPARATION_CONDITIONAL_JUMP,
	MCC_TAC_OPARATION_ADDITION,
	MCC_TAC_OPARATION_SUBTRACTION,
	MCC_TAC_OPARATION_LABLE,
	MCC_TAC_OPARATION_GREATERTHAN,
	MCC_TAC_OPARATION_LESSTHAN,
	MCC_TAC_OPARATION_ASSIGN,
};

struct mCc_tac_element {
	enum mCc_tac_operation tac_operation;
	struct mCc_tac_identifier *tac_argument1;
	struct mCc_tac_identifier *tac_argument2;
	struct mCc_tac_identifier *tac_result;
};


struct mCc_tac_identifier {
	char *name;
};

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
