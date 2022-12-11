//
// Created by suo on 10.12.22.
//
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/PowerMethodShifted.h"

using namespace std;
using namespace Eigen;

namespace my::project {
namespace {

// The fixture for testing class Foo.
class PowerMethodShiftedTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    PowerMethodShiftedTest() :  methodI(10000, 1e-8, "default"),
                                methodII(10000, 1e-8, "15"),
                                methodIII(10000, 1e-8, "0"),
                                methodIV(10000, 1e-8, "-10"){
        // You can do set-up work for each test here.
    }

    ~PowerMethodShiftedTest() override {
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
    PowerMethodWithShift<double> methodI;
    PowerMethodWithShift<double> methodII;
    PowerMethodWithShift<double> methodIII;
    PowerMethodWithShift<double> methodIV;
};

TEST_F(PowerMethodShiftedTest, noImplementedMethod) {
    ASSERT_THROW(methodI.calculateEigenvalues(MatrixXd::Identity(3, 3)), std::logic_error);
}

TEST_F(PowerMethodShiftedTest, constantMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_NEAR(methodI.calculateEigenvalue(I), 0, 1e-8);
}

TEST_F(PowerMethodShiftedTest, computeLargestEigenvalue) {
    MatrixXd II(3, 3);
    II << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodII.calculateEigenvalue(II), II.eigenvalues()(0).real(), 1e-8);
}

TEST_F(PowerMethodShiftedTest, computeMiddleEigenvalue) {
    MatrixXd III(3, 3);
    III << 1,2,3,
            4,5,6,
            7,8,10;
    double real = III.eigenvalues()(2).real();
    double compute = methodIII.calculateEigenvalue(III);
    ASSERT_NEAR(abs(real-compute), 0.0, 1e-8);
}

TEST_F(PowerMethodShiftedTest, computeSmallestEigenvalue) {
    Matrix3d IV;
    IV << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodIV.calculateEigenvalue(IV), IV.eigenvalues()(1).real(), 1e-8);
}
}
}