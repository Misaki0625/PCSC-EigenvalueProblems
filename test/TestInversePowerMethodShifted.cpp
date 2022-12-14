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

/**
 * This is a fixture class for inverse power method with shift.
 */
class InversePowerMethodShiftedTest : public ::testing::Test {
protected:
    /**
     * Constructor and destructor.
     */
    InversePowerMethodShiftedTest() : methodI(10000, 1e-8, 15),
                                      methodII(10000, 1e-8, 0),
                                      methodIII(10000, 1e-8, -10){
    }

    ~InversePowerMethodShiftedTest() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
    InversePowerMethodWithShift<double> methodI;
    InversePowerMethodWithShift<double> methodII;
    InversePowerMethodWithShift<double> methodIII;
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
    ASSERT_NEAR(methodI.calculateEigenvalue(II), II.eigenvalues()(0).real(), 1e-6);
}

TEST_F(InversePowerMethodShiftedTest, computeMiddleEigenvalue) {
    MatrixXd III(3, 3);
    III << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodII.calculateEigenvalue(III), III.eigenvalues()(2).real(), 1e-6);
}

TEST_F(InversePowerMethodShiftedTest, computeSmallestEigenvalue) {
    MatrixXd IV(3, 3);
    IV << 1,2,3,
            4,5,6,
            7,8,10;
    ASSERT_NEAR(methodIII.calculateEigenvalue(IV), IV.eigenvalues()(1).real(), 1e-6);
}
}
}