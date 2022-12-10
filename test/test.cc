# include <cmath>
# include <exception>
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/PowerMethod.h"

using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
