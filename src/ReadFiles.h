//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_PREADFILES_H
#define PCSC_PROJECT_PREADFILES_H

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>
#include <sys/stat.h>

/**
 * FileReader is a virtual class, where all implemented reader are inherited.
 * It has one virtual function called read, which is override by CSVReader and BinaryReader.
 */
template <typename ScalarType>
class FileReader {
public:

    /**
     * declare MatrixType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;

    /**
     * Constructor and destructor.
     */
    FileReader() = default;
    virtual ~FileReader() = default;

    /**
     * virtual function read.
     */
    virtual MatrixType read(const std::string& filename) = 0;
};

/**
 * CSVReader is an inherited class of FileReader.
 * It overrides the read function to read square matrices from a csv file.
 * This reader only accepts double numbers in the file, and reads them into a double Eigen matrix
 * or complex matrix without imaginary parts. In each row, the elements are separated by ','.
 */
template <typename ScalarType>
class CSVReader : public FileReader<ScalarType> {
public:

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using RowVectorType = Eigen::RowVector<ScalarType, -1>;

    /**
     * Constructor and destructor.
     */
    CSVReader() = default;
    ~CSVReader() override = default;

    /**
     * read function is implemented to read a Eigen matrix from csv files.
     */
    MatrixType read(const std::string& filename) override {
        std::ifstream file(filename);
        MatrixType matrix;
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << "!" << std::endl;
            return {};
        }

        while (std::getline(file, line)) {
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<ScalarType> values;
            while (std::getline(lineStream, cell, ',')) {
                values.push_back(std::stod(cell));
            }
            if (matrix.rows() == 0) {
                matrix.resize(1, values.size());
            } else {
                matrix.conservativeResize(matrix.rows() + 1, Eigen::NoChange);
            }
            matrix.row(matrix.rows() - 1) = Eigen::Map<RowVectorType>(values.data(), values.size());
        }

        file.close();

        return matrix;
    }
};

/**
 * BinaryReader is an inherited class of FileReader.
 * It overrides the read function to read square matrices from a binary file.
 * This reader is able to read double and complex matrices. When writing Eigen matrices to binary file, one should use
 * "ios::binary" option, which is compatible with this function.
 */
template <typename ScalarType>
class BinaryReader : public FileReader<ScalarType> {
public:

    /**
     * declare MatrixType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;

    /**
     * Constructor and destructor.
     */
    BinaryReader() = default;
    ~BinaryReader() override = default;

    /**
     * read function is implemented to read a Eigen matrix from binary files.
     */
    MatrixType read(const std::string &filename) override {
        MatrixType matrix;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << "!" << std::endl;
            return {};
        }
        struct stat stat_buf{};
        int rc = stat(filename.c_str(), &stat_buf);
        if (rc!=0) {
            std::cerr << "Error: Could not read the stat of " << filename << "!" << std::endl;
            return {};
        }
        auto num_elems = stat_buf.st_size / sizeof(ScalarType);
        int rows = (int) sqrt(num_elems);
        int cols = num_elems / rows;
        matrix.resize(rows, cols);
        file.clear();
        file.seekg(0, std::ios::beg);
        file.read((char *) matrix.data(), rows * cols * sizeof(ScalarType));

        file.close();

        return matrix;
    }
};

#endif //PCSC_PROJECT_PREADFILES_H