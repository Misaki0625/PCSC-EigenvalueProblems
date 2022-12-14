//
// Created by suo on 09.12.22.
//
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/PowerMethod.h"

using namespace std;
using namespace Eigen;

namespace my::project {
namespace {

/**
 * This is a fixture class for power method using double matrices
 */
class PowerMethodTestDouble : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    PowerMethodTestDouble(): MaxIter(1000), tol(1e-8), powerMethod(MaxIter, tol) {
    }

    ~PowerMethodTestDouble() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
    int MaxIter;
    double tol;
    PowerMethod<double> powerMethod;
};

TEST_F(PowerMethodTestDouble, constantMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_NEAR(powerMethod.calculateEigenvalue(I), 3, 1e-5);

}

TEST_F(PowerMethodTestDouble, unitMatrix) {
    MatrixXd II = Eigen::MatrixXd::Identity(3, 3);
    ASSERT_NEAR(powerMethod.calculateEigenvalue(II), 1, 1e-5);
}

TEST_F(PowerMethodTestDouble, selfAdjointMatrix) {
    MatrixXd III(2,2);
    III << 1,2,
           2,3;
    ASSERT_NEAR(powerMethod.calculateEigenvalue(III), III.eigenvalues().cwiseAbs().maxCoeff(), 1e-5);
}

/**
 * This is a fixture class for power method using complex matrices
 */
class PowerMethodTestComplex : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    PowerMethodTestComplex(): MaxIter(10000), tol(1e-8), powerMethod(MaxIter, tol) {
    }

    ~PowerMethodTestComplex() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
    int MaxIter;
    double tol;
    PowerMethod<std::complex<double>> powerMethod;
};

TEST_F(PowerMethodTestComplex, constantMatrix) {
    MatrixXcd I = Eigen::MatrixXcd::Constant(3,3,1);
    auto real = std::complex<double>{3, 0};
    auto compute = powerMethod.calculateEigenvalue(I);
    ASSERT_NEAR(compute.real(), real.real(), 1e-5);
    ASSERT_NEAR(compute.imag(), real.imag(), 1e-5);
}

TEST_F(PowerMethodTestComplex, selfAdjointMatrix) {
    MatrixXcd II(2,2);
    II << 1,2,
          2,4;
    auto real = std::complex<double>{5, 0};
    auto compute = powerMethod.calculateEigenvalue(II);
    ASSERT_NEAR(compute.real(), real.real(), 1e-5);
    ASSERT_NEAR(compute.imag(), real.imag(), 1e-5);
}

TEST_F(PowerMethodTestComplex, simpleComplexMatrix) {
    MatrixXcd III(2,2);
    III(0,0) = std::complex<double>(1.0, 1.0);
    III(0,1) = std::complex<double>(2.0, -1.0);
    III(1,0) = std::complex<double>(2.0, -1.0);
    III(1,1) = std::complex<double>(1.0, 1.0);
    auto real = std::complex<double>{3, 0};
    auto compute = powerMethod.calculateEigenvalue(III);
    ASSERT_NEAR(compute.real(), real.real(), 1e-5);
    ASSERT_NEAR(compute.imag(), real.imag(), 1e-5);
}

}
}