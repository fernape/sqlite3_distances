cmake_minimum_required(VERSION 3.14)
project(distances)


# Look for SQLite3. We could just look for the sqlite3ext.h
# header, but seems unlikely that the header is present and not the
# whole distribution.

find_package(SQLite3 3.0)
if(SQLite3_FOUND)
	include_directories(${SQLite3_INCLUDE_DIRS})
endif()

add_subdirectory(hamming)
add_subdirectory(damerau-levenshtein)
