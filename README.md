# CompilerConstruction
Compiler construction assignments  will be uploaded in this repo.

## Setup

1. Install meson:

   `pip3 install meson`
   
   NOTE: In 16.04 LTS only version 0.29 available   
   
2. Install google test:
   `sudo apt-get install libgtest-dev`
   
   `sudo apt-get install cmake # install cmake`
   
   `cd /usr/src/gtest`
   
   `sudo cmake CMakeLists.txt`
   
   `sudo make`
   
   `sudo cp *.a /usr/lib`

3. Clone templates:

   `git clone https://github.com/W4RH4WK/mCc.git`

4. Install flex + bison + doxygen:

   `sudo apt-get install flex`
   
   `sudo apt-get install bison`
   
   `sudo apt-get install doxygen`
   
## Changes to provided template

- cmake-configuration added
- template-files integrated and setup with cmake
