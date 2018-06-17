
# find BISON + FLEX targets
# NOTE: they have to be in upper-case
find_package(BISON)
find_package(FLEX)

# build flex- and bison-targets
flex_target(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/scanner.h)
# add -rall to bison-compile-flags if conflicts on parser detected
bison_target(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c COMPILE_FLAGS "-Wall" DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)

add_flex_bison_dependency(scanner parser)

# helper-functions
add_library(mCc_parser_helper SHARED general/parser_helper.c)
add_library(mCc_print_helper SHARED general/print_helper.c)

# basic ast
add_library(mCc_ast SHARED  ast/basis/ast_assignment.c
							ast/basis/ast_declaration.c
							ast/basis/ast_expression.c
							ast/basis/ast_function.c							
							ast/basis/ast_identifier.c					
							ast/basis/ast_literal.c							
							ast/basis/ast_program.c							
							ast/basis/ast_statement.c
							# to free the associated symtab-info at identifiers
							# maybe a better solution?
							symtab/symtab_node.c)

# visitors
add_library(mCc_visit SHARED ast/visit/ast_visit_assignment.c
							ast/visit/ast_visit_declaration.c 
							ast/visit/ast_visit_expression.c
							ast/visit/ast_visit_function.c							
							ast/visit/ast_visit_identifier.c							
							ast/visit/ast_visit_literal.c
							ast/visit/ast_visit_program.c														
							ast/visit/ast_visit_statement.c)

# prints
add_library(mCc_print SHARED ast/print/ast_basic_printing.c
							ast/print/ast_print.c 
							ast/print/ast_print_assignment.c
							ast/print/ast_print_declaration.c 
							ast/print/ast_print_expression.c
							ast/print/ast_print_function.c							
							ast/print/ast_print_identifier.c							
							ast/print/ast_print_literal.c
							ast/print/ast_print_program.c														
							ast/print/ast_print_statement.c)
							
# tac
add_library(mCc_tac SHARED tac/basis/basic_tac.c
							tac/basis/tac.c 
							tac/tac_utils.c
							tac/basis/tac_assignment.c
							tac/basis/tac_declaration.c 
							tac/basis/tac_expression.c
							tac/basis/tac_function.c
							tac/basis/tac_program.c														
							tac/basis/tac_statement.c)
							
#tac print
add_library(mCc_tac_print SHARED tac/tac_print.c)

# symbol-table-handler (for building the symbol-table and validation)
add_library(mCc_symtab SHARED symtab/handler/symtab_handle_scope.c
							symtab/handler/symtab_handle_function.c
							symtab/handler/symtab_handle_identifier.c
							symtab/handler/symtab_handle_declaration.c
							symtab/handler/symtab_handle_assignment.c
							symtab/handler/symtab_handle_expression.c							
							symtab/handler/symtab_handle_program.c																					
							symtab/handler/symtab_handle_statement.c																					
							symtab/symbol_table.c
							symtab/symtab_check.c
							symtab/validator/validator.c
							symtab/validator/validator_helper.c)

add_library(mCc_semantic_error_print SHARED symtab/symtab_error_print.c
							symtab/print/error_printer.c)

add_library(mCc_assembly SHARED assembly/assembly_generator.c
								assembly/generator/assembly_argument.c
								assembly/generator/assembly_arithmetic_op.c
								assembly/generator/assembly_assignment.c
								assembly/generator/assembly_binary_op_logical.c
								assembly/generator/assembly_jump.c
								assembly/generator/assembly_function.c
								assembly/generator/assembly_unary_op.c
								assembly/generator/assembly_return.c
								assembly/generator/assembly_param.c
								assembly/generator/assembly_label.c
								assembly/generator/assembly_declaration.c
								assembly/utils/assembly_offset.c								
								assembly/utils/assembly_general.c
								assembly/utils/assembly_utils.c
								assembly/utils/assembly_formatter.c
								assembly/utils/assembly_template.c)
																												
# to use strdup => global compile-flag?
set_property(TARGET mCc_symtab PROPERTY COMPILE_FLAGS "-D_POSIX_C_SOURCE=200809L")
set_property(TARGET mCc_tac PROPERTY COMPILE_FLAGS "-D_POSIX_C_SOURCE=200809L")

# intermediate
target_link_libraries(mCc_symtab ext_log_c ext_map)

# setup mCc_lib
add_library(mCc_lib SHARED ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})
set_property(TARGET mCc_lib PROPERTY COMPILE_FLAGS "-D_POSIX_C_SOURCE=200809L")

# link remaining
target_link_libraries(mCc_lib 
				mCc_semantic_error_print 
				mCc_assembly 
				mCc_tac 
				mCc_tac_print 
				mCc_print 
				mCc_ast 
				mCc_symtab 
				mCc_visit 
				mCc_parser_helper
				mCc_print_helper)
