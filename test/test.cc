# include <cmath>
# include <exception>
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/PowerMethod.h"
# include "../src/InversePowerMethod.h"
# include "../src/PowerMethodShifted.h"
# include "../src/InversePowerMethodShifted.h"
# include "../src/PowerMethodAll.h"
# include "../src/QRMethod.h"
# include "../src/ReadFiles.h"


using namespace std;
using namespace Eigen;

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
