#ifndef MCC_AST_IDENTIFIER_H
#define MCC_AST_IDENTIFIER_H

#include "mCc/ast/basis/ast_node.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_ast_identifier {
	struct mCc_ast_node node;
	/* It is not const intentionally! */
	char *identifier_name;
};

struct mCc_ast_identifier *mCc_ast_new_identifier(char *name);

void mCc_ast_delete_identifier(struct mCc_ast_identifier *name);

#ifdef __cplusplus
}
#endif

#endif
