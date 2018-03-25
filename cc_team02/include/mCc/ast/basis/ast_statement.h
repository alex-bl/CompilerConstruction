#ifndef MCC_AST_STATEMENT_H
#define MCC_AST_STATEMENT_H

#include "mCc/ast/basis/ast_assignment.h"
#include "mCc/ast/basis/ast_declaration.h"
#include "mCc/ast/basis/ast_expression.h"
#include "mCc/ast/basis/ast_node.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_ast_statement_type {
	MCC_AST_STATEMENT_IF,
	MCC_AST_STATEMENT_WHILE,
	MCC_AST_STATEMENT_RETURN,

	MCC_AST_STATEMENT_DECLARATION,
	MCC_AST_STATEMENT_ASSIGNMENT,
	MCC_AST_STATEMENT_EXPRESSION
};

struct mCc_ast_statement {
	struct mCc_ast_node node;

	enum mCc_ast_statement_type statement_type;

	struct mCc_ast_statement *next_statement;

	union {

		// if
		struct {
			/* MCC_AST_EXPRESSION */
			struct mCc_ast_expression *condition_expression;
			/* MCC_AST_STATEMENT */
			struct mCc_ast_statement *if_statement;
			/* MCC_AST_STATEMENT */
			struct mCc_ast_statement *else_statement;
		};

		// while
		struct {
			struct mCc_ast_expression *loop_condition_expression;
			/* MCC_AST_STATEMENT */
			struct mCc_ast_statement *while_statement;
		};

		// return
		/* MCC_AST_EXPRESSION */
		struct mCc_ast_expression *return_expression;

		/* MCC_AST_EXPRESSION => this as separate attribute?*/
		struct mCc_ast_expression *expression;

		/* MCC_AST_DECLARATION*/
		struct mCc_ast_declaration *declaration;

		/* MCC_AST_ASSIGNMENT */
		struct mCc_ast_assignment *assignment;
	};
};

struct mCc_ast_statement *
mCc_ast_new_if_statement(struct mCc_ast_expression *condition_expr,
                         struct mCc_ast_statement *if_stmt,
                         struct mCc_ast_statement *else_stmt);

struct mCc_ast_statement *
mCc_ast_new_while_statement(struct mCc_ast_expression *loop_expr,
                            struct mCc_ast_statement *while_stmt);
struct mCc_ast_statement *
mCc_ast_new_return_statement(struct mCc_ast_statement *return_stmt);

struct mCc_ast_statement *
mCc_ast_new_expression_statement(struct mCc_ast_expression *expression_stmt);

struct mCc_ast_statement *
mCc_ast_new_declaration_statement(struct mCc_ast_declaration *declaration);

struct mCc_ast_statement *
mCc_ast_new_assign_statement(struct mCc_ast_assignment *assignment);

void mCc_ast_delete_statement(struct mCc_ast_statement *stmt);

#ifdef __cplusplus
}
#endif

#endif
