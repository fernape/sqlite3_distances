# sqlite3_distances
String distances for sqlite3

## Implemented functions

* damerau_levenshtein
* hamming
* sorensen_dice

## Dependencies

[CMake](www.cmake.org)

A CMake's compatible build tool ([ninja](https://ninja-build.org/) is our preferred backend)

We use [check](https://libcheck.github.io/check/) as test framework.

A recent version of clang is required.

SQLite3 is required too.

## How to build

```
$ gitlone https://github.com/fernape/sqlite3_distances.git
$ cd sqlite3_distances
$ mkdir build && cd build
$ cmake -G Ninja ../
$ ninja
$ ninja test
```

Fuzzers are in `build/${subproject}` for example in `build/hamming/hamming_fuzzer`. These programs run indefinitely.

## How to use

```sqlite3 test.db

SQLite version 3.29.0 2019-07-10 17:32:03
Enter ".help" for usage hints.
```

Load library

`sqlite> .load ./damerau-levenshtein/libdamerau-levenshtein`

Use the function

```sqlite
sqlite> select damerau_levenshtein('stuff', 'staff');
1
sqlite>
```
