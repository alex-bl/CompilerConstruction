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

1. Clone or download the code-base.
2. Create the directory where to store the makefiles + binaries: `$ mkdir build`
3. Move to the build-directory: `$ cd build`
4. Build cmake-infrastructure: `$ cmake ../`
5. If you want to build in debug-mode, use: `$ cmake -DCMAKE_BUILD_TYPE:STRING=Debug ../`
6. (Optional) Build the whole project: `$ make all`
7. Execute targets (See possible targets) via: `$ make <target>`

Using the setup-wrapper (experimental):

1. Clone or download the code-base.
2. Build cmake-infrastructure: `$ ./setup-wrapper cmake "<cmake-args>"`
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
| run\_benchmarks | Runs all benchmarks | It is currently not used, but maybe in the future: CMake requires the [google-benchmark](https://github.com/google/benchmark) for this task. A custom shell script then runs all the benchmarked source-files. |

\* Test-targets execute also printer-tests: They don't have any "gtest-assertions" but print the asts (dot-notation) into `build/<release_type>/test/output`. This dot files are named as follow:


`DOT_<test_name>.dot`


## 2. Known issues

This section contains known issues about the project.

### Assigmnent 1

- **False positive memory-leak**: Valgrind reports a [false positive memory-leak](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=802778) at `libstdc++.so.6.0.21`.

See [issues](https://github.com/alex-bl/CompilerConstruction/issues) for project progress and additional information.

### Assigmnent 2

- **Incorrect location information (line-/column-number) on the first statements inside a new scope (if/else, while):** This first statement gets the same location-information as the parent that opens the scope. All subsequent statements are correct. 

## 3. Changelog

This section contains the fixed issues from the previous assignments.

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
- A logging-mechanism was introduced: Everything is logged now into [logfiles](cc_team02/log) (In `Release`-mode logging to `stdout` is suppressed).

Unfixed issues:

- Checking return-values after memory-allocation: Not done at every single place (-.-). An error is logged if such an allocation fails.
- Checking return-values inside the parser: Our colleague that did the whole parser + lexer (only with small exceptions) left the project. So we wanted to touch the parser/lexer stuff only on critical issues such as incorrect precendence-rules (which we had to do). We know that this isn't any excuse. It is just an explanation.