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

// The fixture for testing class Foo.
class InversePowerMethodTestDouble : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    InversePowerMethodTestDouble(): method(1000, 1e-8) {
        // You can do set-up work for each test here.
        MaxIter = 1000;
        tol = 1e-8;
    }

    ~InversePowerMethodTestDouble() override {
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
    InversePowerMethod<double> method;
};

TEST_F(InversePowerMethodTestDouble, invalidMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_THROW(method.calculateEigenvalue(I), std::invalid_argument);
    }

TEST_F(InversePowerMethodTestDouble, noConvergence) {
    Matrix2d II;
    II << 1,2,
          2,1;
    ASSERT_THROW(method.calculateEigenvalue(II), std::runtime_error);
}

TEST_F(InversePowerMethodTestDouble, simpleDoubleMatrix) {
    Matrix3d III;
    III << 1,2,3,
    4,5,6,
    7,8,10;
    double real = III.eigenvalues().cwiseAbs().minCoeff();
    ASSERT_NEAR(method.calculateEigenvalue(III), real, 1e-5);
}

// add more module to test convergence.
class InversePowerMethodTestComplex : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    InversePowerMethodTestComplex(): method(10000, 1e-5) {
        // You can do set-up work for each test here.
        MaxIter = 10000;
        tol = 1e-5;
    }

    ~InversePowerMethodTestComplex() override {
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
//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}
