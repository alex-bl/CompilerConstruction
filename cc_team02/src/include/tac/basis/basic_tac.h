#ifndef MCC_AST_BASIC_TAC_H
#define MCC_AST_BASIC_TAC_H

#include "ast_data_type.h"
#include <stdbool.h>
#include <stdio.h>

#define LABEL_SIZE 64

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_tac_operation {
	MCC_TAC_OPARATION_EMPTY,

	// BINARY_OP
	MCC_TAC_OPARATION_BINARY_OP_ADD_INT,
	MCC_TAC_OPARATION_BINARY_OP_ADD_FLOAT,

	MCC_TAC_OPARATION_BINARY_OP_SUB_INT,
	MCC_TAC_OPARATION_BINARY_OP_SUB_FLOAT,

	MCC_TAC_OPARATION_BINARY_OP_MUL_INT,
	MCC_TAC_OPARATION_BINARY_OP_MUL_FLOAT,

	MCC_TAC_OPARATION_BINARY_OP_DIV_INT,
	MCC_TAC_OPARATION_BINARY_OP_DIV_FLOAT,

	// ASSIGN
	MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_INT,
	MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_FLOAT,
	MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_BOOL,
	MCC_TAC_OPARATION_ASSIGN_PRIMITIVE_STRING,
	MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_INT,
	MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_FLOAT,
	MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_BOOL,
	MCC_TAC_OPARATION_ASSIGN_FUNCTION_CALL_STRING,

	// TODO: needed?
	MCC_TAC_OPARATION_ASSIGN_ARRAY_INT,
	MCC_TAC_OPARATION_ASSIGN_ARRAY_FLOAT,
	MCC_TAC_OPARATION_ASSIGN_ARRAY_BOOL,
	MCC_TAC_OPARATION_ASSIGN_ARRAY_STRING,

	// COMPARE: (only one compair needed (result internally stored into cmp?
	// reg))
	MCC_TAC_OPARATION_EQUALS_INT,
	MCC_TAC_OPARATION_EQUALS_FLOAT,
	MCC_TAC_OPARATION_EQUALS_BOOL,

	MCC_TAC_OPARATION_NOT_EQUALS_INT,
	MCC_TAC_OPARATION_NOT_EQUALS_FLOAT,
	MCC_TAC_OPARATION_NOT_EQUALS_BOOL,

	MCC_TAC_OPARATION_GREATER_INT,
	MCC_TAC_OPARATION_GREATER_FLOAT,

	MCC_TAC_OPARATION_LESS_INT,
	MCC_TAC_OPARATION_LESS_FLOAT,

	MCC_TAC_OPARATION_GREATER_EQUALS_INT,
	MCC_TAC_OPARATION_GREATER_EQUALS_FLOAT,

	MCC_TAC_OPARATION_LESS_EQUALS_INT,
	MCC_TAC_OPARATION_LESS_EQUALS_FLOAT,

	// AND/OR
	MCC_TAC_OPARATION_BINARY_AND,
	MCC_TAC_OPARATION_BINARY_OR,

	// UNARY
	MCC_TAC_OPARATION_UNARY_MINUS_INT,
	MCC_TAC_OPARATION_UNARY_MINUS_FLOAT,
	MCC_TAC_OPARATION_UNARY_NEGATION,

	// JUMP - not using?
	MCC_TAC_OPARATION_JUMP_NOT_EQUALS,
	// JUMP - using jump and jump_false instead
	MCC_TAC_OPARATION_JUMP,
	MCC_TAC_OPARATION_JUMP_EQUALS,

	// RETURN
	MCC_TAC_OPARATION_RETURN_PRIMITIVE_VOID,
	MCC_TAC_OPARATION_RETURN_PRIMITIVE_INT,
	MCC_TAC_OPARATION_RETURN_PREMITIVE_FLOAT,
	MCC_TAC_OPARATION_RETURN_PREMITIVE_BOOL,
	MCC_TAC_OPARATION_RETURN_PREMITIVE_STRING,

	MCC_TAC_OPARATION_RETURN_ARRAY_INT,
	MCC_TAC_OPARATION_RETURN_ARRAY_FLOAT,
	MCC_TAC_OPARATION_RETURN_ARRAY_BOOL,
	MCC_TAC_OPARATION_RETURN_ARRAY_STRING,

	MCC_TAC_OPARATION_INTERMEDIATE_RETURN_INT,
	MCC_TAC_OPARATION_INTERMEDIATE_RETURN_FLOAT,
	MCC_TAC_OPARATION_INTERMEDIATE_RETURN_BOOL,
	MCC_TAC_OPARATION_INTERMEDIATE_RETURN_STRING,

	// PARAMETER
	MCC_TAC_OPARATION_PARAM_INT_PRIMITIVE,
	MCC_TAC_OPARATION_PARAM_FLOAT_PRIMITIVE,
	MCC_TAC_OPARATION_PARAM_BOOL_PRIMITIVE,
	MCC_TAC_OPARATION_PARAM_STRING_PRIMITIVE,
	MCC_TAC_OPARATION_PARAM_INT_ARRAY,
	MCC_TAC_OPARATION_PARAM_FLOAT_ARRAY,
	MCC_TAC_OPARATION_PARAM_BOOL_ARRAY,
	MCC_TAC_OPARATION_PARAM_STRING_ARRAY,

	MCC_TAC_OPARATION_CALL,

	// LABEL
	MCC_TAC_OPARATION_LABEL_FUNCTION,
	MCC_TAC_OPARATION_LABEL_FLOAT,
	MCC_TAC_OPARATION_LABEL_IF,
	MCC_TAC_OPARATION_LABEL_ELSE,
	MCC_TAC_OPARATION_LABEL_AFTER_ELSE,
	MCC_TAC_OPARATION_LABEL_WHILE,
	MCC_TAC_OPARATION_LABEL_STRING,
	MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_INT,
	MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_FLOAT,
	MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_BOOL,
	MCC_TAC_OPERATION_PSEUDO_ASSIGNMENT_STRING,

	MCC_TAC_OPARATION_LABEL_BOOL,

	// ARGUMENT (LABELS)
	MCC_TAC_OPARATION_LABEL_ARGUMENT,
	MCC_TAC_OPARATION_ARGUMENT_LIST_START,

	// FUNCTION DEF
	MCC_TAC_OPARATION_FUNCTION_CALL,
	MCC_TAC_OPARATION_START_FUNCTION_DEF,
	MCC_TAC_OPARATION_END_FUNCTION_DEF,

	// DECLARATION
	MCC_TAC_OPARATION_DECLARE_PRIMITIVE_INT,
	MCC_TAC_OPARATION_DECLARE_PRIMITIVE_FLOAT,
	MCC_TAC_OPARATION_DECLARE_PRIMITIVE_BOOL,
	MCC_TAC_OPARATION_DECLARE_PRIMITIVE_STRING,
	MCC_TAC_OPARATION_DECLARE_ARRAY_INT,
	MCC_TAC_OPARATION_DECLARE_ARRAY_FLOAT,
	MCC_TAC_OPARATION_DECLARE_ARRAY_BOOL,
	MCC_TAC_OPARATION_DECLARE_ARRAY_STRING,

	// LITERAL
	MCC_TAC_OPARATION_LITERAL,

	/*
	/only one compair needed (result internally stored into cmp? reg)
	- and	=> todo
	- or	=> todo*/

	// OLD OPARATIONS:
	/*MCC_TAC_OPARATION_BINARY_OP_LESS_THAN,
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
	MCC_TAC_OPARATION_PROCEDURAL_CALL,
	MCC_TAC_OPARATION_RETURN,
	MCC_TAC_OPARATION_INDEXING,
	MCC_TAC_OPARATION_LABLE,
	MCC_TAC_OPARATION_FUNCTION_DEF,
	MCC_TAC_OPARATION_FUNCTION_PARAMETER,*/
};

