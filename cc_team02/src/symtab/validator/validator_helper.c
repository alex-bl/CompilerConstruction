#include "validator_helper.h"

#include <assert.h>
#include <stddef.h>

#include "log.h"

struct mCc_ast_statement *
mCc_validator_find_return_statement(struct mCc_ast_function_def *function_def)
{
	assert(function_def);
	struct mCc_ast_statement *next_statement = function_def->first_statement;
	if (!next_statement) {
		log_debug("Function '%s' has no statements",
		          function_def->identifier->identifier_name);
	}
	while (next_statement) {
		if (next_statement->statement_type == MCC_AST_STATEMENT_RETURN) {
			return next_statement;
		}
		next_statement = next_statement->next_statement;
	}
	return NULL;
}
