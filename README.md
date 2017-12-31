# Compiler Construction

This repository holds a *getting started* code-base for the [compiler construction course](https://github.com/W4RH4WK/UIBK-703602-Compiler-Construction).

## Input Language

- see [mC Specification](doc/mC_specification.md)
- see [examples](doc/examples)

## Prerequisites

- [Meson](http://mesonbuild.com/) in a recent version (`0.44.0`).
  You may want to install it via `pip3 install --user meson`.
- [Ninja](https://ninja-build.org/)
- `time`, typically located in `/usr/bin/time`, do not confuse with the Bash built-in.
- `flex` for generating the lexer.
- `bison` for generating the parser.
- [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html)
- A C11 and C++14 compiler.

## Building and Testing

[Google Test](https://github.com/google/googletest) is used for unit testing.
Meson downloads and builds it automatically if it is not found system.

    $ git clone https://github.com/W4RH4WK/mCc.git
    $ cd mCc
    $ meson builddir
    $ cd builddir
    $ ninja
    $ ninja test
    $ ../test/integration

## Overview

The header and source files located in `include` and `src` respectively are built into a (shared) library.
Each source file located in `src/bin` results in one corresponding executable, which is linked against the library.
Similarly, each source file in `test` is results in one executable for unit testing purposes.

The goal is to have the implementation of the mC compiler (`mCc`) available as library.

### Naming

As C does not feature namespaces, the names of all symbols are prefixed with `mC_` followed by another prefix for their corresponding unit (eg `ast_`).
Please adhere to this convention to prevent conflicts.

### Formatting

ClangFormat is used to format the entire code-base.
A configuration is provided.

### Build System

The file `meson.build` contains all build system settings, each source file is listed there.
It is not recommended to glob for source files.
Extend the list upon adding new ones.

The default build-type is configured to *release*.
Pass `--buildtype=debug` to `meson` when creating the build directory to obtain a debug build.

### Unit Testing

While the compiler itself is written in C, unit tests are allowed to by written in C++ due to Google Test.
Each *unit* (source file located in `src`) should have a corresponding `_test` file in `test` containing the relevant tests.
For convenience, each unit test suit is compiled into a separate executable.

Pay attention when combining C and C++ code.
Strange errors may occur when handled incorrectly.
Consider passing `-Wc++-compat` to the C compiler for additional warnings.

### Integration Testing

Valid examples inputs are placed inside `doc/examples`.
They can be compiled with `mCc` using the provided shell script `test/integration`.
Invoke it from the build directory as shown above.

It will run each example input, in alphabetical order, and display elapsed time, maximum memory consumption, and result.

### Lexer and Parser

`flex` and `bison` are used to generate the lexer and parser, respectively.
Their input files are `scanner.l` and `parser.y` and have their own special syntax.
The result are `scanner.c`, `scanner.h`, `parser.tab.c`, and `parser.tab.h`, which are all considered implementation details.
The main interface to the parser is defined by `parser.h`.

### Abstract Syntax Tree (AST)

The AST is defined in `ast.h`.
Nodes are encoded in 2 levels, structs for *node types* (eg statement, expression, literal, ...) and *tagged unions* to distinguish their variants (eg call expression, binary operation, ...).

Furthermore, a depth-first visitor is provided in `ast_visit.h` which allows for either pre-order or post-order traversal.

### Printing and Debugging

The visitor is used to enable printing of the AST in [Graphviz](https://graphviz.gitlab.io/)'s *dot* format.
The resulting format can be used to create an image representing the AST.

    $ ./mC_to_dot ../doc/examples/fib.mC | dot -Tpng | feh -

Note that for this purpose a dedicated executable `mC_to_dot` is created.
It is recommended to add other utility executables for debugging and scripting purposes.
Prefer this method to adding additional flags to the main compiler executable `mCc`.

### Current State

Since this is only here to get you started, only a small portion of the grammar has been implemented.
Yet this should make it much easier to work with `flex` / `bison` as starting from scratch.
