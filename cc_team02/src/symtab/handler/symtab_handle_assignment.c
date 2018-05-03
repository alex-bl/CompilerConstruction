#include "mCc/symtab/handler/symtab_handle_assignment.h"

#include <assert.h>
#include <stddef.h>

#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/typecheck.h"
#include "mCc/symtab/validator/validator.h"

// called post orderly
void mCc_symtab_handle_primitive_assignment_post_order(
    struct mCc_ast_assignment *assignment, void *data)
{
	assert(assignment);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	mCc_process_validation_without_call_back(
	    mCc_typecheck_validate_type_assignment, info_holder->symbol_table,
	    assignment, info_holder);
}

void mCc_symtab_handle_array_assignment_post_order(
    struct mCc_ast_assignment *assignment, void *data)
{
	assert(assignment);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	mCc_process_validation_without_call_back(
	    mCc_typecheck_validate_type_assignment, info_holder->symbol_table,
	    assignment, info_holder);

	mCc_process_validation_without_call_back(
	    mCc_typecheck_validate_type_assignment_arr_expr,
	    info_holder->symbol_table, assignment, info_holder);
}
