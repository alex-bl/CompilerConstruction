#ifndef MCC_AST_VISIT_H
#define MCC_AST_VISIT_H

#include "mCc/ast.h"

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
};

typedef void (*mCc_ast_expression_visitor)(struct mCc_ast_expression *, void *);
typedef void (*mCc_ast_literal_visitor)(struct mCc_ast_literal *, void *);

struct mCc_ast_visitor {
	enum mCc_ast_visit_traversal traversal;
	enum mCc_ast_visit_order order;

	void *userdata;

	mCc_ast_expression_visitor expression;
	mCc_ast_expression_visitor expression_literal;
	mCc_ast_expression_visitor expression_binary_op;
	mCc_ast_expression_visitor expression_parenth;

	mCc_ast_literal_visitor literal;
	mCc_ast_literal_visitor literal_int;
	mCc_ast_literal_visitor literal_float;
};

void mCc_ast_visit_expression(struct mCc_ast_expression *expression,
                              struct mCc_ast_visitor *visitor);

void mCc_ast_visit_literal(struct mCc_ast_literal *literal,
                           struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
