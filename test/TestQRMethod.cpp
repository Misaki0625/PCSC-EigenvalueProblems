//
// Created by suo on 10.12.22.
//
# include <cmath>
# include <exception>
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/QRMethod.h"

using namespace std;
using namespace Eigen;

namespace my::project {
    namespace {

// The fixture for testing class Foo.
class QRMethodTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    QRMethodTest(): method(1000, 1e-8) {
        // You can do set-up work for each test here.

        MaxIter = 1000;
        tol = 1e-8;
    }

    ~QRMethodTest() override {
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
    QRMethod method;
};

TEST_F(QRMethodTest, ScalarMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 5);
    // Find the largest eigenvalue
    VectorXcd eigenvalues = I.eigenvalues().cwiseAbs();
    ASSERT_NEAR(method.calculateEigenvalues(I).norm(), eigenvalues.norm(), 1e-8);
    }

// Tests that the Foo::Bar() method does Abc.
TEST_F(QRMethodTest, UnitMatrix) {
    MatrixXd II = Eigen::MatrixXd::Identity(3, 3);
    VectorXcd eigenvalues = II.eigenvalues().cwiseAbs();
    ASSERT_NEAR(method.calculateEigenvalues(II).norm(), eigenvalues.norm(), 1e-8);
}

TEST_F(QRMethodTest, SelfAdjointMatrix) {
    MatrixXd III;
    III << 1,2,3,
    2,4,6,
    3,6,5;
    VectorXcd eigenvalues = III.eigenvalues().cwiseAbs();
    ASSERT_NEAR(method.calculateEigenvalues(III).norm(), eigenvalues.norm(), 1e-8);
}

// add more module to test convergence.

}
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}