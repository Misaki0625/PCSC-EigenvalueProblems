//
// Created by suo on 10.12.22.
//
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/InversePowerMethodShifted.h"

using namespace std;
using namespace Eigen;

namespace my::project {
namespace {

// The fixture for testing class Foo.
class InversePowerMethodShiftedTest : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    InversePowerMethodShiftedTest() : methodI(10000, 1e-8, "default"),
                                      methodII(10000, 1e-8, "15"),
                                      methodIII(10000, 1e-8, "0"),
                                      methodIV(10000, 1e-8, "-10"){
        // You can do set-up work for each test here.
    }

    ~InversePowerMethodShiftedTest() override {
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
    InversePowerMethodWithShift<double> methodI;
    InversePowerMethodWithShift<double> methodII;
    InversePowerMethodWithShift<double> methodIII;
    InversePowerMethodWithShift<double> methodIV;
};

TEST_F(InversePowerMethodShiftedTest, noImplementedMethod) {
    ASSERT_THROW(methodI.calculateEigenvalues(MatrixXd::Identity(3, 3)), std::logic_error);
}

TEST_F(InversePowerMethodShiftedTest, invalidMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_THROW(methodI.calculateEigenvalue(I), std::invalid_argument);
}

TEST_F(InversePowerMethodShiftedTest, computeLargestEigenvalue) {
    MatrixXd II(3, 3);
    II << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodII.calculateEigenvalue(II), II.eigenvalues()(0).real(), 1e-6);
}

TEST_F(InversePowerMethodShiftedTest, computeMiddleEigenvalue) {
    MatrixXd III(3, 3);
    III << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodIII.calculateEigenvalue(III), III.eigenvalues()(2).real(), 1e-6);
}

TEST_F(InversePowerMethodShiftedTest, computeSmallestEigenvalue) {
    MatrixXd IV(3, 3);
    IV << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodIV.calculateEigenvalue(IV), IV.eigenvalues()(1).real(), 1e-6);
}
}
}