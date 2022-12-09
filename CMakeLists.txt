
cmake_minimum_required (VERSION 3.0)

project (PCSC-project)

set(CMAKE_CXX_STANDARD 17)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_library(pcsc
        src/pcsc.cc
        )

add_subdirectory(googletest)
include_directories(eigen)

add_executable(main src/main.cc)
target_link_libraries(main pcsc)

add_executable(matrix src/matrix.cpp)
target_link_libraries(matrix pcsc)

add_executable(test_pcsc test/TestQRMethod.cpp)
target_link_libraries(test_pcsc gtest_main gtest pthread pcsc)

add_custom_target(test ./test_pcsc DEPENDS test_pcsc)