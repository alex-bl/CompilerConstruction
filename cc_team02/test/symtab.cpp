#include <stdbool.h>
#include <stddef.h>

#include "gtest/gtest.h"

#include "mCc/ast.h"
#include "mCc/symtab/symbol_table.h"
#include "mCc_test/mCc_test_utils.h"
#include "map.h"

//============================================ symtab_node
TEST(SymtabNode, NewParameterRef)
{
	struct mCc_ast_identifier *identifier =
	    mCc_test_build_const_test_identifier("var");

	struct mCc_symtab_parameter_ref *param =
	    mCc_symtab_new_parameter_ref(identifier);

	ASSERT_STREQ(param->identifier->identifier_name,
	             identifier->identifier_name);

	mCc_symtab_delete_symtab_parameter_ref(param);
	mCc_ast_delete_identifier(identifier);
}

TEST(SymtabNode, CreateDeclarationNodePrimitive)
{
	struct mCc_ast_declaration *decl =
	    mCc_test_build_test_declaration("a", MCC_AST_DATA_TYPE_INT);

	struct mCc_symbol_table_node *symtab_node =
	    mCc_symtab_new_declaration_node(decl);

	ASSERT_EQ(MCC_SYM_TAB_IDENTIFIER_VARIABLE_PRIMITIVE,
	          symtab_node->entry_type);
	ASSERT_EQ(0L, (long)symtab_node->size);

	mCc_ast_delete_declaration(decl);
	mCc_symtab_delete_symtab_node(symtab_node);
}

TEST(SymtabNode, CreateDeclarationNodeArray)
{
	struct mCc_ast_declaration *decl =
	    mCc_test_build_test_array_declaration("a", MCC_AST_DATA_TYPE_INT, 100);

	struct mCc_symbol_table_node *symtab_node =
	    mCc_symtab_new_declaration_node(decl);

	ASSERT_EQ(MCC_SYM_TAB_IDENTIFIER_VARIABLE_ARRAY, symtab_node->entry_type);
	ASSERT_EQ(100L, (long)symtab_node->size);

	mCc_symtab_delete_symtab_node(symtab_node);
	mCc_ast_delete_declaration(decl);
}

TEST(SymtabNode, CreateFunctionDefNodeWithoutParams)
{
	struct mCc_ast_expression *return_expr =
	    mCc_test_build_test_lit_expression(10);
	struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(MCC_AST_DATA_TYPE_INT, "func",
	                                     return_expr);

	struct mCc_symbol_table_node *symtab_node =
	    mCc_symtab_new_function_def_node(function_def);

	ASSERT_FALSE(symtab_node->already_defined);
	ASSERT_EQ(MCC_SYM_TAB_IDENTIFIER_FUNCTION, symtab_node->entry_type);
	EXPECT_EQ(NULL, symtab_node->next_parameter);

	mCc_symtab_delete_symtab_node(symtab_node);
	mCc_ast_delete_function_def(function_def);
}

TEST(SymtabNode, CreateFunctionDefNodeWithParams)
{
	struct mCc_ast_expression *return_expr =
	    mCc_test_build_test_lit_expression(10);
	struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(MCC_AST_DATA_TYPE_INT, "func",
	                                     return_expr);

	struct mCc_ast_declaration *param_0 =
	    mCc_test_build_test_declaration("a", MCC_AST_DATA_TYPE_INT);

	struct mCc_ast_declaration *param_1 =
	    mCc_test_build_test_declaration("b", MCC_AST_DATA_TYPE_FLOAT);

	param_0->next_declaration = param_1;
	function_def->first_parameter = param_0;

	struct mCc_symbol_table_node *symtab_node =
	    mCc_symtab_new_function_def_node(function_def);

	ASSERT_FALSE(symtab_node->already_defined);
	ASSERT_EQ(MCC_SYM_TAB_IDENTIFIER_FUNCTION, symtab_node->entry_type);

	struct mCc_symtab_parameter_ref *next_parameter =
	    symtab_node->next_parameter;

	ASSERT_STREQ("a", next_parameter->identifier->identifier_name);
	ASSERT_STREQ("b",
	             next_parameter->next_parameter->identifier->identifier_name);
	EXPECT_EQ(NULL,
	          symtab_node->next_parameter->next_parameter->next_parameter);

	mCc_symtab_delete_symtab_node(symtab_node);
	mCc_ast_delete_function_def(function_def);
}

// just for completeness :D
TEST(SymtabNode, DeleteSymtabParameterRef)
{
	struct mCc_ast_identifier *identifier =
	    mCc_test_build_const_test_identifier("var");

	struct mCc_symtab_parameter_ref *param =
	    mCc_symtab_new_parameter_ref(identifier);

	ASSERT_TRUE(param != NULL);
	mCc_symtab_delete_symtab_parameter_ref(param);
	mCc_ast_delete_identifier(identifier);
}

// just for completeness :D
TEST(SymtabNode, DeleteSymtabNode)
{
	struct mCc_ast_declaration *decl =
	    mCc_test_build_test_declaration("a", MCC_AST_DATA_TYPE_INT);

	struct mCc_symbol_table_node *symtab_node =
	    mCc_symtab_new_declaration_node(decl);

	ASSERT_TRUE(symtab_node != NULL);

	mCc_ast_delete_declaration(decl);
	mCc_symtab_delete_symtab_node(symtab_node);
}

