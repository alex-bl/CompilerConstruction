# CC team02

See [here](README_original.md) for the original README about the given template.

## Content

Contains the cc_team02 full code-base.


## Internal notes

This section contains internal notes about the project.

- **False positive memory-leak**: Valgrind reports a [false positive memory-leak](https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=802778) at `libstdc++.so.6.0.21`.

See [issues](https://github.com/YusufIpek/CompilerConstruction/issues) for project progress and additional information.

## Setup

This section describes the minimal prerequisites, the build steps as well as a detailed description about the different targets. This project offers a build configuration for both build-systems **meson** and **cmake**.

Minimal prerequisites for both build-systems:

- flex 2.6.0
- bison (GNU Bison) 3.0.4
- valgrind-3.11.0
- doxygen 1.8.11

### Meson
  
This is the recommended build-system to use for building the project, because cmake requires some extra dependencies that are not so easy to enforce (see next section). Therefore please use mason if you want less configuration/installation effort.

Additional minimal prerequisites for a build with **meson**:

- meson 0.45.0
- ninja 1.5.1  

Manual build steps:

1. Clone or download the code-base.
2. Build ninja-infrastructure: `$ meson builddir`
3. If you want to build in debug-mode, use `$ meson builddir --buildtype=debug`
4. Move into builddir: `$ cd builddir`
5. (Optional) Run ninja to build the whole project: `$ ninja`
6. Execute targets (See possible targets) via: `$ ninja <target>`

Using the setup-wrapper:

1. Clone or download the code-base.
2. Build ninja-infrastructure: `$ ./setup-wrapper meson "<meson-args>"`
3. Move into builddir: `$ cd builddir`
4. Execute targets (See possible targets) via: `$ ninja <target>`

### CMake

This build-system is used for developing because it exists for longer than meson (which is very new) and hence it provides already a good tool support for IDEs. It is not considered the "default-build-system" for this project because it requires more effort to setup. But it is a nice build-system too.

Additional minimal prerequisites for a build with **cmake**:

- libcurl4-openssl-dev 7.47.0
- cmake 3.9.6

Please note that the downloaded files need to be installed manually using `./bootstrap --system-curl` to [ensure ssl-support](https://stackoverflow.com/questions/29816529/unsupported-protocol-while-download-tar-gz-package) (which is needed to automatically download external projects).

Manual build steps:

1. Clone or download the code-base.
2. Create the directory where to store the makefiles + binaries: `$ mkdir build`
3. Move to the build-directory: `$ cd build`
4. Build cmake-infrastructure: `$ cmake ../`
5. If you want to build in debug-mode, use: `$ cmake -DCMAKE_BUILD_TYPE:STRING=Debug ../`
6. (Optional) Build the whole project: `$ make all`
7. Execute targets (See possible targets) via: `$ make <target>`

Using the setup-wrapper:

1. Clone or download the code-base.
2. Build cmake-infrastructure: `$ ./setup-wrapper cmake "<cmake-args>"`
3. Move to the build-directory: `$ cd build`
4. Execute targets (See possible targets) via: `$ make <target>`

**Note**: If there occur strange error-messages from cmake, try to delete the build-directory.

### Targets

This section lists the available targets that can be build.

| Target        | Description	| Additional notes  | For cmake | For meson|
| ------------- |-------------	|------------------	|---------------|-------|
| all			| Self explanatory | -	| Yes | Yes |
| clean			| Self explanatory      |   -			|  Yes 	|   Yes |
| doxygen		| Builds the documentation      |    - 			|  Yes 	|    Yes |
| test\*			| Runs all gtests (unit)	| - | Yes |  Yes |
| build\_and\_test\* | Runs all gtests (unit; and builds all needed targets) | In cmake the default test-target does not ensure a rebuild. |  Yes  | No |
| build\_and\_test_memcheck\* | Runs all gtests together with valgrind | To run tests with valgrind in meson use `$ meson test --wrap=valgrind` (see [here](https://github.com/mesonbuild/meson/blob/master/docs/markdown/Unit-tests.md)). |  Yes  | No |
| integration\_test | Runs all integration-tests (and builds all needed targets) | It runs the provided [shell-script](https://github.com/W4RH4WK/mCc/blob/master/test/integration). | Yes  | Yes |
| benchmark		| Runs all benchmarks	| It is currently not used, but maybe in the future: Meson suports it "out of the box". | No | Yes |
| run\_benchmarks | Runs all benchmarks | It is currently not used, but maybe in the future: CMake requires the [google-benchmark](https://github.com/google/benchmark) for this task. A custom shell script then runs all the benchmarked source-files. | Yes  | No |

\* Test-targets execute also printer-tests: They don't have any "gtest-assertions" but print the asts (dot-notation) into the build-directory. This dot files are named as follow:


`DOT_<test_name>.dot`