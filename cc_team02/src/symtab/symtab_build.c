#include "mCc/symtab_build.h"

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "log.h"
#include "mCc/ast_print_visitors.h"
#include "mCc/ast_visit.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc/symtab/validator/validator.h"
#include "mCc/symtab_handler.h"

//"global" visitor needed
static struct mCc_ast_visitor
symtab_visitor(struct mCc_symtab_and_validation_holder *symtab_info_holder)
{
	assert(symtab_info_holder);

	return (struct mCc_ast_visitor){

		.traversal = MCC_AST_VISIT_DEPTH_FIRST,
		.order = MCC_AST_VISIT_PRE_ORDER,
		.userdata = symtab_info_holder,
		// TODO: declaration-handler -> in function AND in statement
		// (declaration-handler not needed anymore)
		//===============================
		// needed for symtab-construction:
		.function_def_enter_scope = mCc_symtab_enter_scope,
		.function_def_leave_scope = mCc_symtab_leave_scope,
		.statement_if_enter_scope = mCc_symtab_enter_scope,
		.statement_if_leave_scope = mCc_symtab_leave_scope,
		.statement_while_enter_scope = mCc_symtab_enter_scope,
		.statement_while_leave_scope = mCc_symtab_leave_scope,
		// needed
		.identifier = mCc_symtab_handle_identifier,
		// identifier => get from symtab an link information
		//.function
		.function_def = mCc_symtab_handle_function_def,
		.function_call = mCc_symtab_handle_function_call,
		//.declaration => add declarations to current symtab
		.declaration_primitive = mCc_symtab_handle_declaration_primitive,
		.declaration_array = mCc_symtab_handle_declaration_array,

		//=================================

		// maybe not needed inside symtab-construction
		//.expression
		.expression_literal = NULL,
		.expression_binary_op = NULL,
		.expression_parenth = NULL,
		.expression_function_call = NULL,
		.expression_identifier = NULL,
		.expression_array_identifier = NULL,
		.expression_unary_op = NULL,
		//.literal
		.literal_int = NULL,
		.literal_float = NULL,
		.literal_bool = NULL,
		.literal_string = NULL,
		//.assignment
		.assignment_primitive = NULL,
		.assignment_array = NULL,
		// program
		.program = NULL,
		// statement
		.statement_if = NULL,
		.statement_while = NULL,
		.statement_return = NULL,
		.statement_assignment = NULL,
		.statement_expression = NULL,
		.statement_declaration = NULL,
	};
}

static struct mCc_ast_function_def *
create_buildin(const char *identifier, struct mCc_ast_declaration *parameter,
               enum mCc_ast_data_type return_type)
{
	struct mCc_ast_function_def *def =
	    mCc_ast_new_non_parameterized_function_def(
	        mCc_ast_new_identifier(strdup(identifier)), return_type, NULL);
	def->first_parameter = parameter;
	return def;
}

static struct mCc_ast_declaration *
create_declaration(const char *identifier, enum mCc_ast_data_type type)
{
	return mCc_ast_new_primitive_declaration(
	    type, mCc_ast_new_identifier(strdup(identifier)));
}

/*Parameter is a new scope*/
static void
insert_declaration_to_symtab(struct mCc_symbol_table *parent,
                             struct mCc_ast_declaration *declaration,
                             int *scope_level)
{
	*scope_level = *scope_level + 1;
	struct mCc_symbol_table *symbol_table =
	    mCc_symtab_new_symbol_table(NULL, *scope_level);
	mCc_symtab_insert_var_node(symbol_table, declaration);
	symbol_table->parent = parent;
}

static void add_buildins(struct mCc_symbol_table *symbol_table,
                         int *scope_level)
{
	struct mCc_ast_declaration *print_msg =
	    create_declaration("msg", MCC_AST_DATA_TYPE_STRING);
	mCc_symtab_insert_function_def_node(
	    symbol_table,
	    create_buildin("print", print_msg, MCC_AST_DATA_TYPE_VOID));
	insert_declaration_to_symtab(symbol_table, print_msg, scope_level);

	mCc_symtab_insert_function_def_node(
	    symbol_table, create_buildin("print_nl", NULL, MCC_AST_DATA_TYPE_VOID));

	struct mCc_ast_declaration *print_x_int =
	    create_declaration("x", MCC_AST_DATA_TYPE_INT);
	mCc_symtab_insert_function_def_node(
	    symbol_table,
	    create_buildin("print_int", print_x_int, MCC_AST_DATA_TYPE_VOID));
	insert_declaration_to_symtab(symbol_table, print_x_int, scope_level);

	struct mCc_ast_declaration *print_x_float =
	    create_declaration("x", MCC_AST_DATA_TYPE_FLOAT);
	mCc_symtab_insert_function_def_node(
	    symbol_table,
	    create_buildin("print_float", print_x_float, MCC_AST_DATA_TYPE_VOID));
	insert_declaration_to_symtab(symbol_table, print_x_float, scope_level);

	mCc_symtab_insert_function_def_node(
	    symbol_table, create_buildin("read_int", NULL, MCC_AST_DATA_TYPE_INT));

	mCc_symtab_insert_function_def_node(
	    symbol_table,
	    create_buildin("read_float", NULL, MCC_AST_DATA_TYPE_FLOAT));
}

// TODO: return status
struct mCc_validation_status_result *
mCc_symtab_build_program(struct mCc_ast_program *program)
{
	assert(program);

	struct mCc_symbol_table *symbol_table =
	    mCc_symtab_new_symbol_table(NULL, 0);
	if (!symbol_table) {
		log_error("Malloc failed: Could not init top-level symbol-table");
		return NULL;
	}
	log_debug("Top-level symbol-table with scope %d created",
	          symbol_table->scope_level);

	struct mCc_symtab_and_validation_holder info_holder;

	info_holder.symbol_table = symbol_table;
	info_holder.first_semantic_error = NULL;
	info_holder.scope_level = 0;

	// add build-in-functions
	add_buildins(symbol_table, &info_holder.scope_level);

	// TODO: add build-ins
	struct mCc_ast_visitor visitor = symtab_visitor(&info_holder);

	mCc_ast_visit_program(program, &visitor);

	log_debug("Leaving symbol-table with scope %d", symbol_table->scope_level);
	// free symtab
	mCc_symtab_delete_symbol_table(symbol_table);

	// there wasn't any error
	if (!info_holder.first_semantic_error) {
		info_holder.first_semantic_error = mCc_validator_new_validation_result(
		    MCC_VALIDATION_STATUS_VALID, "");
	}

	return info_holder.first_semantic_error;
}

// TODO: are they required?
void mCc_symtab_build_assignment(struct mCc_ast_assignment *assignment)
{
	assert(assignment);
}

void mCc_symtab_build_declaration(struct mCc_ast_declaration *declaration)
{
	assert(declaration);
}

void mCc_symtab_build_expression(struct mCc_ast_expression *expression)
{
	assert(expression);
}

void mCc_symtab_build_function_def(struct mCc_ast_function_def *function_def)
{

	assert(function_def);
}

void mCc_symtab_build_function_call(struct mCc_ast_function_call *function_call)
{
	assert(function_call);
}

void mCc_symtab_build_identifier(struct mCc_ast_identifier *identifier)
{

	assert(identifier);
}

void mCc_symtab_build_literal(struct mCc_ast_literal *literal)
{

	assert(literal);
}

void mCc_symtab_build_statement(struct mCc_ast_statement *statement)
{

	assert(statement);
}
