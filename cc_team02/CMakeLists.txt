# TODOs: 
# - add benchmarking? => if yes, see https://github.com/vincent-picaud/Blog_CMake_GoogleBenchmark
# - add install-target
# - add + configure cpack?

cmake_minimum_required (VERSION 3.9.6)
project (cc_team02)

# The version number.
set(cc_team02_VERSION_MAJOR 1)
set(cc_team02_VERSION_MINOR 8)
set(cc_team02_VERSION_LOWER 11)

# set global compiler flags (append them)
# append -Wextra when all ast-implmentations are provided
string(APPEND CMAKE_C_FLAGS " -std=c11 -Wall -Wextra -Wno-unused-parameter -Wno-format-truncation -Wno-unused-function -Wno-sign-compare")
string(APPEND CMAKE_CXX_FLAGS " -std=c++14 -Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-sign-compare")

# enable this to see the exact commands form cmake
set(CMAKE_VERBOSE_MAKEFILE OFF)

if(NOT CMAKE_BUILD_TYPE)
	# if no build-type was specified, use release
	set(CMAKE_BUILD_TYPE Release)
	message(STATUS "No build-type set: Using default " ${CMAKE_BUILD_TYPE})
endif()

message(STATUS "Build-type: " ${CMAKE_BUILD_TYPE})

set(STDOUT_LOGGING_DISABLED 1)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	set(STDOUT_LOGGING_DISABLED 0)	
endif()

message(STATUS "Logging to stdout: " ${STDOUT_LOGGING_DISABLED})

# base dir for sub-projects
set(SUB_PROJECTS_BASE_DIR "${CMAKE_BINARY_DIR}/subprojects")

set(GTEST_DOWNLOAD_DESTINATION "${SUB_PROJECTS_BASE_DIR}/googletest-release1.8.0")
set(GBENCHMARK_DOWNLOAD_DESTINATION "${SUB_PROJECTS_BASE_DIR}/googlebenchmark-release-1.3.0")

#============================================================ test config (output-folders)
set(DOT_TEST_OUTPUT_DIR "${CMAKE_BINARY_DIR}/test/output/dot")
set(CFG_DOT_TEST_OUTPUT_DIR "${CMAKE_BINARY_DIR}/test/output/tac-cfg-dot")
set(ASSEMBLY_TEST_OUTPUT_DIR "${CMAKE_BINARY_DIR}/test/output/assembly")
#============================================================ doxygen config
set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/doc")
# for other supported types see https://www.stack.nl/~dimitri/doxygen/manual/output.html
# maybe integrate pandoc to construct markdown out of doxygen's xml
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)
set(DOXYGEN_GENERATE_XML NO)
#============================================================ valgrind config
#message(STATUS "valgrind: " ${MEMORYCHECK_COMMAND})
set(MCC_VALGRIND_ARGS "--leak-check=full --show-reachable=yes --track-origins=yes --error-exitcode=1")
set(MCC_VALGRIND_SUPPRESSIONS "--suppressions=${CMAKE_BINARY_DIR}/config/valgrind_libstdc++.so.6.0.21.supp")
set(MCC_VALGRIND_SUPPRESSIONS_2 "--suppressions=${CMAKE_BINARY_DIR}/config/valgrind_libstdc++.so.6.0.25.supp")
							  
set(MEMORYCHECK_COMMAND_OPTIONS "${MCC_VALGRIND_ARGS} ${MCC_VALGRIND_SUPPRESSIONS} ${MCC_VALGRIND_SUPPRESSIONS_2}")
#============================================================  assembler config
set(OBJECT_OUTPUT_DIR "${CMAKE_BINARY_DIR}/out")
set(ASSEMBLY_OUTPUT_DIR "${CMAKE_BINARY_DIR}/assembly")
#============================================================
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config/config.h.in"
  "${CMAKE_BINARY_DIR}/config/config.h"
  )

# configure bench_execution shell-script
configure_file (
  "${PROJECT_SOURCE_DIR}/config/run_benchmarks.in"
  "${CMAKE_BINARY_DIR}/utils/run_benchmarks"
  )

# configure valgrind-suppression for false positive: https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=802778
configure_file (
  "${PROJECT_SOURCE_DIR}/config/valgrind_libstdc++.so.6.0.21.supp.in"
  "${CMAKE_BINARY_DIR}/config/valgrind_libstdc++.so.6.0.21.supp"
  )

configure_file (
  "${PROJECT_SOURCE_DIR}/config/valgrind_libstdc++.so.6.0.25.supp.in"
  "${CMAKE_BINARY_DIR}/config/valgrind_libstdc++.so.6.0.25.supp"
  )

# configure build-ins (semantic checks)
configure_file(
	"${PROJECT_SOURCE_DIR}/data/buildins.mC.in"
	"${CMAKE_BINARY_DIR}/data/buildins.mC"
)

# configure build-ins (implementation)
configure_file(
	"${PROJECT_SOURCE_DIR}/data/buildins.c.in"
	"${CMAKE_BINARY_DIR}/data/buildins.c"
)

