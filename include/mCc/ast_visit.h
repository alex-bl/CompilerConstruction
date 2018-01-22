#ifndef MCC_AST_VISIT_H
#define MCC_AST_VISIT_H

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mCc_ast_expression_visitor)(struct mCc_ast_expression *, void *);
typedef void (*mCc_ast_literal_visitor)(struct mCc_ast_literal *, void *);

struct mCc_ast_visitor {
	/* some custom data provided to each callback */
	void *data;

	mCc_ast_expression_visitor expression;
	mCc_ast_expression_visitor expression_literal;
	mCc_ast_expression_visitor expression_binary_op;
	mCc_ast_expression_visitor expression_parenth;

	mCc_ast_literal_visitor literal;
	mCc_ast_literal_visitor literal_int;
	mCc_ast_literal_visitor literal_float;
};

enum mCc_ast_visit_order {
	MCC_AST_VISIT_PRE_ORDER,
	MCC_AST_VISIT_POST_ORDER,
};

/* Depth-First */

void mCc_ast_visit_expression_df(enum mCc_ast_visit_order order,
                                 struct mCc_ast_expression *expression,
                                 struct mCc_ast_visitor *visitor);

void mCc_ast_visit_literal(enum mCc_ast_visit_order order,
                           struct mCc_ast_literal *literal,
                           struct mCc_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
