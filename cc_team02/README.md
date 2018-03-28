# CC team02

See [here](README_original.md) for the original README about the given template.

## Content

- cc_team02 (the full code-base)
- The template provided from https://github.com/W4RH4WK/mCc setup with cmake

## Internal notes

This section contains internal notes about the given template.   
See [issues](https://github.com/YusufIpek/CompilerConstruction/issues) for project progress and additional information.

## Setup

This section describes the minimal prerequisites, the build steps as well as a detailed description about the different targets. This project offers a build configuration for both build-tools **meson** and **cmake**.

Minimal prerequisites for both build-tools:  

- flex 2.6.0  
- bison (GNU Bison) 3.0.4 
- valgrind-3.11.0  
- doxygen 1.8.11

### Meson
  
This is the recommended build-tool to use for building the project, because cmake requires some extra dependencies that are not so easy to enforce (see next section). Therefore please use mason if you want less configuration/installation effort.


Additional minimal prerequisites for a build with **meson**:   

- meson 0.45.0  


Build steps:

1. Clone or download the code-base.
2. Build ninja-infrastructure: ```$ meson builddir```
3. Move into builddir: ```$ cd builddir```
4. Run ninja to build the project: ```$ ninja```
5. Execute targets (See possible targets)

### CMake

This build-tool is used for developing because it exists for longer than meson (which is very new) and hence it provides already a good tool support for IDEs. It is not considered the "default-build-tool" for this project because it requires more effort to setup. But it is a nice build-tool too.

Additional minimal prerequisites for a build with **cmake**:

- libcurl4-openssl-dev 7.47.0
- cmake 3.9.6

Please not that the downloaded files need to be installed manually using ```./bootstrap --system-curl``` to ensure ssl-support (which is needed to automatically download external projects)

### Targets

This section lists the available targets that can be build.

| Target        | Description	| Additional notes  | For cmake | For meson|   
| ------------- |-------------	|------------------	|---------------|-------|   
| all			| Self explanatory | -	| Yes | Yes |   
| clean			| Self explanatory      |   -			|  Yes 	|   Yes |   
| doxygen		| Builds the documentation      |    - 			|  Yes 	|    Yes |   
| test			| Runs all gtests (unit)	| - | Yes |  Yes |   
| build_and_test| Runs all gtests (unit; and builds all needed targets) | In cmake the default test-target does not ensure a rebuild |  Yes  | No |  
| build_and_test_memcheck | Runs all gtests together with valgrind | To run tests with valgrind in meson use ```$ meson test --wrap=valgrind``` (see [here](https://github.com/mesonbuild/meson/blob/master/docs/markdown/Unit-tests.md)) |  Yes  | No |  
| integration_test | Runs all integration-tests (and builds all needed targets) | It runs the provided [shell-script](https://github.com/W4RH4WK/mCc/blob/master/test/integration) | Yes  | Yes |  
| benchmark		| Runs all benchmarks	| It is currently not used, but maybe in the future: Meson suports it "out of the box" | No | Yes |  
| run_benchmarks | Runs all benchmarks | It is currently not used, but maybe in the future: CMake requires the [google-benchmark](https://github.com/google/benchmark) for this task. A custom shell script then runs all the benchmarked source-files. | Yes  | No |  
