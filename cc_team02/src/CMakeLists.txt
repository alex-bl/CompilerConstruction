
# find BISON + FLEX targets
# NOTE: they have to be in upper-case
find_package(BISON)
find_package(FLEX)

# build flex- and bison-targets
flex_target(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/scanner.h)
bison_target(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c COMPILE_FLAGS "-Wall" DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)

add_flex_bison_dependency(scanner parser)

# basic ast
add_library(mCc_ast SHARED  ast/basis/ast_assignment.c
							ast/basis/ast_declaration.c
							ast/basis/ast_expression.c
							ast/basis/ast_function.c							
							ast/basis/ast_identifier.c							
							ast/basis/ast_literal.c							
							ast/basis/ast_program.c							
							ast/basis/ast_statement.c)

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

# symbol-table-handler (for building the symbol-table and validation)
add_library(mCc_symtab SHARED symtab/handler/symtab_handle_scope.c
							symtab/handler/symtab_handle_function.c
							symtab/handler/symtab_handle_identifier.c
							symtab/handler/symtab_handle_statement.c
							symtab/symbol_table.c
							symtab/symtab_build.c)

# intermediate
target_link_libraries(mCc_symtab ext_map)

# setup mCc_lib
add_library(mCc_lib SHARED ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})

# link remaining
target_link_libraries(mCc_lib mCc_print mCc_visit mCc_ast)

set_property(TARGET mCc_lib PROPERTY COMPILE_FLAGS "-D_POSIX_C_SOURCE=200809L")

