sdbl
====

Simple Database Library - a module to do data persistence in C, in size fixed rows, size fixed columns, no data types.

For small data, no index.

The key for register is the number of register.

## Installation ##

Just compile with `make` command.


## Interface ##

* `SDBL_file_s *SDBL_open(const char *fname, int data_len)`

Open file `fname` with register size of `data_len` characters, create if necessary. Returns a controller pointer.


* `int SDBL_close(SDBL_file_s *fh)`

Free internal structures and close controller `fh`.


* `int SDBL_put(SDBL_file_s *finfo, SDBL_key_t key, char *data)`

Save the register poitend by `data` into controller `fh`. If `key` is equal SDBL_NEW_RECORD, add a register, otherwise save a existent register pointed by `key`. Returns a true value if success.


* `char *SDBL_get(SDBL_file_s *file, SDBL_key_t key)`

Returns a register pointed by `key`.


* `int SDBL_next(SDBL_file_s *)`

Go to next register in file.


* `int SDBL_prev(SDBL_file_s *)`

Go to prev register in file.


* `int SDBL_top(SDBL_file_s *)`

Go to first register (top of file).


* `int SDBL_bottom(SDBL_file_s *)`

Go to last register in file (bottom of file).


## Usage example ##

See the *test.c* (type `make test` to compile).
