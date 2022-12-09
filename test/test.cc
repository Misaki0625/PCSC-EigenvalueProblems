# include <cmath>
# include <exception>
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/PowerMethod.h"

using namespace std;
using namespace Eigen;

TEST(sqrt, integer) { EXPECT_EQ(2, std::sqrt(4)); }

TEST(MysqrtTest, positive_integers) {
    EXPECT_EQ(2, sqrt(4));
    EXPECT_EQ(4, sqrt(16));
    EXPECT_EQ(3, sqrt(9));
}

TEST(PowerMethodTest, Matrix) {
    ASSERT_NEAR(std::sqrt(2), sqrt(2), 1e-15);
    ASSERT_NEAR(std::sqrt(3), sqrt(3), 1e-15);
}

TEST(PowerMethodTest, RandomMatrix) {
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver;
    PowerMethod powerMethod(10000, 1e-5);
    Eigen::Matrix3d I;
    I << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    // EXPECT_EQ(f.Bar(input_filepath, output_filepath), 0);
    solver.compute(I);
    // Find the largest eigenvalue
    double maxEigenvalue = solver.eigenvalues().maxCoeff();
    ASSERT_NEAR(powerMethod.calculateEigenvalue(I), maxEigenvalue, 1e-8);

}
// Tests that the Foo::Bar() method does Abc.
TEST(PowerMethodTest, UnitMatrix) {
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver;
    PowerMethod powerMethod(1000,1e-8);
    MatrixXd II = Eigen::MatrixXd::Identity(3, 3);
    solver.compute(II);
    // Find the largest eigenvalue
    double maxEigenvalue = solver.eigenvalues().maxCoeff();
    ASSERT_NEAR(powerMethod.calculateEigenvalue(II), maxEigenvalue, 1e-8);
}

//TEST(PowerMethodTest, SelfAdjointMatrix) {
//    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver;
//    PowerMethod powerMethod(1000,1e-8);
//    MatrixXd III = Eigen::MatrixXd::Random(3, 3);
//    solver.compute(III);
//    // Find the largest eigenvalue
//    double maxEigenvalue = solver.eigenvalues().maxCoeff();
//    ASSERT_NEAR(powerMethod.calculateEigenvalue(III), maxEigenvalue, 1e-8);
//}

