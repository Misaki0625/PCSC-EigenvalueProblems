//
// Created by suo on 09.12.22.
//
# include <cmath>
# include <exception>
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/PowerMethod.h"

using namespace std;
using namespace Eigen;

namespace my::project {
namespace {

// The fixture for testing class Foo.
class PowerMethodTestDouble : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    PowerMethodTestDouble(): MaxIter(1000), tol(1e-8), powerMethod(MaxIter, tol) {
        // You can do set-up work for each test here.
    }

    ~PowerMethodTestDouble() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

//     If the constructor and destructor are not enough for setting up
//     and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
    int MaxIter;
    double tol;
    PowerMethod<double> powerMethod;
};

TEST_F(PowerMethodTestDouble, constantMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_NEAR(powerMethod.calculateEigenvalue(I), 3, 1e-6);

}
// Tests that the Foo::Bar() method does Abc.
TEST_F(PowerMethodTestDouble, unitMatrix) {
    MatrixXd II = Eigen::MatrixXd::Identity(3, 3);
    ASSERT_NEAR(powerMethod.calculateEigenvalue(II), 1, 1e-6);
}

TEST_F(PowerMethodTestDouble, selfAdjointMatrix) {
    MatrixXd III(2,2);
    III << 1,2,
           2,3;
    ASSERT_NEAR(powerMethod.calculateEigenvalue(III), III.eigenvalues().cwiseAbs().maxCoeff(), 1e-6);
}

// add more module to test convergence.
class PowerMethodTestComplex : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    PowerMethodTestComplex(): MaxIter(10000), tol(1e-8), powerMethod(MaxIter, tol) {
        // You can do set-up work for each test here.
    }

    ~PowerMethodTestComplex() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

//     If the constructor and destructor are not enough for setting up
//     and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
    int MaxIter;
    double tol;
    PowerMethod<std::complex<double>> powerMethod;
};

TEST_F(PowerMethodTestComplex, constantMatrix) {
    // auto I = Eigen::Matrix<std::complex<double>, -1, -1>::Constant(3, 3, 1);
    MatrixXcd I = Eigen::MatrixXcd::Constant(3,3,1);
    auto real = std::complex<double>{3, 0};
    auto compute = powerMethod.calculateEigenvalue(I);
    ASSERT_NEAR(compute.real(), real.real(), 1e-6);
    ASSERT_NEAR(compute.imag(), real.imag(), 1e-6);
}

TEST_F(PowerMethodTestComplex, selfAdjointMatrix) {
    MatrixXcd II(2,2);
    II << 1,2,
          2,4;
    auto real = std::complex<double>{5, 0};
    auto compute = powerMethod.calculateEigenvalue(II);
    ASSERT_NEAR(compute.real(), real.real(), 1e-6);
    ASSERT_NEAR(compute.imag(), real.imag(), 1e-6);
}

TEST_F(PowerMethodTestComplex, simpleComplexMatrix) {
    MatrixXcd III(2,2);
    III(0,0) = std::complex<double>(1.0, 1.0);
    III(0,1) = std::complex<double>(2.0, -1.0);
    III(1,0) = std::complex<double>(2.0, -1.0);
    III(1,1) = std::complex<double>(1.0, 1.0);
    auto real = std::complex<double>{3, 0};
    auto compute = powerMethod.calculateEigenvalue(III);
    ASSERT_NEAR(compute.real(), real.real(), 1e-6);
    ASSERT_NEAR(compute.imag(), real.imag(), 1e-6);
}

}
}