#ifndef MCC_AST_LITERAL_H
#define MCC_AST_LITERAL_H

#include "mCc/ast/basis/ast_node.h"
#include <stdbool.h>
#include "ast_data_type.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mCc_ast_literal {
	struct mCc_ast_node node;

	enum mCc_ast_data_type type;
	union {
		/* MCC_AST_DATA_TYPE_INT */
		long i_value;

		/* MCC_AST_DATA_TYPE_FLOAT */
		double f_value;

		/* MCC_AST_DATA_TYPE_BOOL */
		bool b_value;

		/* MCC_AST_DATA_TYPE_STRING */
		const char *s_value;
	};
};

struct mCc_ast_literal *mCc_ast_new_literal_int(long value);

struct mCc_ast_literal *mCc_ast_new_literal_float(double value);

/* added */
struct mCc_ast_literal *mCc_ast_new_literal_bool(bool value);

struct mCc_ast_literal *mCc_ast_new_literal_string(const char *value);

void mCc_ast_delete_literal(struct mCc_ast_literal *literal);

#ifdef __cplusplus
}
#endif

#endif
