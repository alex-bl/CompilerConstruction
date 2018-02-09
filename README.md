# mC Compiler

This repository holds a *getting started* code-base for the [compiler construction course](https://github.com/W4RH4WK/UIBK-703602-Compiler-Construction).

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

## Overview

The source files located in `src` are built into a (shared) library.
Each source file located in `src/bin` results in one corresponding executable, which is linked against the library.
Similarly, each source file in `test` results in one executable for unit testing purposes.

The goal is to have the implementation of the mC compiler (`mCc`) available as library.

### Naming

As C does not feature namespaces, the names of all symbols are prefixed with `mCc_` followed by another prefix for their corresponding unit (eg `ast_`).
Please adhere to this convention to prevent conflicts with other software.

### Formatting

ClangFormat is used to format the entire code-base.
A configuration is provided.

### Build System

The file `meson.build` contains all build system settings, each source file is listed there.
It is not recommended to glob for source files.
Extend the lists upon adding new source files.

The default build-type is configured to *release*.
Pass `--buildtype=debug` to `meson` when creating the build directory to obtain a debug build.

### Unit Testing

While the compiler itself is written in C, unit tests are written in C++.
Each *unit* (source file located in `src`) should have a corresponding file in `test` containing the relevant unit tests.
For convenience, each unit test suit is compiled into a separate executable.

Pay attention when combining C and C++ code.
Strange errors may occur when handled incorrectly.
Consider passing additional flags (eg `-Wc++-compat`) to the C compiler for more warnings.

Meson provides a way to wrap tests with arbitrary programs (eg Valgrind) or GDB.

### Integration Testing

Valid example inputs are placed inside `doc/examples`.
They can be compiled with `mCc` using the provided Bash script `test/integration`.
Invoke it from the build directory as shown above.

### Lexer and Parser

`flex` and `bison` are used to generate the lexer and parser, respectively.
Their input files are `scanner.l` and `parser.y` and have their own special syntax.
The resulting files are `scanner.c`, `scanner.h`, `parser.tab.c`, and `parser.tab.h`, which are all considered implementation details.
The main interface of the parser is defined by `parser.h` and should be free of implementation details.

### Abstract Syntax Tree (AST)

The AST is defined in `ast.h`.
Nodes are encoded in 2 levels, structs for *node types* (eg statement, expression, literal, ...) and *tagged unions* to distinguish their variants (eg call expression, binary operation, ...).

Furthermore, a visitor mechanism is provided in `ast_visit.h`.

### Printing and Debugging

An AST printer for the [Dot Format](https://en.wikipedia.org/wiki/DOT_(graph_description_language)) is provided.
Together with [Graphviz](https://graphviz.gitlab.io/), ASTs can be visualised.

    $ ./mC_to_dot ../doc/examples/fib.mC | dot -Tpng | feh -

Note that for this very purpose a dedicated executable `mC_to_dot` is created.
It is recommended to add other utility executables for debugging and scripting purposes.
Prefer this method to adding additional flags to the main compiler executable `mCc`.

### Current State

Since this is only here to get you started, only a small portion of the grammar has been implemented.
Yet this should make it much easier to work with `flex` / `bison` than starting from scratch.

Be sure to understand the provided code before using it!
Notice me if you find any mistakes which should be patched.
