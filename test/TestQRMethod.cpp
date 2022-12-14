//
// Created by suo on 10.12.22.
//
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/QRMethod.h"

using namespace std;
using namespace Eigen;

namespace my::project {
namespace {

/**
 * This is a fixture class for QR method using double matrices.
 */
class QRMethodTestDouble : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    QRMethodTestDouble(): MaxIter(10000), tol(1e-8), method(MaxIter, tol) {
    }

    ~QRMethodTestDouble() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
    int MaxIter;
    double tol;
    QRMethod<double> method;
};

TEST_F(QRMethodTestDouble, noImplementedMethod) {
    ASSERT_THROW(method.calculateEigenvalue(MatrixXd::Identity(3, 3)), std::logic_error);
}

TEST_F(QRMethodTestDouble, constantMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    Vector3d real;
    real << 3,0,0;
    Vector3d compute = method.calculateEigenvalues(I);
    ASSERT_NEAR((compute-real).norm(), 0, 1e-5);
}

TEST_F(QRMethodTestDouble, simpleDoubleMatrix) {
    MatrixXd II(3,3);
    II << 1,2,3,
          4,5,6,
          7,8,10;
    VectorXcd compute = method.calculateEigenvalues(II);
    VectorXcd real = II.eigenvalues();
    ASSERT_NEAR((compute-real).norm(), 0, 1e-5);
}

/**
 * This is a fixture class for QR method using complex matrices.
 */
class QRMethodTestComplex : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    QRMethodTestComplex(): MaxIter(10000), tol(1e-8), method(MaxIter, tol) {
    }

    ~QRMethodTestComplex() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
    int MaxIter;
    double tol;
    QRMethod<std::complex<double>> method;
};

TEST_F(QRMethodTestComplex, simpleComplexMatrix) {
    MatrixXcd I(2,2);
    I(0,0) = std::complex<double>(1.0, 1.0);
    I(0,1) = std::complex<double>(2.0, -1.0);
    I(1,0) = std::complex<double>(2.0, -1.0);
    I(1,1) = std::complex<double>(1.0, 1.0);

    VectorXcd real(2);
    real << std::complex<double>(3,0), std::complex<double>(-1,2);
    VectorXcd compute = method.calculateEigenvalues(I);
    ASSERT_NEAR((compute-real).norm(), 0, 1e-5);
}

}
}