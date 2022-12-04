# Install script for directory: /Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/AdolcForward"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/AlignedVector3"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/ArpackSupport"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/AutoDiff"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/BVH"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/EulerAngles"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/FFT"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/IterativeSolvers"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/KroneckerProduct"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/LevenbergMarquardt"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/MatrixFunctions"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/MoreVectorization"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/MPRealSupport"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/NonLinearOptimization"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/NumericalDiff"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/OpenGLSupport"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/Polynomials"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/Skyline"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/SparseExtra"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/SpecialFunctions"
    "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/Splines"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/eigen/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/cmake-build-debug/eigen/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

