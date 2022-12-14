//
// Created by suo on 10.12.22.
//
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/InversePowerMethod.h"

using namespace std;
using namespace Eigen;

namespace my::project {
namespace {

/**
 * This is a fixture class for inverse power method using double matrices
 */
class InversePowerMethodTestDouble : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    InversePowerMethodTestDouble(): methodI(1, 1e-8),
                                    methodII(1000, 1e-8) {
        MaxIter = 1000;
        tol = 1e-8;
    }

    ~InversePowerMethodTestDouble() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
    int MaxIter;
    double tol;
    InversePowerMethod<double> methodI;
    InversePowerMethod<double> methodII;
};

TEST_F(InversePowerMethodTestDouble, invalidMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_THROW(methodI.calculateEigenvalue(I), std::invalid_argument);
    }

TEST_F(InversePowerMethodTestDouble, noConvergence) {
    Matrix3d II;
    II << 1,2,3,
          2,1,3,
          4,5,2;
    ASSERT_THROW(methodI.calculateEigenvalue(II), std::runtime_error);
}

TEST_F(InversePowerMethodTestDouble, simpleDoubleMatrix) {
    Matrix3d III;
    III << 1,2,3,
    4,5,6,
    7,8,10;
    double real = III.eigenvalues().cwiseAbs().minCoeff();
    ASSERT_NEAR(methodII.calculateEigenvalue(III), real, 1e-5);
}

/**
 * This is a fixture class for inverse power method using complex matrices
 */
class InversePowerMethodTestComplex : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    InversePowerMethodTestComplex(): method(10000, 1e-5) {
        MaxIter = 10000;
        tol = 1e-5;
    }

    ~InversePowerMethodTestComplex() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
    int MaxIter;
    double tol;
    InversePowerMethod<std::complex<double>> method;
};

TEST_F(InversePowerMethodTestComplex, invalidMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_THROW(method.calculateEigenvalue(I), std::invalid_argument);
}

TEST_F(InversePowerMethodTestComplex, simpleComplexMatrix) {
    MatrixXcd II(2,2);
    II(0,0) = std::complex<double>(1.0, 1.0);
    II(0,1) = std::complex<double>(1.0, -2.0);
    II(1,0) = std::complex<double>(1.0, -2.0);
    II(1,1) = std::complex<double>(-1.0, -1.0);
    auto real = II.eigenvalues()(0);
    auto compute = method.calculateEigenvalue(II);
    ASSERT_NEAR(std::abs(compute-real), 0.0, 1e-6);
}
}
}