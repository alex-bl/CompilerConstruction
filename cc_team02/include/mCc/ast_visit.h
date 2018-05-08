#ifndef MCC_AST_VISIT_H
#define MCC_AST_VISIT_H

#include "mCc/ast.h"

#define visit(node, callback, visitor) \
	do { \
		if (callback) { \
			(callback)(node, (visitor)->userdata); \
		} \
	} while (0)

#define visit_scope(callback, visitor) \
	do { \
		if (callback) { \
			(callback)((visitor)->userdata); \
		} \
	} while (0)

#define visit_if(cond, node, callback, visitor) \
	do { \
		if (cond) { \
			visit(node, callback, visitor); \
		} \
	} while (0)

#define visit_if_scope(cond, callback, visitor) \
	do { \
		if (cond) { \
			visit_scope(callback, visitor); \
		} \
	} while (0)

#define visit_if_pre_order(node, callback, visitor) \
	visit_if((visitor)->order == MCC_AST_VISIT_PRE_ORDER, node, callback, \
	         visitor)

#define visit_if_post_order(node, callback, visitor) \
	visit_if((visitor)->order == MCC_AST_VISIT_POST_ORDER, node, callback, \
	         visitor)

#define visit_if_both_order(node, callback, visitor) \
	visit_if((visitor)->order == MCC_AST_VISIT_BOTH_ORDER, node, callback, \
	         visitor)

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_ast_visit_traversal {
	MCC_AST_VISIT_DEPTH_FIRST,
	/* TODO: MCC_AST_VISIT_BREADTH_FIRST, */
};

enum mCc_ast_visit_order {
	MCC_AST_VISIT_PRE_ORDER,
	MCC_AST_VISIT_POST_ORDER,
	MCC_AST_VISIT_BOTH_ORDER
};

/* Callbacks */
typedef void (*mCc_ast_visit_expression_cb)(struct mCc_ast_expression *,
                                            void *);
typedef void (*mCc_ast_visit_literal_cb)(struct mCc_ast_literal *, void *);

typedef void (*mCc_ast_visit_assignment_cb)(struct mCc_ast_assignment *,
                                            void *);

typedef void (*mCc_ast_visit_declaration_cb)(struct mCc_ast_declaration *,
                                             void *);

typedef void (*mCc_ast_visit_function_def_cb)(struct mCc_ast_function_def *,
                                              void *);

typedef void (*mCc_ast_visit_function_call_cb)(struct mCc_ast_function_call *,
                                               void *);

typedef void (*mCc_ast_visit_identifier_cb)(struct mCc_ast_identifier *,
                                            void *);

typedef void (*mCc_ast_visit_program_cb)(struct mCc_ast_program *, void *);

typedef void (*mCc_ast_visit_statement_cb)(struct mCc_ast_statement *, void *);

// scope-handler
typedef void (*mCc_ast_scope_cb)(void *);

struct mCc_ast_visitor {
	enum mCc_ast_visit_traversal traversal;
	enum mCc_ast_visit_order order;

	void *userdata;
	struct mCc_ast_scope_holder *scope_level;

	// expression
	mCc_ast_visit_expression_cb expression;
	mCc_ast_visit_expression_cb expression_literal;
	mCc_ast_visit_expression_cb expression_binary_op;
	mCc_ast_visit_expression_cb expression_parenth;
	mCc_ast_visit_expression_cb expression_function_call;
	mCc_ast_visit_expression_cb expression_identifier;
	mCc_ast_visit_expression_cb expression_array_identifier;
	mCc_ast_visit_expression_cb expression_unary_op;

	mCc_ast_visit_expression_cb expression_post_order;
	mCc_ast_visit_expression_cb expression_literal_post_order;
	mCc_ast_visit_expression_cb expression_binary_op_post_order;
	mCc_ast_visit_expression_cb expression_parenth_post_order;
	mCc_ast_visit_expression_cb expression_function_call_post_order;
	mCc_ast_visit_expression_cb expression_identifier_post_order;
	mCc_ast_visit_expression_cb expression_array_identifier_post_order;
	mCc_ast_visit_expression_cb expression_unary_op_post_order;

