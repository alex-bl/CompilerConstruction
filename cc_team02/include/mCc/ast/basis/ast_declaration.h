#ifndef MCC_AST_DECLARATION_H
#define MCC_AST_DECLARATION_H

#include "mCc/ast/basis/ast_data_type.h"
#include "mCc/ast/basis/ast_identifier.h"
#include "mCc/ast/basis/ast_node.h"
#include <stddef.h>

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
	enum mCc_ast_data_type data_type;

	struct mCc_ast_declaration *next_declaration;
	// for semantic checks
	struct mCc_validation_status_result *semantic_error;

	union {
		/* MCC_AST_IDENTIFIER */
		struct mCc_ast_identifier *identifier;

		/* MCC_AST_DECLARATION_TYPE_ARRAY */
		struct {
			struct mCc_ast_identifier *array_identifier;
			size_t size;
		};
	};
};

struct mCc_ast_declaration *
mCc_ast_new_primitive_declaration(enum mCc_ast_data_type data_type,
                                  struct mCc_ast_identifier *identifier);

struct mCc_ast_declaration *
mCc_ast_new_array_declaration(enum mCc_ast_data_type data_type,
                              struct mCc_ast_identifier *identifier,
                              size_t size);

struct mCc_ast_identifier *
mCc_ast_get_declaration_identifier(struct mCc_ast_declaration *decl);

void mCc_ast_delete_declaration(struct mCc_ast_declaration *name);

#ifdef __cplusplus
}
#endif

#endif
