# mC Compiler

This repository holds a *getting started* code-base for the [compiler construction course](https://github.com/W4RH4WK/UIBK-703602-Compiler-Construction).

A more detailed overview can be found in [`doc/overview.md`](doc/overview.md).

## Input Language

- see [mC Specification](https://github.com/W4RH4WK/UIBK-703602-Compiler-Construction/blob/master/mC_specification.md)
- see [examples](doc/examples)

## Prerequisites

- [Meson](http://mesonbuild.com/) in a recent version (`0.44.0`)
  (you may want to install it via `pip3 install --user meson`)
- [Ninja](https://ninja-build.org/)
- `time`, typically located in `/usr/bin/time`, do not confuse with the Bash built-in
- `flex` for generating the lexer
- `bison` for generating the parser
- [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
- a C11 and C++14 compiler (typically GCC or Clang)

## Building and Testing

[Google Test](https://github.com/google/googletest) is used for unit testing.
Meson downloads and builds it automatically if it is not found on your system.

    $ git clone https://github.com/W4RH4WK/mCc.git
    $ cd mCc
    $ meson builddir && cd builddir
    $ ninja
    $ ninja test
    $ ../test/integration
    $ ninja benchmark
