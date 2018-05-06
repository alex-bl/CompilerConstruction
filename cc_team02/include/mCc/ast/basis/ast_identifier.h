#ifndef MCC_AST_IDENTIFIER_H
#define MCC_AST_IDENTIFIER_H

#include "mCc/ast/basis/ast_node.h"
#include "mCc/symtab/symtab_node_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_ast_identifier {
	struct mCc_ast_node node;
	/* It is not const intentionally! */
	char *identifier_name;
	/* link the corresponding node from the symbol-table*/
	struct mCc_symbol_table_node *symtab_info;
	// for semantic checks
	struct mCc_validation_status_result *semantic_error;
};

struct mCc_ast_identifier *mCc_ast_new_identifier(char *name);

void mCc_ast_delete_identifier(struct mCc_ast_identifier *name);

#ifdef __cplusplus
}
#endif

#endif
