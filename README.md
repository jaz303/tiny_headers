# header_libs

C/C++ single-file header libraries

## Global `#define`s

  - `JLIB_NO_MALLOC`: do not perform memory allocation via e.g. `new`, `malloc()`

## ring_buffer.hpp

  - Fixed-size generic ring buffer
  - Not thread safe
  - Size must be a power of 2
  - If `remove()` is called on empty buffer the return value is undefined
  - To ensure validity the contents of pointers obtained from `remove_ptr()` should be copied immediately
