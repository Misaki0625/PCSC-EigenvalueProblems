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
class InversePowerMethodTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    InversePowerMethodTest(): method(1000, 1e-8) {
        // You can do set-up work for each test here.
        MaxIter = 1000;
        tol = 1e-8;
    }

    ~InversePowerMethodTest() override {
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
    InversePowerMethod method;
    // Create a SelfAdjointEigenSolver object
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver;
};

TEST_F(InversePowerMethodTest, ScalarMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_THROW(method.calculateEigenvalue(I), std::invalid_argument);
    }

TEST_F(InversePowerMethodTest, UnitMatrix) {
    MatrixXd II = Eigen::MatrixXd::Identity(3, 3);
    solver.compute(II);
    // Find the smallest eigenvalue
    double minEigenvalue = solver.eigenvalues().cwiseAbs().minCoeff();
    ASSERT_NEAR(method.calculateEigenvalue(II), minEigenvalue, 1e-8);
}

TEST_F(InversePowerMethodTest, SelfAdjointMatrix) {
    MatrixXd III;
    III << 1,2,3,
    2,4,6,
    3,6,5;
    solver.compute(III);
    // Find the largest eigenvalue
    double minEigenvalue = solver.eigenvalues().cwiseAbs().minCoeff();
    ASSERT_NEAR(method.calculateEigenvalue(III), minEigenvalue, 1e-8);
}

// add more module to test convergence.

}
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
