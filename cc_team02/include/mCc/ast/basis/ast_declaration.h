#ifndef MCC_AST_DECLARATION_H
#define MCC_AST_DECLARATION_H

#include <stddef.h>

#include "mCc/ast/basis/ast_node.h"
#include "mCc/ast/basis/ast_identifier.h"

#ifdef __cplusplus
extern "C" {
#endif

enum mCc_ast_declaration_type {
	MCC_AST_DECLARATION_PRIMITIVE,
	MCC_AST_DECLARATION_ARRAY
};

struct mCc_ast_declaration {
	struct mCc_ast_node node;

	enum mCc_ast_declaration_type declaration_type;
	enum mCc_ast_literal_type data_type;

	union {
		/* MCC_AST_IDENTIFIER */
		struct mCc_ast_identifier identifier;

		/* MCC_AST_DECLARATION_TYPE_ARRAY */
		struct {
			struct mCc_ast_identifier array_identifier;
			size_t size;
		};
	};
};

struct mCc_ast_declaration *
mCc_ast_new_primitive_declaration(enum mCc_ast_literal_type data_type,
                                  const char *identifier);

struct mCc_ast_declaration *
mCc_ast_new_array_declaration(enum mCc_ast_literal_type data_type,
                              const char *identifier, size_t size);

void mCc_ast_delete_primitive_declaration(struct mCc_ast_declaration *name);

void mCc_ast_delete_array_declaration(struct mCc_ast_declaration *name);

#ifdef __cplusplus
}
#endif

#endif
