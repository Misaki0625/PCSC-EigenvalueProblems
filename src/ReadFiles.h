//
// Created by suo on 05.12.22.
//
//#ifndef READFILES_H
//#define READFILES_H

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>

// Base class for file readers
class FileReader {
public:
    virtual Eigen::MatrixXd read(const std::string& filename) = 0;
};

// CSV file reader class
class CSVReader : public FileReader {
public:
    Eigen::MatrixXd read(const std::string& filename) override {
        std::ifstream file(filename);
        Eigen::MatrixXd matrix;
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
            std::vector<double> values;
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
            matrix.row(matrix.rows() - 1) = Eigen::Map<Eigen::RowVectorXd>(values.data(), values.size());
        }

        // Close file
        file.close();

        // Print matrix
        std::cout << matrix << std::endl;

        return matrix;
    }
};

// TXT file reader class
class BinaryReader : public FileReader {
public:
    Eigen::MatrixXd read(const std::string &filename) override {
        Eigen::MatrixXd matrix;
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << "!" << std::endl;
            return {};
        }
        int num_elems = 0;
        double elem;
        while (file.read((char *) &elem, sizeof(double))) {
            num_elems++;
        }
        int rows = (int) sqrt(num_elems);
        int cols = num_elems / rows;
        matrix.resize(rows, cols);
        file.clear();
        file.seekg(0, std::ios::beg);
        file.read((char *) matrix.data(), rows * cols * sizeof(double));

        // Close file
        file.close();

        // Print matrix
        std::cout << matrix << std::endl;

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