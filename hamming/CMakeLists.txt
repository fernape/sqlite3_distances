cmake_minimum_required(VERSION 3.14)
project(hamming)

set(target "hamming")

# Create shared library
add_library(${target} SHARED hamming.c)

# Create a static library to be linked against in tests
set(static_lib ${target}_static)
add_library(${static_lib} STATIC hamming.c)
set_target_properties(${target}_static PROPERTIES COMPILE_FLAGS "${COVERAGE_COMPILE_FLAGS}")
set_target_properties(${target}_static PROPERTIES LINK_FLAGS "${COVERAGE_LINK_FLAGS}")

add_executable(test_${target} test_hamming.c)
target_link_libraries(test_${target} ${static_lib} ${CHECK_LINK_LIBRARIES})
set_target_properties(test_${target} PROPERTIES COMPILE_FLAGS "${COVERAGE_COMPILE_FLAGS}")
set_target_properties(test_${target} PROPERTIES LINK_FLAGS "${COVERAGE_LINK_FLAGS}")

# Add test so this target can be invoked via <ninja/make> test
add_test(NAME test_${target} COMMAND test_${target})

# Create fuzzer
set(fuzzer_exe ${target}_fuzzer)
add_executable(${fuzzer_exe} hamming_fuzzer.c ../common/fuzz.c)
set_target_properties(${fuzzer_exe} PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=fuzzer,address ${COVERAGE_COMPILE_FLAGS}")
set_target_properties(${fuzzer_exe} PROPERTIES LINK_FLAGS "-fsanitize=fuzzer,address ${COVERAGE_LINK_FLAGS}")
target_link_libraries(${fuzzer_exe} ${static_lib})
