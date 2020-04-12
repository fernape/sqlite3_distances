cmake_minimum_required(VERSION 3.14)
project(sorensen-dice)

set(target "sorensen-dice")

# Create shared library
add_library(${target} SHARED sorensen-dice.c)

# Create a static library to be linked against in tests
set(static_lib ${target}_static)
add_library(${static_lib} STATIC sorensen-dice.c)

add_executable(test_${target} test_sorensen_dice.c)
target_link_libraries(test_${target} ${static_lib} ${CHECK_LINK_LIBRARIES})

# Add test so this target can be invoked via <ninja/make> test
add_test(NAME test_${target} COMMAND test_${target})

# Create fuzzer
set(fuzzer_exe ${target}_fuzzer)
add_executable(${fuzzer_exe} sorensen_dice_fuzzer.c ../common/fuzz.c)
set_target_properties(${fuzzer_exe} PROPERTIES COMPILE_FLAGS "-g -O1 -fsanitize=fuzzer,address")
set_target_properties(${fuzzer_exe} PROPERTIES LINK_FLAGS "-fsanitize=fuzzer,address")
target_link_libraries(${fuzzer_exe} ${static_lib})
