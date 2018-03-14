# TODOs: 
# - add benchmarking? => if yes, see https://github.com/vincent-picaud/Blog_CMake_GoogleBenchmark
# - add install-target
# - add + configure cpack?

cmake_minimum_required (VERSION 3.9.6)
project (cc_team02)

# The version number.
set(cc_team02_VERSION_MAJOR 1)
set(cc_team02_VERSION_MINOR 0)

# set global compiler flags (append them)
string(APPEND CMAKE_C_FLAGS "-std=c11 -Wall -Werror")
string(APPEND CMAKE_CXX_FLAGS "-std=c++14 -Wall -Werror")

# build-type
set(CMAKE_BUILD_TYPE Debug)

# gtest download-dest
set(GTEST_DOWNLOAD_DESTINATION "${PROJECT_SOURCE_DIR}/subprojects/googletest-release-1.8.0")
set(GBENCHMARK_DOWNLOAD_DESTINATION "${PROJECT_SOURCE_DIR}/subprojects/googlebenchmark-release-1.3.0")

#============================================================ doxygen config
set(DOXYGEN_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/doc")
# for other supported types see https://www.stack.nl/~dimitri/doxygen/manual/output.html
# maybe integrate pandoc to construct markdown out of doxygen's xml
set(DOXYGEN_GENERATE_HTML YES)
set(DOXYGEN_GENERATE_MAN NO)
set(DOXYGEN_GENERATE_XML NO)
#============================================================  
  
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config/config.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/config/config.h"
  )
  
# ignore tests
# configure_file("${PROJECT_SOURCE_DIR}/config/ignore_tests.cmake" "${CMAKE_BINARY_DIR}")
#=================================================================== building
  
# add the binary tree to the search path for include files
# so that we will find the headers
include_directories("${PROJECT_SOURCE_DIR}/include" ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(src)

# link libs with executables
add_executable(mCc src/bin/mCc.c)
target_link_libraries(mCc mCc_lib)

add_executable(mC_to_dot src/bin/mC_to_dot.c)
target_link_libraries(mC_to_dot mCc_lib)

#================================================================== testing

# test deps => target 'gtest'
# test => run tests
add_subdirectory("test")
include(CTest)

# taken from:
# https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project
# Now simply link against gtest or gtest_main as needed. Eg
#
# ... and extended (using the loop)
# is it that much simple? googleTest is already a module => https://cmake.org/cmake/help/v3.9/module/GoogleTest.html

#create list: add all tests manually here (file-names without *.cpp)
set(unit_test_list "parser")

foreach(entry_name ${unit_test_list})
	# build and link
	add_executable(${entry_name}_test_exec test/${entry_name}.cpp)	
	target_link_libraries(${entry_name}_test_exec mCc_lib gtest_main)
	# pass the test_exec to ctest => after COMMAND set args
	add_test(NAME ${entry_name}_test COMMAND ${entry_name}_test_exec)
endforeach(entry_name)

# enabling valgrind => target test_memcheck
# taken from:
# https://stackoverflow.com/questions/40325957/how-do-i-add-valgrind-tests-to-my-cmake-test-target
add_custom_target(test_memcheck
    COMMAND ${CMAKE_CTEST_COMMAND} 
        --force-new-ctest-process --test-action memcheck
    COMMAND cat "${CMAKE_BINARY_DIR}/Testing/Temporary/MemoryChecker.*.log")

#================================================================= benchmark
# TODO: why are there 36 benchmarks instead of 2?

add_subdirectory("benchmark")
# do the same as for testing, but with benchmark
set(my_benchmark_list "just_try")

foreach(entry_name ${my_benchmark_list})
	# build and link
	add_executable(${entry_name}_benchmark_exec benchmark/${entry_name}.cpp)	
	# TODO: used the correct binary?
	# This is actually just a test-file: If using non-test-files also link the mCc_binaries
	target_link_libraries(${entry_name}_benchmark_exec benchmark)
	# pass the test_exec to ctest => after COMMAND set args
	#add_test(NAME ${entry_name}_benchmark COMMAND ${entry_name}_benchmark_exec)
endforeach(entry_name)

# TODO: add a custom configuration here to set a base path-variable in executeBench.sh
# then iterate over the binary-dir end run the binaries matching to *bench

# custom benchmark-target => show output
add_custom_target(tests_with_benchmark
    COMMAND "${PROJECT_SOURCE_DIR}/benchmark/executeBench.sh")
#just_try_benchmark_exec --benchmark_color=false
#================================================================ doxygen
# why doxygen cannot be in upper-case???? => not compilant to BISON, FLEX find_package -.-
find_package(Doxygen)
doxygen_add_docs(doxygen "${PROJECT_SOURCE_DIR}/include" "${PROJECT_SOURCE_DIR}/src" COMMENT "Generating docs")

#================================================================