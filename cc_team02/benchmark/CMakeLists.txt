# taken from:
# https://github.com/google/googletest/tree/master/googletest#incorporating-into-an-existing-cmake-project
# ... and adapted for googlebenchmark

configure_file(${CMAKE_SOURCE_DIR}/config/gbenchmark.in ${GBENCHMARK_DOWNLOAD_DESTINATION}/googlebenchmark-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY "${GBENCHMARK_DOWNLOAD_DESTINATION}/googlebenchmark-download")
if(result)
  message(FATAL_ERROR "CMake step for googlebenchmark failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY "${GBENCHMARK_DOWNLOAD_DESTINATION}/googlebenchmark-download" )
if(result)
  message(FATAL_ERROR "Build step for googlebenchmark failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows => needed here?
set(googlebenchmark_force_shared_crt ON CACHE BOOL "" FORCE)

# Disable the googlebenchmark specific tests which would run on default on every ctest-run
SET(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable gbenchmark tests to run on every ctest-run")

# Add googlebenchmark directly to our build. This defines
# the gbenchmark and gbenchmark_main targets.
add_subdirectory(${GBENCHMARK_DOWNLOAD_DESTINATION}/googlebenchmark-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-build
                 EXCLUDE_FROM_ALL)


# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
# The googlebenchmarks also?
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${googlebenchmark_SOURCE_DIR}/include")
endif()