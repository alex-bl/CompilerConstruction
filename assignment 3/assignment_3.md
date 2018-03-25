# Assignment 3 -- Control Flow Graph / Assembly

*due on 16 May 2018*

The goal of this assignment is to implement the parts remaining to obtain an executable.
Additionally, you are asked to create the control flow graph (CFG) which will be used later on for optimisations.

For simplicity we are targeting x86, not x86_64.
This can be achieved on a 64 bit installation by passing `-m32` to GCC when compiling your generated assembler code.
For this, the [GCC multilib package](https://packages.debian.org/buster/gcc-multilib) needs to be installed.

## Task 1

- Implement the generation of CFGs (one per function) based on your TAC.
- Provide a mechanism to print a CFG in the DOT format.

## Task 2

- Implement code generation.

The task is to convert your TAC to assembly code which can be compiled with the [GNU Assembler](https://en.wikipedia.org/wiki/GNU_Assembler).

To achieve this you should investigate how simple code snippets (if statement, while loop, ...) are translated by a C compiler without optimisations.

You do not have to perform register allocation for this.
Each variable should simply be located on the stack.
Yet, pay special attention to floating point and integer handling.

Use [cdecl calling convention](https://en.wikipedia.org/wiki/X86_calling_conventions#cdecl).
It is crucial to correctly implement the calling convention, otherwise you will corrupt your stack during function calls and returns.

## Task 3

- Implement back-end compiler invocation.

Now that we obtained assembly code we can convert it to an executable by running it through an assembler and linker.
For this we'll simply pass it to GCC.
This also allows us to attach the built-in functions, just pass the C source file to the compiler call.

Double check whether the built-in functions provided to your back-end compiler use the same calling convention.

You should now have a working compiler which can convert valid mC input programs to executables.

## Task 4

Polish the commandline parameter handling of your main compiler executable.
At least the following flags must be provided:

- `-h` / `--help`    to display usage information
- `-v` / `--version` to display version information
- `-o` / `--output`  to specify the resulting executable

## Task 5

Extend your integration test runner to also execute the generated binary.
Pass the content of the corresponding `.stdin` file to the binary and compare its output with the corresponding `.stdout` file.
Matching output indicates success.

## Submission

Follow the steps stated in the first assignment, using the following command to build the archive and the link below.

    $ git archive --prefix=team_XX_assignment_3/ --format=zip HEAD > team_XX_assignment_3.zip

:email: [send email](mailto:alexander.hirsch@uibk.ac.at?subject=703602%20-%20Assignment%203)
