
cmake_minimum_required (VERSION 3.14)
project (PCSC-project)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
# find_package(argparse REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_library(pcsc
  src/pcsc.cc
)

add_subdirectory(googletest)
add_subdirectory(argparse)
include_directories(eigen)
include_directories(SYSTEM /usr/local/include)
include_directories(argparse)
# set(FILELIST src/main.cc src/pcsc.cc src/ReadFile.cpp)

add_executable(main src/main.cc)
target_link_libraries(main -largparse)
# target_link_libraries(main pcsc)
# target_link_libraries(main pcsc)

#add_executable(QR src/QRMethod.cpp)
#add_executable(try src/try.cpp)
#add_executable(eigensolver src/eigensolver.cpp)
#add_executable(power src/PowerMethod.cpp)
#
#add_executable(readfile src/ReadFiles.cpp)

add_executable(test_pcsc test/test.cc)
target_link_libraries(test_pcsc gtest_main gtest pthread pcsc)

add_custom_target(test ./test_pcsc DEPENDS test_pcsc)
