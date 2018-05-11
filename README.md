# CC team02

This repository contains the cc_team02 full code-base.

## Known issues

This section contains known issues about the project.

- **False positive memory-leak**: Valgrind reports a [false positive memory-leak](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=802778) at `libstdc++.so.6.0.21`.

See [issues](https://github.com/YusufIpek/CompilerConstruction/issues) for project progress and additional information.

## Setup

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
| doxygen		| Builds the documentation      |    - 			|
| test\*			| Runs all gtests (unit)	| - |
| build\_and\_test\* | Runs all gtests (unit; and builds all needed targets) | In cmake the default test-target does not ensure a rebuild. |
| build\_and\_test_memcheck\* | Runs all gtests together with valgrind | - |
| integration\_test | Runs all integration-tests (and builds all needed targets) | It runs the provided [shell-script](https://github.com/W4RH4WK/mCc/blob/master/test/integration). |
| run\_benchmarks | Runs all benchmarks | It is currently not used, but maybe in the future: CMake requires the [google-benchmark](https://github.com/google/benchmark) for this task. A custom shell script then runs all the benchmarked source-files. |

\* Test-targets execute also printer-tests: They don't have any "gtest-assertions" but print the asts (dot-notation) into `build/<release_type>/test/output`. This dot files are named as follow:


`DOT_<test_name>.dot`
