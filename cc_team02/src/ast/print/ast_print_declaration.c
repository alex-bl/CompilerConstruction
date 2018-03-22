#include <assert.h>

#include "mCc/ast/print/ast_print_declaration.h"
#include "mCc/ast/print/ast_basic_printing.h"
#include "mCc/ast/visit/ast_visit_declaration.h"

void mCc_ast_print_dot_declaration(FILE *out,
                                   struct mCc_ast_declaration *declaration)
{
	/*TODO*/
}

static struct mCc_ast_visitor print_dot_visitor(FILE *out)
{
	assert(out);

	return (struct mCc_ast_visitor){

	};
}
