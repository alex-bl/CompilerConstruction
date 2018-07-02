
# find BISON + FLEX targets
# NOTE: they have to be in upper-case
find_package(BISON)
find_package(FLEX)

# build flex- and bison-targets
flex_target(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/scanner.h)
# add -rall to bison-compile-flags if conflicts on parser detected
bison_target(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c COMPILE_FLAGS "-Wall" DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)

add_flex_bison_dependency(scanner parser)

add_library(mCc_lib	STATIC  ${BISON_parser_OUTPUTS} 
							${FLEX_scanner_OUTPUTS}
							# helper
							general/parser_helper.c
							general/print_helper.c
							# ast-basics
							ast/basis/ast_assignment.c
							ast/basis/ast_declaration.c
							ast/basis/ast_expression.c
							ast/basis/ast_function.c							
							ast/basis/ast_identifier.c					
							ast/basis/ast_literal.c							
							ast/basis/ast_program.c							
							ast/basis/ast_statement.c
							symtab/symtab_node.c				
							# visitors
							ast/visit/ast_visit_assignment.c
							ast/visit/ast_visit_declaration.c 
							ast/visit/ast_visit_expression.c
							ast/visit/ast_visit_function.c							
							ast/visit/ast_visit_identifier.c							
							ast/visit/ast_visit_literal.c
							ast/visit/ast_visit_program.c														
							ast/visit/ast_visit_statement.c				
							# ast-printers
							ast/print/ast_basic_printing.c
							ast/print/ast_print.c 
							ast/print/ast_print_assignment.c
							ast/print/ast_print_declaration.c 
							ast/print/ast_print_expression.c
							ast/print/ast_print_function.c							
							ast/print/ast_print_identifier.c							
							ast/print/ast_print_literal.c
							ast/print/ast_print_program.c														
							ast/print/ast_print_statement.c				
							# tac-basics
							tac/basis/basic_tac.c
							tac/basis/tac.c 
							tac/tac_utils.c
							tac/basis/tac_assignment.c
							tac/basis/tac_declaration.c 
							tac/basis/tac_expression.c
							tac/basis/tac_function.c
							tac/basis/tac_program.c														
							tac/basis/tac_statement.c
							# tac-print
							tac/tac_print.c
							tac/cfg/tac_cfg.c
							# semantic-check infrastructure
							symtab/handler/symtab_handle_scope.c
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
							symtab/validator/validator_helper.c														
							# error-printers
							symtab/symtab_error_print.c
							symtab/print/error_printer.c
							# assembly-generators
							assembly/assembly_generator.c
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
							assembly/generator/assembly_array.c																				
							assembly/utils/assembly_general.c
							assembly/utils/assembly_utils.c
							assembly/utils/assembly_formatter.c
							assembly/utils/assembly_template.c)	
							
set_target_properties(mCc_lib PROPERTIES PREFIX "")
set_target_properties(mCc_lib PROPERTIES OUTPUT_NAME "libmCc")							
set_property(TARGET mCc_lib PROPERTY COMPILE_FLAGS "-D_POSIX_C_SOURCE=200809L")				
target_link_libraries(mCc_lib ext_log_c ext_map)
				