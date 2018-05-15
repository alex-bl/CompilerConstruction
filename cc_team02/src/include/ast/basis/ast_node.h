#ifndef MCC_AST_NODE_H
#define MCC_AST_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_ast_source_location {
	int start_line;
	int start_col;
	int end_line;
	int end_col;
};

/* Data contained by every AST node. */
struct mCc_ast_node {
	struct mCc_ast_source_location sloc;
};

#ifdef __cplusplus
}
#endif

#endif
