
cmake_minimum_required (VERSION 3.0)
project (PCSC-project)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

set(CMAKE_CXX_STANDARD 17)

add_library(pcsc
  src/pcsc.cc
)

add_subdirectory(googletest)
include_directories(eigen)

# set(FILELIST src/main.cc src/pcsc.cc src/ReadFile.cpp)

add_executable(main src/main.cpp)
target_link_libraries(main pcsc)

add_executable(readfile src/ReadFiles.cpp)

add_executable(test_pcsc test/test.cc)
target_link_libraries(test_pcsc gtest_main gtest pthread pcsc)

add_custom_target(test ./test_pcsc DEPENDS test_pcsc)
