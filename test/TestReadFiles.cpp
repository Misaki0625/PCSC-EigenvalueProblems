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

    ReadFileTestCSV() :  reader() {
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
    CSVReader<double> reader;
};

TEST_F(ReadFileTestCSV, readDoubleMatrix) {
    MatrixXd m1(2,2);
    MatrixXd m2(2,2);
    m1 << 1,2,3,4;
    m2 << 1,2,3,4;
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
    MatrixXd m1(2,2);
    MatrixXd m2(2,2);
    m1 << 1,2,3,4;
    m2 << 1,2,3,4;
    EXPECT_EQ(m1, m2);
}
TEST_F(ReadFileTestBinary, readComplexMatrix) {
    MatrixXd m1(2,2);
    MatrixXd m2(2,2);
    m1 << 1,2,3,4;
    m2 << 1,2,3,4;
    EXPECT_EQ(m1, m2);
}

}
}