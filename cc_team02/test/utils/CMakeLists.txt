
# test utils
# maybe extend here?
add_library(mCc_test_utils STATIC  mCc_test_utils.c)
set_property(TARGET mCc_test_utils PROPERTY COMPILE_FLAGS "-D_POSIX_C_SOURCE=200809L")