#=================================================================== headers
include_directories(${CMAKE_CURRENT_BINARY_DIR}) 
# config
include_directories(${CMAKE_CURRENT_BINARY_DIR}/config)  
# add the binary tree to the search path for include files
# so that we will find the headers
include_directories("${PROJECT_SOURCE_DIR}/include")
# include test-utils-header also => separated from source
include_directories("${PROJECT_SOURCE_DIR}/test/include")
# external logging-lib
include_directories("${PROJECT_SOURCE_DIR}/external/log/include")
# external hash-map
include_directories("${PROJECT_SOURCE_DIR}/external/map/include")

#=========== all-dev header-includes
include_directories("${PROJECT_SOURCE_DIR}/src/include/")

include_directories("${PROJECT_SOURCE_DIR}/src/include/ast/basis")
include_directories("${PROJECT_SOURCE_DIR}/src/include/ast/print")
include_directories("${PROJECT_SOURCE_DIR}/src/include/ast/visit")

include_directories("${PROJECT_SOURCE_DIR}/src/include/general")

include_directories("${PROJECT_SOURCE_DIR}/src/include/symtab")
include_directories("${PROJECT_SOURCE_DIR}/src/include/symtab/handler")
include_directories("${PROJECT_SOURCE_DIR}/src/include/symtab/print")
include_directories("${PROJECT_SOURCE_DIR}/src/include/symtab/validator")

include_directories("${PROJECT_SOURCE_DIR}/src/include/tac")
include_directories("${PROJECT_SOURCE_DIR}/src/include/tac/basis")
include_directories("${PROJECT_SOURCE_DIR}/src/include/tac/cfg")
include_directories("${PROJECT_SOURCE_DIR}/src/include/assembly")
include_directories("${PROJECT_SOURCE_DIR}/src/include/assembly/generator")
include_directories("${PROJECT_SOURCE_DIR}/src/include/assembly/utils")

#=================================================================== external-src

add_subdirectory(external)

# externals build as shared libraries:
# ext_log_c
# ext_map

#=================================================================== src

add_subdirectory(src)

# link libs with executables
add_executable(mCc src/bin/mCc.c)
target_link_libraries(mCc mCc_lib)
# to ensure the output-dir is generated
add_dependencies(mCc build_assembler_output_dir object_output_dir)

add_executable(mC_to_dot src/bin/mC_to_dot.c)
target_link_libraries(mC_to_dot mCc_lib)

#================================================================== testing

# test deps => target 'gtest'
# test => run tests
add_subdirectory("test" "${GTEST_DOWNLOAD_DESTINATION}")
# test-utils
add_subdirectory("test/utils" "${CMAKE_BINARY_DIR}/test/utils")



include(CTest)
# add native gtest support
include(GoogleTest)

# taken from:
# https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project
# Now simply link against gtest or gtest_main as needed. Eg
#
# ... and extended (using the loop)
# is it that much simple? googleTest is already a module => https://cmake.org/cmake/help/v3.9/module/GoogleTest.html

#create list: add all tests manually here (file-names without *.cpp)
#set(unit_test_list "tac_build" "tac_print")
#set(unit_test_list "assembly")
set(unit_test_list "parser" "builder" "printer" "symtab" "validator" "checks" "tac_build" "tac_print" "tac_cfg_print" "assembly")

#================================================================ valgrind

# custom test-target to enforce a rebuild (see https://stackoverflow.com/questions/733475/cmake-ctest-make-test-doesnt-build-tests)
# add -V for verbose-info on tests
add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} --output-on-failure)

