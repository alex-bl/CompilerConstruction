#ifndef MCC_AST_FUNCTION_H
#define MCC_AST_FUNCTION_H

#include <stddef.h>

#include "mCc/ast/basis/ast_declaration.h"
#include "mCc/ast/basis/ast_expression.h"
#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/ast/basis/ast_node.h"
#include "mCc/ast/basis/ast_statement.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: really required separately or using mcc_type?
enum mCc_ast_function_return_type {
	MCC_AST_FUNCTION_RETURN_TYPE_VOID,
	MCC_AST_FUNCTION_RETURN_TYPE_INT,
	MCC_AST_FUNCTION_RETURN_TYPE_FLOAT,
	MCC_AST_FUNCTION_RETURN_TYPE_BOOL,
	MCC_AST_FUNCTION_RETURN_TYPE_STRING
};

struct mCc_ast_function_def {
	struct mCc_ast_node node;

	/* MCC_AST_IDENTIFIER */
	struct mCc_ast_identifier identifier;
	enum mCc_ast_function_return_type return_type;
	/* Just a helper */
	struct mCc_ast_compound_statement *compound_statement;

	struct {
		struct mCc_ast_declaration *parameters;
		/*TODO: size_t enough?*/
		size_t nr_of_parameters;
	};
};

struct mCc_ast_function_def
mCc_ast_new_void_function_def(const char *identifier);

struct mCc_ast_function_def mCc_ast_new_int_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt);

struct mCc_ast_function_def mCc_ast_new_float_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt);

struct mCc_ast_function_def mCc_ast_new_bool_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt);

struct mCc_ast_function_def mCc_ast_new_string_function_def(
    const char *identifier, struct mCc_ast_declaration *params,
    size_t nr_of_params, struct mCc_ast_compound_statement *compound_stmt);

void mCc_ast_delete_void_function_def(
    struct mCc_ast_function_def *function_def);

void mCc_ast_delete_int_function_def(struct mCc_ast_function_def *function_def);

void mCc_ast_delete_float_function_def(
    struct mCc_ast_function_def *function_def);

void mCc_ast_delete_bool_function_def(
    struct mCc_ast_function_def *function_def);

void mCc_ast_delete_string_function_def(
    struct mCc_ast_function_def *function_def);

/* ---------------------------------------------------------------- Function
 * call*/

struct mCc_ast_function_call {
	struct mCc_ast_node node;

	/* MCC_AST_IDENTIFIER */
	struct mCc_ast_identifier identifier;

	struct {
		/* MCC_AST_EXPRESSION*/
		struct mCc_ast_expression *arguments;
		/*TODO: long here?*/
		long nr_expressions;
	};
};

struct mCc_ast_function_call
mCc_ast_new_int_function_call(const char *identifier,
                              struct mCc_ast_expression *args, long nr_args);

void mCc_ast_delete_function_call(struct mCc_ast_function_call *function_call);

#ifdef __cplusplus
}
#endif

#endif
