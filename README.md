# CC team02

This repository contains the cc_team02 full code-base.

## 1. Project setup

This section describes the minimal prerequisites, the build steps as well as a detailed description about the different targets. This project offers a build configuration for **cmake**.

Minimal prerequisites:

- flex 2.6.0
- bison (GNU Bison) 3.0.4
- valgrind-3.11.0
- doxygen 1.8.11
- libcurl4-openssl-dev 7.47.0
- cmake 3.9.6

Please note that the downloaded files (cmake) need to be installed manually using `./bootstrap --system-curl` to [ensure ssl-support](https://stackoverflow.com/questions/29816529/unsupported-protocol-while-download-tar-gz-package) (which is needed to automatically download external projects).

Manual build steps (**recommended**):

1. Clone or download the code-base (and move to the /cc_team02 folder).
2. Create the directory where to store the makefiles + binaries: `$ mkdir build`
3. Move to the build-directory: `$ cd build`
4. Build cmake-infrastructure: `$ cmake ../`
5. If you want to build in debug-mode, use: `$ cmake -DCMAKE_BUILD_TYPE:STRING=Debug ../`
6. (Optional) Build the whole project: `$ make all`
7. Execute targets (See possible targets) via: `$ make <target>`

Using the setup-wrapper (experimental):

1. Clone or download the code-base (and move to the /cc_team02 folder).
2. Build cmake-infrastructure: `$ ./setup-wrapper "<cmake-args>"`
3. Move to the build-directory: `$ cd build`
4. Execute targets (See possible targets) via: `$ make <target>`

**Note**: If there occur strange error-messages from cmake, try to delete the build-directory.

### Targets

This section lists the available targets that can be build.

| Target        | Description	| Additional notes  |
| ------------- |-------------	|------------------	|
| all			| Self explanatory | -	|
| clean			| Self explanatory      |   -			|
| cleanup_logger			| Removes all log-files      |   -			|
| doxygen		| Builds the documentation      |    - 			|
| test\*			| Runs all gtests (unit)	| - |
| build\_and\_test\* | Runs all gtests (unit; and builds all needed targets) | In cmake the default test-target does not ensure a rebuild. |
| build\_and\_test_memcheck\* | Runs all gtests together with valgrind | - |
| integration\_test | Runs all integration-tests (and builds all needed targets) | It runs the provided [shell-script](https://github.com/W4RH4WK/mCc/blob/master/test/integration). |
| run\_benchmarks\*\* | Runs all benchmarks | It is currently not used, but maybe in the future: CMake requires the [google-benchmark](https://github.com/google/benchmark) for this task. A custom shell script then runs all the benchmarked source-files. |

\* Test-targets execute also printer-tests: They don't have any "gtest-assertions" but print the AST (dot-notation) into `build/<release_type>/test/output`. This dot files are named as follow: `DOT_<test_name>.dot`  
\*\* Currently disabled

## 2. Usage

The execution of the `mC-compiler` is configurable using various options.

Run `./mCc --help` to display all options:

```
$ ./mCc --help
Usage: mCc [OPTION...] INPUT_FILE or '-' for stdin
mCc -- A compiler for the mC-language

  -c, --tac-cfg              Generate tac control flow graph    (default=false)
  -d, --dot                  Print the AST in dot-notation      (default=false)
  -f, --fileLog              Log into <project_dir>/log/        (default=false)
  -l, --stdoutLog            Log to stdout                      (default=false)
  -o, --output=FILE          Output to FILE                     (default=a.out)
  -t, --tac                  Print the Three-adress-code        (default=false)
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Report bugs to the members of team02.
```

**Note:**   
The printing functionalities are integrated into the `mCc`-executable.  The `mC_to_dot`-executable still exists and hence it can be executed. But note that it just prints out the AST in dot-notation without performing any semantic checks.

## 3. Known issues

This section contains known issues about the project.

### Assigmnent 1

- **False positive memory-leak**: Valgrind reports a [false positive memory-leak](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=802778) at `libstdc++.so.6.0.21`.

See [issues](https://github.com/alex-bl/CompilerConstruction/issues) for project progress and additional information.

### Assigmnent 2

- **Incorrect location information (line-/column-number) on the first statements inside a new scope (if/else, while):** This first statement gets the same location-information as the parent that opens the scope. All subsequent statements are correct. 
- **Memory Leaks on TAC tests:** Testing the TAC code still shows memory leaks. This will be improved shortly.

### Assignment 3
- **Valgrind issue**: Valgrind reports "Uninitialised value was created by a heap allocation" if using `malloc` on allocating memory for identifiers at `basic_tac.c`. We do not investigated further why this error occurs, but fixed it initializing the allocated memory with `0`s (using `calloc`).

- **Rounding error at integration tests**: On test-programs where a `floating-point` value's equality is checked afterwards, it may happens, that rounding errors prevent a positive match (because of string-comparison between program-output and `*.mC.stdout`). The affected test-outputs (currently only one) were adjusted accordingly.

## 4. Changelog

This section contains the fixed and unfixed issues from the previous assignments.

#### After assignment 2:

- Parsing assotiativity for binary-operations corrected (changed from right to left to guarantee correct TAC-construction + later evaluation).
- Function-uses before their declaration are allowed now (according to specification).
- Function- and primitive-variable-identifiers cannot be abused as array-identifiers anymore.
- Additional semantic checks for arrays as arguments (size + type equality ensured now).
- Assignments on array-variables dropped according to the changed specification.
- Segmentation fault dueto function-uses before their declaration (because of unlinked symbol-table-information) fixed.  
- Further TAC improvements done.

Unfixed issues:

- Avoid creating a shared library for each module.

#### After assignment 1:

- `Meson`-support is dropped. Only `CMake` is used now as build-tool.
- `Segmentation-fault` on `mCc` and `mCc_to_dot` is fixed (The wrong toplevel was detected).
- Parser now results in an error if toplevel is a statement/expression (Using a workaround, because we couldn't get working the [the suggested approach](https://www.gnu.org/software/bison/manual/html_node/Multiple-start_002dsymbols.html) spending a reasonable amount of time).
- Incorrect operator precedence in the parser was detected and fixed.
- Missing location-information on identifiers was fixed.
- README-restructuring done.
- All exported library symbols are prefixed now.
- Warnings on unused parameters are suppressed now.
- Include-pahts are managed by the build-system now.
- Restructuring on the `include`-directory done.
- A logging mechanism was introduced (logging to stdout and/or logfiles can be configured using command-line arguments).

Unfixed issues:

- Checking return-values after memory-allocation: Not done at every single place (-.-). An error is logged if such an allocation fails.
- Checking return-values inside the parser: Our colleague that did the whole parser + lexer (only with small exceptions) left the project. So we wanted to touch the parser/lexer stuff only on critical issues such as incorrect precendence-rules (which we had to do). We know that this isn't any excuse. It is just an explanation.
