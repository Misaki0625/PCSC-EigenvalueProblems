//
// Created by suo on 10.12.22.
//
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/PowerMethodAll.h"

using namespace std;
using namespace Eigen;

namespace my::project {
namespace {

// The fixture for testing class Foo.
class PowerMethodAllTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    PowerMethodAllTest() :  method(10000, 1e-8) {
        // You can do set-up work for each test here.
    }

    ~PowerMethodAllTest() override {
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
    PowerMethodAll<double> method;
};

TEST_F(PowerMethodAllTest, noImplementedMethod) {
    ASSERT_THROW(method.calculateEigenvalue(MatrixXd::Identity(3, 3)), std::logic_error);
}

TEST_F(PowerMethodAllTest, invalidMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_THROW(method.calculateEigenvalues(I), std::invalid_argument);
}

TEST_F(PowerMethodAllTest, computeAllEigenvalue) {
    MatrixXd II(3, 3);
    II << 1,2,3,
          4,5,6,
          7,8,10;
    VectorXcd real = II.eigenvalues();
    VectorXcd compute = method.calculateEigenvalues(II);
    ASSERT_NEAR((compute-real).norm(), 0, 1e-8);
}

}
}
