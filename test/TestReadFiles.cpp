//
// Created by suo on 11.12.22.
//
# include <gtest/gtest.h>
# include <Eigen/Dense>
# include "../src/ReadFiles.h"

using namespace std;
using namespace Eigen;

namespace my::project {
namespace {

// The fixture for testing class Foo.
class ReadFileTestCSV : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    ReadFileTestCSV() :  readerI(), readerII() {
        // You can do set-up work for each test here.
    }

    ~ReadFileTestCSV() override {
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
    CSVReader<double> readerI;
    CSVReader<std::complex<double>> readerII;
};

TEST_F(ReadFileTestCSV, readDoubleMatrix) {
    auto m1 = readerI.read("matrix.csv");
    MatrixXd m2(3,3);
    m2 << 1,2,3,
            4,5,6,
            7,8,10;
    EXPECT_EQ(m1, m2);
}

TEST_F(ReadFileTestCSV, readComplexMatrix) {
    auto m1 = readerII.read("matrix.csv");
    MatrixXcd m2(3,3);
    m2 << 1,2,3,
            4,5,6,
            7,8,10;
    EXPECT_EQ(m1, m2);
}


// The fixture for testing class Foo.
class ReadFileTestBinary : public ::testing::Test {
protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    ReadFileTestBinary() :  readerI(),
                            readerII() {
        // You can do set-up work for each test here.
    }

    ~ReadFileTestBinary() override {
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
    BinaryReader<double> readerI;
    BinaryReader<std::complex<double>> readerII;
};

TEST_F(ReadFileTestBinary, readDoubleMatrix) {
    auto m1 = readerI.read("data.bin");
    MatrixXd m2(3,3);
    m2 << 1,2,4,4,5,6,7,8,10;
    EXPECT_EQ(m1, m2);
}
TEST_F(ReadFileTestBinary, readComplexMatrix) {
    auto m1 = readerII.read("data.bin");
    MatrixXcd m2(2,2);
    m2(0,0) = std::complex<double>(1.0, 4.0);
    m2(0,1) = std::complex<double>(5.0, 8.0);
    m2(1,0) = std::complex<double>(7.0, 2.0);
    m2(1,1) = std::complex<double>(4.0, 6.0);
    EXPECT_EQ(m1, m2);
}

}
}