	// literal
	mCc_ast_visit_literal_cb literal;
	mCc_ast_visit_literal_cb literal_int;
	mCc_ast_visit_literal_cb literal_float;
	mCc_ast_visit_literal_cb literal_bool;
	mCc_ast_visit_literal_cb literal_string;

	mCc_ast_visit_literal_cb literal_post_order;
	mCc_ast_visit_literal_cb literal_int_post_order;
	mCc_ast_visit_literal_cb literal_float_post_order;
	mCc_ast_visit_literal_cb literal_bool_post_order;
	mCc_ast_visit_literal_cb literal_string_post_order;

	// assignment
	mCc_ast_visit_assignment_cb assignment;
	mCc_ast_visit_assignment_cb assignment_primitive;
	mCc_ast_visit_assignment_cb assignment_array;

	mCc_ast_visit_assignment_cb assignment_post_order;
	mCc_ast_visit_assignment_cb assignment_primitive_post_order;
	mCc_ast_visit_assignment_cb assignment_array_post_order;

	// declaration
	// use this for preorder
	mCc_ast_visit_declaration_cb declaration;
	mCc_ast_visit_declaration_cb declaration_type;
	mCc_ast_visit_declaration_cb declaration_primitive;
	mCc_ast_visit_declaration_cb declaration_array;

	mCc_ast_visit_declaration_cb declaration_post_order;
	mCc_ast_visit_declaration_cb declaration_type_post_order;
	mCc_ast_visit_declaration_cb declaration_primitive_post_order;
	mCc_ast_visit_declaration_cb declaration_array_post_order;

	// function
	mCc_ast_visit_function_call_cb function_call;
	mCc_ast_visit_function_def_cb function_def;
	mCc_ast_visit_function_def_cb function_def_type;

	mCc_ast_visit_function_call_cb function_call_post_order;
	mCc_ast_visit_function_def_cb function_def_post_order;
	mCc_ast_visit_function_def_cb function_def_type_post_order;

	/* at enter scope => manage symtab, add declarations*/
	mCc_ast_scope_cb function_def_enter_scope;
	mCc_ast_scope_cb function_def_leave_scope;
	/*=====================================================*/

	// identifier
	mCc_ast_visit_identifier_cb identifier;

	// program
	mCc_ast_visit_program_cb program;
	mCc_ast_visit_program_cb program_post_order;
	// statement
	mCc_ast_visit_statement_cb statement;
	mCc_ast_visit_statement_cb statement_if;
	mCc_ast_visit_statement_cb statement_while;
	mCc_ast_visit_statement_cb statement_return;
	mCc_ast_visit_statement_cb statement_declaration;
	mCc_ast_visit_statement_cb statement_assignment;
	mCc_ast_visit_statement_cb statement_expression;

	mCc_ast_visit_statement_cb statement_post_order;
	mCc_ast_visit_statement_cb statement_if_post_order;
	mCc_ast_visit_statement_cb statement_while_post_order;
	mCc_ast_visit_statement_cb statement_return_post_order;
	mCc_ast_visit_statement_cb statement_declaration_post_order;
	mCc_ast_visit_statement_cb statement_assignment_post_order;
	mCc_ast_visit_statement_cb statement_expression_post_order;

	/* at enter scope => manage symtab, add declarations*/
	mCc_ast_scope_cb statement_if_enter_scope;
	mCc_ast_scope_cb statement_if_leave_scope;
	mCc_ast_scope_cb statement_while_enter_scope;
	mCc_ast_scope_cb statement_while_leave_scope;
	/*=====================================================*/
};

#ifdef __cplusplus
}
#endif

#endif
