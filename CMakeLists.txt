cmake_minimum_required(VERSION 3.14)
project(distances)

# Look for SQLite3. We could just look for the sqlite3ext.h
# header, but seems unlikely that the header is present and not the
# whole distribution.

find_package(SQLite3 3.0)
if(SQLite3_FOUND)
	include_directories(${SQLite3_INCLUDE_DIRS})
endif()

# Try and find check for tests
include(FindPkgConfig)
pkg_search_module(CHECK check)

if(CHECK_FOUND)
	include_directories(${CHECK_INCLUDE_DIRS})
endif()

# Enable testing via CTest
enable_testing()

# Add all the subdirectories
add_subdirectory(hamming)
add_subdirectory(damerau-levenshtein)
add_subdirectory(sorensen-dice)