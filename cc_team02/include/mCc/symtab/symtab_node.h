#ifndef MCC_SYMTAB_NODE_H
#define MCC_SYMTAB_NODE_H

#include <stdbool.h>
#include <stddef.h>

#include "mCc/ast/basis/ast_data_type.h"
#include "mCc/symtab/symtab_node_types.h"
#include "mCc/ast/basis/ast_declaration.h"
#include "mCc/ast/basis/ast_function.h"
#include "mCc/ast/basis/ast_identifier.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * Creates a new parameter-reference
 *
 * @param identifier_name
 *
 * @return
 * 	A reference to a new parameter_ref or NULL in error-case
 */
struct mCc_symtab_parameter_ref *
mCc_symtab_new_parameter_ref(struct mCc_ast_identifier *identifier);

/**
 * Creates a new symbol-table node out of a declaration
 *
 * @param declaration
 * 		The ast-element of declaration
 * @return
 * 		A new symbol-table-node element
 */
struct mCc_symbol_table_node *
mCc_symtab_new_declaration_node(struct mCc_ast_declaration *declaration);

/**
 * Creates a new symbol-table node out of a function def
 *
 * @param function_def
 * 		The ast-element of function_def
 * @return
 * 		A new symbol-table-node element
 */
struct mCc_symbol_table_node *
mCc_symtab_new_function_def_node(struct mCc_ast_function_def *function_def);

void mCc_symtab_delete_symtab_parameter_ref(
    struct mCc_symtab_parameter_ref *ref);

void mCc_symtab_delete_symtab_node(struct mCc_symbol_table_node *node);

#ifdef __cplusplus
}
#endif

#endif
