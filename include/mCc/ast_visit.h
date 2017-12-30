#ifndef MCC_AST_VISIT_H
#define MCC_AST_VISIT_H

#include "mCc/ast.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mC_ast_expression_visitor)(struct mC_ast_expression *, void *);
typedef void (*mC_ast_literal_visitor)(struct mC_ast_literal *, void *);

struct mC_ast_visitor {
	/* some custom data provided to each callback */
	void *data;

	mC_ast_expression_visitor expression;
	mC_ast_expression_visitor expression_literal;
	mC_ast_expression_visitor expression_binary_op;
	mC_ast_expression_visitor expression_parenth;

	mC_ast_literal_visitor literal;
	mC_ast_literal_visitor literal_int;
	mC_ast_literal_visitor literal_float;
};

void mC_ast_visit_expression(struct mC_ast_expression *expression,
                             struct mC_ast_visitor *visitor);

void mC_ast_visit_literal(struct mC_ast_literal *literal,
                          struct mC_ast_visitor *visitor);

#ifdef __cplusplus
}
#endif

#endif
