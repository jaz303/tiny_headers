# header_libs

C/C++ single-file header libraries.

## Global `#define`s

  - `JLIB_xxx_IMPL`: used in libraries that have both a header and implementation component to indicate that the implementation should be generated.
  - `JLIB_NO_MALLOC`: do not use memory allocation via `new`, `malloc()`, etc. Some libraries (e.g. `ring_buffer.hpp`) will allocate their own storage if none is provided to the constructor. Defining `JLIB_NO_MALLOC` will make this functionality unavailable.

## `list.h`

  - Doubly-linked and circular lists for C
  - Not thread safe
  - Needs an implementation file: create `list.c`, `#define JLIB_LIST_IMPL` and `#include "list.h"`
  - To use with your own data types, make `struct list_node` the first struct member and use `AS_LIST_NODE()` to cast pointers

## `ring_buffer.hpp`

  - Fixed-size generic ring buffer
  - Not thread safe
  - Size must be a power of 2
  - If `remove()` is called on empty buffer the return value is undefined
  - To ensure validity, the contents of pointers obtained from `remove_ptr()` should be copied immediately