enum mCc_tac_type {
	MCC_TAC_TYPE_NO_TYPE,
	MCC_TAC_TYPE_INTEGER,
	MCC_TAC_TYPE_BOOL,
	MCC_TAC_TYPE_FLOAT,
	MCC_TAC_TYPE_STRING
};

enum mCc_tac_identifier_type {
	MCC_IDENTIFIER_TAC_TYPE_INTEGER,
	MCC_IDENTIFIER_TAC_TYPE_FLOAT,
	MCC_IDENTIFIER_TAC_TYPE_BOOL,
	MCC_IDENTIFIER_TAC_TYPE_STRING,
	/*required for identifying tac-identifier denoting a variable*/
	// TODO: distinguish between variable and other labels!!
	MCC_IDENTIFIER_TAC_TYPE_VAR,
	MCC_IDENTIFIER_TAC_TYPE_FUNCTION_CALL,
	MCC_IDENTIFIER_TAC_TYPE_FUNCTION_DEF,
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
	bool is_param;
	char *name;
	union {
		char *s_val;
		double f_val;
		long i_val;
		bool b_val;
	};
	int stack_offset;
};

int mCc_tac_helper_intlen(int var);

struct mCc_tac_identifier *mCc_helper_concat_name_and_scope(char *name,
                                                            int scope);

struct mCc_tac_identifier *tac_new_identifier(char *name);

struct mCc_tac_identifier *tac_new_identifier_string(char *string);

struct mCc_tac_identifier *tac_new_identifier_float(double value);

struct mCc_tac_identifier *tac_new_identifier_int(long value);

struct mCc_tac_identifier *tac_new_identifier_bool(bool value);

void mCc_tac_delete_identifier(struct mCc_tac_identifier *identifier);

void mCc_tac_element_delete(struct mCc_tac_element *tac_element);

void mCc_tac_delete(struct mCc_tac_element *tac_element);

struct mCc_tac_identifier *
mCc_tac_create_from_tac_identifier(struct mCc_tac_identifier *identifier);

struct mCc_tac_element *
mCc_tac_create_new_lable_tac_element(enum mCc_tac_operation label_type,
                                     struct mCc_tac_identifier *identifier,
                                     struct mCc_tac_element *previous_tac);

struct mCc_tac_identifier *mCc_tac_create_new_lable_identifier();

#ifdef __cplusplus
}
#endif

#endif
