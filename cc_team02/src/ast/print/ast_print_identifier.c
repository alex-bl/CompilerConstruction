#include <stdlib.h>
#include <assert.h>

#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/print/ast_print_identifier.h"
#include "mCc/ast/visit/ast_visit_identifier.h"

void mCc_ast_print_dot_identifier(FILE *out,
                                  struct mCc_ast_identifier *identifier)
{
	/*TODO*/
}

static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

	};
}
