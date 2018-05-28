#ifndef MCC_AST_BASIC_TAC_H
#define MCC_AST_BASIC_TAC_H

#include "ast_data_type.h"
#include <stdio.h>
#include <stdbool.h>

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
	MCC_TAC_OPARATION_EMPTY,
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
	MCC_TAC_OPARATION_LABLE,
	MCC_TAC_OPARATION_FUNCTION_DEF,
	MCC_TAC_OPARATION_FUNCTION_PARAMETER,
};

enum mCc_tac_type {
	MCC_TAC_TYPE_NO_TYPE,
	MCC_TAC_TYPE_INTEGER,
	MCC_TAC_TYPE_FLOAT,
	MCC_TAC_TYPE_STRING
};

enum mCc_tac_identifier_type {
	MCC_IDENTIFIER_TAC_TYPE_INTEGER,
	MCC_IDENTIFIER_TAC_TYPE_FLOAT,
	MCC_IDENTIFIER_TAC_TYPE_BOOL,
	MCC_IDENTIFIER_TAC_TYPE_STRING
};

struct mCc_tac_element {
	enum mCc_tac_operation tac_operation;
	struct mCc_tac_identifier *tac_argument1;
	struct mCc_tac_identifier *tac_argument2;
	struct mCc_tac_identifier *tac_result;
	enum mCc_tac_type tac_type;
	int tac_scope;
	struct mCc_tac_element *tac_next_element;
};

struct mCc_tac_element *tac_new_element(enum mCc_tac_operation operation,
                                        struct mCc_tac_identifier *argument1,
                                        struct mCc_tac_identifier *argument2,
                                        struct mCc_tac_identifier *result,
                                        enum mCc_tac_type tac_type,
                                        int tac_scope);

void mCc_tac_connect_tac_entry(struct mCc_tac_element *previous_tac,
                               struct mCc_tac_element *tac);

struct mCc_tac_identifier {
	enum mCc_tac_identifier_type type;
	union {
		char *name;
		double f_val;
		long i_val;
		bool b_val;
	};
	int stack_offset;
};

struct mCc_tac_identifier *tac_new_identifier(char *name);

struct mCc_tac_identifier *tac_new_identifier_float(double value);

struct mCc_tac_identifier *tac_new_identifier_int(long value);

struct mCc_tac_identifier *tac_new_identifier_bool(bool value);

void mCc_tac_delete_identifier(struct mCc_tac_identifier *identifier);

void mCc_tac_element_delete(struct mCc_tac_element *tac_element);

void mCc_tac_delete(struct mCc_tac_element *tac_element);

struct mCc_tac_identifier *
mCc_tac_create_from_tac_identifier(struct mCc_tac_identifier *identifier);

#ifdef __cplusplus
}
#endif

#endif
