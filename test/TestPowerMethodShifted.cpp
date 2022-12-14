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

/**
 * This is a fixture class for power method with shift.
 */
class PowerMethodShiftedTest : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    PowerMethodShiftedTest() :  methodI(10000, 1e-8, 15),
                                methodII(10000, 1e-8, 0),
                                methodIII(10000, 1e-8, -10) {
    }

    ~PowerMethodShiftedTest() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
    PowerMethodWithShift<double> methodI;
    PowerMethodWithShift<double> methodII;
    PowerMethodWithShift<double> methodIII;
};

TEST_F(PowerMethodShiftedTest, noImplementedMethod) {
    ASSERT_THROW(methodI.calculateEigenvalues(MatrixXd::Identity(3, 3)), std::logic_error);
}

TEST_F(PowerMethodShiftedTest, constantMatrix) {
    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);
    ASSERT_NEAR(methodI.calculateEigenvalue(I), 3, 1e-5);
}

TEST_F(PowerMethodShiftedTest, computeLargestEigenvalue) {
    MatrixXd II(3, 3);
    II << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodI.calculateEigenvalue(II), II.eigenvalues()(0).real(), 1e-5);
}

TEST_F(PowerMethodShiftedTest, computeMiddleEigenvalue) {
    MatrixXd III(3, 3);
    III << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodII.calculateEigenvalue(III), III.eigenvalues()(2).real(), 1e-5);
}

TEST_F(PowerMethodShiftedTest, computeSmallestEigenvalue) {
    MatrixXd IV(3, 3);
    IV << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodIII.calculateEigenvalue(IV), IV.eigenvalues()(1).real(), 1e-5);
}
}
}