//============================================ symbol_table
TEST(Symtab, CreateNewSymbolTableBasic)
{
	struct mCc_symbol_table *symtab = mCc_symtab_new_symbol_table(NULL, 0);

	ASSERT_TRUE(symtab != NULL);
	ASSERT_EQ(0, symtab->scope_level);
	EXPECT_EQ(NULL, symtab->parent);
	ASSERT_TRUE(&symtab->table != NULL);

	mCc_symtab_delete_symbol_table(symtab);
}

TEST(Symtab, CreateNewSymbolTableWithParent)
{

	struct mCc_symbol_table *symtab_parent =
	    mCc_symtab_new_symbol_table(NULL, 0);
	struct mCc_symbol_table *symtab =
	    mCc_symtab_new_symbol_table(symtab_parent, 1);

	ASSERT_TRUE(symtab != NULL);
	ASSERT_TRUE(symtab_parent != NULL);

	ASSERT_EQ(1, symtab->scope_level);
	ASSERT_EQ(0, symtab_parent->scope_level);

	EXPECT_EQ(NULL, symtab_parent->parent);
	ASSERT_TRUE(symtab->parent != NULL);

	mCc_symtab_delete_symbol_table(symtab);
	mCc_symtab_delete_symbol_table(symtab_parent);
}

TEST(Symtab, InsertNode)
{
	struct mCc_symbol_table *symtab = mCc_symtab_new_symbol_table(NULL, 0);
	struct mCc_ast_declaration *decl =
	    mCc_test_build_test_declaration("var", MCC_AST_DATA_TYPE_INT);
	struct mCc_symbol_table_node *symtab_node =
	    mCc_symtab_new_declaration_node(decl);

	ASSERT_TRUE(symtab != NULL);
	ASSERT_TRUE(decl != NULL);
	ASSERT_TRUE(symtab_node != NULL);

	mCc_symtab_insert_node(symtab, decl->identifier, symtab_node);
	struct mCc_symbol_table_node *result =
	    mCc_symtab_lookup(symtab, decl->identifier, true);

	ASSERT_TRUE(result != NULL);

	mCc_ast_delete_declaration(decl);
	mCc_symtab_delete_symbol_table(symtab);
}

TEST(Symtab, InsertVarNode)
{
	struct mCc_symbol_table *symtab = mCc_symtab_new_symbol_table(NULL, 0);
	struct mCc_ast_declaration *decl =
	    mCc_test_build_test_declaration("var", MCC_AST_DATA_TYPE_INT);

	ASSERT_TRUE(symtab != NULL);
	ASSERT_TRUE(decl != NULL);

	mCc_symtab_insert_var_node(symtab, decl);
	struct mCc_symbol_table_node *result =
	    mCc_symtab_lookup(symtab, decl->identifier, true);

	ASSERT_TRUE(result != NULL);
	mCc_ast_delete_declaration(decl);
	mCc_symtab_delete_symbol_table(symtab);
}

TEST(Symtab, InsertFunctionDefNode)
{
	struct mCc_ast_expression *return_expr =
	    mCc_test_build_test_lit_expression(10);
	struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(MCC_AST_DATA_TYPE_INT, "func",
	                                     return_expr);

	struct mCc_symbol_table *symtab = mCc_symtab_new_symbol_table(NULL, 0);
	ASSERT_TRUE(symtab != NULL);
	ASSERT_TRUE(function_def != NULL);

	mCc_symtab_insert_function_def_node(symtab, function_def);
	struct mCc_symbol_table_node *result =
	    mCc_symtab_lookup(symtab, function_def->identifier, true);

	ASSERT_TRUE(result != NULL);
	mCc_ast_delete_function_def(function_def);
	mCc_symtab_delete_symbol_table(symtab);
}

TEST(Symtab, LookupParentScope)
{
	struct mCc_ast_expression *return_expr =
	    mCc_test_build_test_lit_expression(10);
	struct mCc_ast_function_def *function_def =
	    mCc_test_build_test_function_def(MCC_AST_DATA_TYPE_INT, "func",
	                                     return_expr);
	struct mCc_symbol_table *symtab_parent =
	    mCc_symtab_new_symbol_table(NULL, 0);
	struct mCc_symbol_table *symtab =
	    mCc_symtab_new_symbol_table(symtab_parent, 1);

	ASSERT_TRUE(symtab != NULL);
	ASSERT_TRUE(symtab_parent != NULL);

	mCc_symtab_insert_function_def_node(symtab_parent, function_def);
	struct mCc_symbol_table_node *result =
	    mCc_symtab_lookup(symtab, function_def->identifier, true);

	EXPECT_EQ(NULL, result);

	result = mCc_symtab_lookup(symtab, function_def->identifier, false);

	ASSERT_TRUE(result != NULL);

	mCc_ast_delete_function_def(function_def);
	mCc_symtab_delete_symbol_table(symtab);
	mCc_symtab_delete_symbol_table(symtab_parent);
}

// just for completeness :D
TEST(Symtab, DeleteSymtab)
{
	struct mCc_symbol_table *symtab = mCc_symtab_new_symbol_table(NULL, 0);

	ASSERT_TRUE(symtab != NULL);

	mCc_symtab_delete_symbol_table(symtab);
}
