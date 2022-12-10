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

// Base class for file readers
template <typename ScalarType>
class FileReader {
public:
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;

    FileReader() = default;
    virtual ~FileReader() = default;

    virtual MatrixType read(const std::string& filename) = 0;
};

// CSV file reader class
template <typename ScalarType>
class CSVReader : public FileReader<ScalarType> {
public:
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using RowVectorType = Eigen::RowVector<ScalarType, -1>;

    CSVReader() = default;
    ~CSVReader() override = default;

    MatrixType read(const std::string& filename) override {
        std::ifstream file(filename);
        MatrixType matrix;
        std::string line;

        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << filename << "!" << std::endl;
            return {};
        }

        while (std::getline(file, line))
        {
            // Parse line
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<ScalarType> values;
            while (std::getline(lineStream, cell, ','))
            {
                values.push_back(std::stod(cell));
            }

            // Add row to matrix
            if (matrix.rows() == 0)
            {
                matrix.resize(1, values.size());
            }
            else
            {
                matrix.conservativeResize(matrix.rows() + 1, Eigen::NoChange);
            }
            matrix.row(matrix.rows() - 1) = Eigen::Map<RowVectorType>(values.data(), values.size());
        }

        // Close file
        file.close();

        // Print matrix
        // std::cout << matrix << std::endl;

        return matrix;
    }
};

// Binary file reader class
template <typename ScalarType>
class BinaryReader : public FileReader<ScalarType> {
public:
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    // using VectorType = Eigen::Vector<ScalarType, -1>;

    BinaryReader() = default;
    ~BinaryReader() override = default;

    MatrixType read(const std::string &filename) override {
        MatrixType matrix;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << "!" << std::endl;
            return {}; // to modify
        }
        struct stat stat_buf{};
        int rc = stat(filename.c_str(), &stat_buf);
        if (rc!=0){
            std::cerr << "Error: Could not read the stat of " << filename << "!" << std::endl;
            return {};
        }
        auto num_elems = stat_buf.st_size / sizeof(ScalarType);

        // int num_elems = 0;
//        double elem;
//        while (file.read((char *) &elem, sizeof(double))) {
//            num_elems++;
//        }
        int rows = (int) sqrt(num_elems);
        int cols = num_elems / rows;
        matrix.resize(rows, cols);
        file.clear();
        file.seekg(0, std::ios::beg);
        file.read((char *) matrix.data(), rows * cols * sizeof(ScalarType));

        // Close file
        file.close();

        // Print matrix
        // std::cout << matrix << std::endl;

        // Return matrix
        return matrix;

    }
};
// write a matrix into a binary file
//    Eigen::MatrixXd a(3, 3);
//    a << 1, 2, 4,
//    4, 5, 6,
//    7, 8, 10;
//
//    // Write matrix to binary file
//    ofstream out("data.bin", ios::binary);
//    out.write((char*)a.data(), a.size()*sizeof(double));
//    out.close();

#endif //PCSC_PROJECT_PREADFILES_H