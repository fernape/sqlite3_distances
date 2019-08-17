cmake_minimum_required(VERSION 3.14)
project(hamming)

set(target "hamming")

# Create shared library
add_library(${target} SHARED hamming.c)

# Create a static library to be linked against in tests
add_library(${target}_test STATIC hamming.c)

add_executable(test_${target} test_hamming.c)
target_link_libraries(test_${target} ${target}_test ${CHECK_LINK_LIBRARIES})

# Add test so this target can be invoked via <ninja/make> test
add_test(NAME test_${target} COMMAND test_${target})
