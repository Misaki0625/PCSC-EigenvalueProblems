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

/**
 * This is a fixture class for power method to compute all eigenvalues.
 */
class PowerMethodAllTest : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    PowerMethodAllTest() :  method(10000, 1e-8) {
    }

    ~PowerMethodAllTest() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
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
    ASSERT_NEAR((compute-real).norm(), 0, 1e-5);
}

}
}
