# Setup

1. Install cmake:

   `sudo apt-get install cmake`

   `sudo apt-get install valgrind`

   `sudo apt-get install libcurl4-openssl-dev`
   
2. Install google test:

   `sudo apt-get install libgtest-dev`
      
   `cd /usr/src/gtest`
   
   `sudo cmake CMakeLists.txt`
   
   `sudo make`
   
   `sudo cp *.a /usr/lib`

3. Clone templates:

   `git clone https://github.com/W4RH4WK/mCc.git`

4. Install flex + bison + doxygen + clang-format 5.0 (at least):

   `sudo apt-get install flex`
   
   `sudo apt-get install bison`
   
   `sudo apt-get install doxygen`

   `sudo apt-get install clang-format-5.0`