# enabling valgrind => target test_memcheck
# taken from:
# https://stackoverflow.com/questions/40325957/how-do-i-add-valgrind-tests-to-my-cmake-test-target
add_custom_target(build_and_test_memcheck
	COMMAND echo "Removing old log-files..."
	COMMAND rm -rf ${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log
    COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --test-action memcheck
    # by having 100 unit-tests, a cat of such a number may not senseful => check log-file instead
    #COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log"    
    )

# Is this enough or should there be a custom valgring-target?
# configure memcheck => see https://stackoverflow.com/questions/9303711/how-do-i-make-ctest-run-a-program-with-valgrind-without-dart
# Is this working? => set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")

# Custom valgrind-target:
# - https://stackoverflow.com/questions/9303711/how-do-i-make-ctest-run-a-program-with-valgrind-without-dart
# - https://github.com/fletcher/c-template/blob/master/CMakeLists.txt

# Notes: Valgrind reports a false positive memleak on every run in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21
# See https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=802778

#=============================================================== integration tests

set(INTEGRATION_TEST_SCRIPT "${PROJECT_SOURCE_DIR}/test/integration")
set(RUN_INTEGRATION_TEST_SCRIPT "${PROJECT_SOURCE_DIR}/test/run_integration")
set(RUN_EXTENDED_UNIT_TEST_SCRIPT "${PROJECT_SOURCE_DIR}/test/run_extended_unit_test")

# use provided shell-script
add_custom_target(integration_test
	COMMAND echo "======================================================================================"
	COMMAND ${RUN_INTEGRATION_TEST_SCRIPT} ${INTEGRATION_TEST_SCRIPT}
	COMMAND echo "======================================================================================")
add_dependencies(integration_test mCc)

# integration-tests on a unit-level (for assembly-generation)
add_custom_target(extended_unit_test	
	COMMAND echo "======================================================================================"
	COMMAND ${RUN_EXTENDED_UNIT_TEST_SCRIPT} ${INTEGRATION_TEST_SCRIPT}
	COMMAND echo "======================================================================================")
add_dependencies(extended_unit_test mCc)

# execute unit-tests before the extended unit-tests
add_custom_target(build_and_test_all_units	
	COMMAND echo "======================================================================================"
	COMMAND ${RUN_EXTENDED_UNIT_TEST_SCRIPT} ${INTEGRATION_TEST_SCRIPT}
	COMMAND echo "======================================================================================"
	DEPENDS build_and_test mCc)

# one target to run every test
add_custom_target(build_and_test_all
	COMMAND echo "======================================================================================"
	COMMAND ${RUN_INTEGRATION_TEST_SCRIPT} ${INTEGRATION_TEST_SCRIPT}
	COMMAND echo "======================================================================================")
add_dependencies(build_and_test_all build_and_test_all_units)

#=============================================================== gtest-execution
# build output-folders
add_dependencies(gtest build_test_dot_output_dir)	
add_dependencies(gtest build_test_assembly_output_dir)		
add_dependencies(gtest object_output_dir)	
add_dependencies(gtest build_assembler_output_dir)	
add_dependencies(gtest build_test_cfg_dot_output_dir)		

foreach(entry_name ${unit_test_list})
	
	# build and link
	add_executable(${entry_name}_test_exec test/${entry_name}.cpp)
	target_link_libraries(${entry_name}_test_exec mCc_test_utils mCc_lib gtest_main)
	# pass the test_exec to ctest => after COMMAND set args
	# add_test(NAME ${entry_name}_test COMMAND ${entry_name}_test_exec)
	# native gtest support since cmake 3.9?
	gtest_add_tests(TARGET ${entry_name}_test_exec
					EXTRA_ARGS "-V"
					TEST_PREFIX "mCc_test_"
					TEST_SUFFIX ".tst"
					TEST_LIST "list_of_exec_tests")
	# copy executables to test-directory => NOTE: it does not easily works with meson to specify an output-path, so leave it out for
	# compatability issues with meson
	 set_target_properties(${entry_name}_test_exec PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/test
		RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/test)
							
	# force a rebuild
	add_dependencies(build_and_test ${entry_name}_test_exec)
	add_dependencies(build_and_test_memcheck ${entry_name}_test_exec)
endforeach(entry_name)

#================================================================= benchmark
# currently not used!

# custom benchmark-target => run all benchmark-binaries within shell-script
#add_custom_target(run_benchmarks
#    COMMAND ${CMAKE_BINARY_DIR}/utils/run_benchmarks)

# exclude from build, because currently not used
# add_subdirectory("benchmark" "${GBENCHMARK_DOWNLOAD_DESTINATION}")
# do the same as for testing, but with benchmark
# set(my_benchmark_list "just_try")

#foreach(entry_name ${my_benchmark_list})
	# build and link
#	add_executable(${entry_name}_benchmark_exec benchmark/${entry_name}.cpp)	
	# TODO: used the correct binary?
	# This is actually just a test-file: If using non-test-files also link the mCc_binaries
#	target_link_libraries(${entry_name}_benchmark_exec benchmark)
	# copy executables to bench-directory
#	set_target_properties(${entry_name}_benchmark_exec PROPERTIES
#		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/benchmark
#		RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/benchmark)
#	add_dependencies(run_benchmarks ${entry_name}_benchmark_exec)
#endforeach(entry_name)

#================================================================= logging
add_custom_target(cleanup_logger
			COMMAND echo "Removing log-files..."
			COMMAND rm -f ${PROJECT_SOURCE_DIR}/log/*.log) 

#================================================================ doxygen
# why doxygen cannot be in upper-case???? => not compilant to BISON, FLEX find_package -.-
find_package(Doxygen)
doxygen_add_docs(doxygen "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/src" COMMENT "Generating docs")

#================================================================ assembler
add_custom_target(object_output_dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${OBJECT_OUTPUT_DIR})
add_custom_target(build_assembler_output_dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSEMBLY_OUTPUT_DIR})

add_custom_target(build_test_dot_output_dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${DOT_TEST_OUTPUT_DIR})
add_custom_target(build_test_assembly_output_dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${ASSEMBLY_TEST_OUTPUT_DIR})
add_custom_target(build_test_cfg_dot_output_dir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${CFG_DOT_TEST_OUTPUT_DIR})
