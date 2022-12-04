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
        std::string line;

        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << filename << "!" << std::endl;
            return Eigen::MatrixXd();
        }

        // Read the first line to get the dimensions of the matrix
        std::getline(file, line);
        int rows = std::count(line.begin(), line.end(), ',') + 1;
        int cols = 0;
        while (std::getline(file, line)) {
            cols++;
        }

        // Resize the matrix and read the file again
        Eigen::MatrixXd matrix(rows, cols);
        file.clear();
        file.seekg(0, std::ios::beg);
        std::getline(file, line); // skip the first line
        int row = 0;
        while (std::getline(file, line)) {
            int col = 0;
            std::string value;
            std::stringstream ss(line);
            while (std::getline(ss, value, ',')) {
                matrix(row, col) = std::stod(value);
                col++;
            }
            row++;
        }

        return matrix;
    }
};

// TXT file reader class
class TXTReader : public FileReader {
public:
    Eigen::MatrixXd read(const std::string& filename) override {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << "!" << std::endl;
            //return Eigen::MatrixXd();
        }
        // Read data into matrix
        Eigen::MatrixXd matrix;
        std::string line;
        while (std::getline(file, line)) {
            // Parse line
            std::stringstream lineStream(line);
            std::string cell;
            std::vector<double> values;
            while (std::getline(lineStream, cell, ',')) {
                values.push_back(std::stod(cell));
            }
            // Add row to matrix
            if (matrix.rows() == 0) {
                matrix.resize(1, values.size());
            } else {
                matrix.conservativeResize(matrix.rows() + 1, Eigen::NoChange);
            }
            matrix.row(matrix.rows() - 1) = Eigen::Map<Eigen::RowVectorXd>(values.data(), values.size());
        }

        // Close file
        file.close();

        // Return matrix
        return matrix;
    }
//        std::ifstream file(filename);
//        std::string line;
//
//        // Read the first line to get the dimensions of the matrix
//        std::getline(file, line);
//        int rows = std::count(line.begin(), line.end(), ' ') + 1;
//        int cols = 0;
//        while (std::getline(file, line)) {
//            cols++;
//        }
//
//        // Resize the matrix and read the file again
//        Eigen::MatrixXd matrix(rows, cols);
//        file.clear();
//        file.seekg(0, std::ios::beg);
//        std::getline(file, line); // skip the first line
//        int row = 0;
//        while (std::getline(file, line)) {
//            int col = 0;
//            std::string value;
//            std::stringstream ss(line);
//            while (std::getline(ss, value, ' ')) {
//                matrix(row, col) = std::stod(value);
//                col++;
//            }
//            row++;
//        }
//
//        return matrix;
//    }
};