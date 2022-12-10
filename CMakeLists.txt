
cmake_minimum_required (VERSION 3.0)

project (PCSC-project)

set(CMAKE_CXX_STANDARD 17)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

#add_library(pcsc
#        src/pcsc.cc
#        )

add_subdirectory(googletest)
include_directories(eigen)

add_executable(main
        src/main.cc
        src/ReadFiles.cpp
        src/GeneralMethod.cpp
        src/SingleEigenMethod.cpp
        src/AllEigenMethod.cpp
        src/PowerMethod.cpp
        src/InversePowerMethod.cpp
        src/PowerMethodShifted.cpp
        src/InversePowerMethodShifted.cpp
        src/PowerMethodAll.cpp
        src/QRMethod.cpp)

add_executable(matrix src/matrix.cpp)

aux_source_directory(test test_source)
add_executable(test_pcsc ${test_source})
target_link_libraries(test_pcsc gtest_main gtest pthread)

add_custom_target(test ./test_pcsc DEPENDS test_pcsc)

file(COPY src/matrix.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/data.bin DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(COPY src/output.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})