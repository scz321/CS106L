#!/bin/bash

# download cpr and dependencies
echo 'Now downloading dependencies. Sit tight! This might take a few minutes!'
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
./vcpkg integrate install
./vcpkg install cpr
cd ..

# set up build directory
echo 'Now building, compiling, and running project.'
mkdir build
cd build
echo '#!/bin/bash

cmake .. "-DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build .' > build.sh
chmod +x build.sh

# build test configuration!
echo '#!/bin/bash

cmake .. "-DTEST_WIKISCRAPER=ON -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build .' > build-test.sh
chmod +x build-test.sh

cd ..
# confirm and print out confirmation message + instructions.
echo '#!/bin/bash
set -e

cd build
rm -f CMakeCache.txt
./build.sh
cd ..
./build/main' > build_and_run.sh
chmod +x build_and_run.sh

# build to set path to CPR
echo 'Successfully built! Running ./build_and_run.sh.'
rm -f build/CMakeCache.txt
# ./build_and_run.sh
# rm -f build/CMakeCache.txt

echo 'cmake_minimum_required(VERSION 3.0)
project(wikiracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(cpr CONFIG REQUIRED)
option(TEST_WIKISCRAPER "Test wikiracer only" OFF)

if(TEST_WIKISCRAPER)
    message("Building Wikiscraper Test")
    add_executable(test test-wikiscraper.cpp wikiscraper.cpp error.cpp)
    target_link_libraries(test PRIVATE cpr::cpr)
else()
    message("Building Entire Project")
    add_executable(main main.cpp wikiscraper.cpp error.cpp)
    target_link_libraries(main PRIVATE cpr::cpr)
endif()' >| CMakeLists.txt

echo 'Trying to build now!'
./build_and_run.sh

echo 'All done! From now on, all you have to do to compile, build, and run your entire project
is to type "./build_and_run.sh" (without the quotes) and hit enter. Before doing so,
you will want to complete wikiscraper.cpp and test it with "./test-wikiscraper.sh". Once you
are passing all of those tests, feel free to run ./build_and_run.sh to build the entire project!
If you run into any issues and want to quit out of the program, press the ctrl and c key
at the same time!'
