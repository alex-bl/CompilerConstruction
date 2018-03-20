
# find BISON + FLEX targets
# NOTE: they have to be in upper-case
find_package(BISON)
find_package(FLEX)

# build flex- and bison-targets
flex_target(scanner scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.c DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/scanner.h)
bison_target(parser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c COMPILE_FLAGS "-Wall" DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h)

add_flex_bison_dependency(scanner parser)

add_library(mCc_lib SHARED ast.c ast_print.c ast_visit.c ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})
set_property(TARGET mCc_lib PROPERTY COMPILE_FLAGS "-D_POSIX_C_SOURCE=200809L")