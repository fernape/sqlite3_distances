# sqlite3_distances
String distances for sqlite3

## How to build
`$ git clone https://github.com/fernape/sqlite3_distances.git`

`$ cd sqlite3_distances`

`$ mkdir build && cd build`

`$ cmake -G Ninja ../`

`$ ninja`

## How to use

`$ sqlite3 test.db`
`SQLite version 3.29.0 2019-07-10 17:32:03
Enter ".help" for usage hints.`

Load library

`sqlite> .load ./damerau-levenshtein/libdamerau-levenshtein`

Use the function

```sqlite
sqlite> select damerau_levenshtein('stuff', 'staff');
1
sqlite>```
