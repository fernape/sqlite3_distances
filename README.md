# sqlite3_distances
String distances for sqlite3. These functions will give a numeric value to know how similar two strings are.

## Implemented functions

* damerau_levenshtein
* hamming
* longest common sequence
* optimal_string_alignment
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
You can force a specific clang version with:

```
$ CC=clang10 cmake ../ -GNinja
```

Fuzzers are in `build/${subproject}` for example in `build/hamming/hamming_fuzzer`. These programs run indefinitely.

## Coverage

To build with coverage support, from the build directory:

```
$ CC=clang10 cmake -DCOVERAGE=1 ../ -GNinja
```
Now, run the tests. In this example, de Damerau-Levenshtein tests:

```
$ cd damerau-levenshtein
$ ./test_damerau-levenshtein
```
Merge results:
```
$ llvm-profdata10  merge -sparse default.profraw -o default.profdata
```
Show report:
```
$ llvm-cov10 report ./test_damerau-levenshtein -instr-profile=default.profdata
```

## How to use it

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

## Reporting problems

Please, report any problems by [creating an issue](https://github.com/fernape/sqlite3_distances/issues) :-)
