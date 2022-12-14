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

/**
 * This is a fixture class for CSV reader.
 */
class ReadFileTestCSV : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    ReadFileTestCSV() :  readerI(), readerII() {
    }

    ~ReadFileTestCSV() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
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


/**
 * This is a fixture class for binary reader.
 */
class ReadFileTestBinary : public ::testing::Test {
protected:

    /**
     * Constructor and destructor.
     */
    ReadFileTestBinary() :  readerI(),
                            readerII() {
    }

    ~ReadFileTestBinary() override {
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    // Class members declared here
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