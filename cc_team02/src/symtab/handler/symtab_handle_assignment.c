#include "mCc/symtab/handler/symtab_handle_assignment.h"

#include <assert.h>
#include <stddef.h>

#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/typecheck.h"
#include "mCc/symtab/validator/validator.h"

void mCc_symtab_handle_primitive_assignment(
    struct mCc_ast_assignment *assignment, void *data)
{
	assert(assignment);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	//"prefetch" symtab info for error-printing
	assignment->identifier->symtab_info = mCc_symtab_lookup(
	    info_holder->symbol_table, assignment->identifier, false);

	mCc_process_validation(mCc_typecheck_validate_type_assignment, NULL,
	                       info_holder->symbol_table, assignment, info_holder,
	                       NULL);
}

void mCc_symtab_handle_array_assignment(struct mCc_ast_assignment *assignment,
                                        void *data)
{
	assert(assignment);
	assert(data);

	struct mCc_symtab_and_validation_holder *info_holder =
	    (struct mCc_symtab_and_validation_holder *)data;

	//"prefetch" symtab info for error-printing
	assignment->identifier->symtab_info = mCc_symtab_lookup(
	    info_holder->symbol_table, assignment->identifier, false);

	mCc_process_validation(mCc_typecheck_validate_type_assignment, NULL,
	                       info_holder->symbol_table, assignment, info_holder,
	                       NULL);

	mCc_process_validation(mCc_typecheck_validate_type_assignment_arr_expr,
	                       NULL, info_holder->symbol_table, assignment,
	                       info_holder, NULL);
}
