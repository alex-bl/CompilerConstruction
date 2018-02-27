# Overview

The source files located in `src` are built into a (shared) library.
Each source file located in `src/bin` results in one corresponding executable, which is linked against the library.
Similarly, each source file in `test` and `benchmark` results in one executable for unit testing / benchmarking.

The goal is to implement the mC compiler as (shared) library.
This implementation is then used by dedicated binaries, like `mCc` and `mC_to_dot`.

## Naming

As C does not feature namespaces, the names of all symbols are prefixed with `mCc_` followed by another prefix for their corresponding unit (eg `ast_`).
Please adhere to this convention to prevent conflicts with other software.

## Formatting

ClangFormat is used to format the entire code-base.
A configuration is provided.

## Build System

The file `meson.build` contains all build system settings, each source file is listed there.
It is not recommended to glob for source files.
If you really wanna glob for source files, see [the related FAQ entry](http://mesonbuild.com/FAQ.html#but-i-really-want-to-use-wildcards)
Otherwise, extend the lists upon adding new source files.

The default build-type is configured to *release*.
Pass `--buildtype=debug` to `meson` when creating the build directory to obtain a debug build.
Meson also provides `debugoptimized` which is commonly used during development.

## Unit Testing

While the compiler itself is written in C, unit tests are written in C++.
Each *unit* should have a corresponding file in `test` containing the relevant unit tests.
For convenience, each unit test suit is compiled into a separate executable.

Pay attention when combining C and C++ code.
Strange errors may occur when handled incorrectly.
Consider passing additional flags (eg `-Wc++-compat`) to the C compiler for more warnings.

Meson provides a `--wrapper` flag to run tests through arbitrary programs, for instance:

    $ meson test --wrapper 'valgrind --error-exitcode=1 --leak-check=full'

Full output can be obtained by also passing `--verbose`.

If you encounter segfaults happening at random, catch them by repeating unit tests multiple times with GDB attached:

    $ meson test --repeat 1000000 --gdb

## Integration Testing

Valid example inputs are placed inside `doc/examples`.
They can be compiled with `mCc` using the provided Bash script `test/integration`.

## Lexer and Parser

`flex` and `bison` are used to generate the lexer and parser, respectively.
Their input files are `scanner.l` and `parser.y` and have their own special syntax.
The resulting files are `scanner.c`, `scanner.h`, `parser.tab.c`, and `parser.tab.h`, which are all considered implementation details.
The main interface of the parser is defined by `parser.h` and should be free of implementation details.

## Abstract Syntax Tree (AST)

The AST is defined in `ast.h`.
Nodes are encoded in 2 levels, structs for *node types* (eg statement, expression, literal, ...) and *tagged unions* to distinguish their variants (eg call expression, binary operation, ...).

Furthermore, a visitor mechanism is provided in `ast_visit.h`.

## Printing and Debugging

An AST printer for the [Dot Format](https://en.wikipedia.org/wiki/DOT_(graph_description_language)) is provided.
Together with [Graphviz](https://graphviz.gitlab.io/), ASTs can be visualised.

    $ cat ../doc/examples/fib.mC | ./mC_to_dot | xdot -

or

    $ cat ../doc/examples/fib.mC | ./mC_to_dot | dot -Tpng > fib.mC.png
    $ xdg-open fib.mC.png

Note that for this very purpose a dedicated executable `mC_to_dot` is created.
It is recommended to add other utility executables for debugging and scripting purposes.
Prefer this method to adding additional flags to the main compiler executable `mCc`.

## Current State

Since this is only here to get you started, only a small portion of the grammar has been implemented.
Yet this should make it much easier to work with `flex` / `bison` than starting from scratch.

Be sure to understand the provided code before using it!
Notify me if you find any mistakes which should be patched.
