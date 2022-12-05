
// Created by suo on 05.12.22.

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <exception>

#include "ReadFiles.h"
#define MAXBUFSIZE  ((int) 1e6)

using namespace std;

Eigen::MatrixXd createDoubleMatrix(int n) {
    Eigen::MatrixXd Q(n,n);
    Q.setRandom();
    Q = Eigen::HouseholderQR<Eigen::MatrixXd>(Q).householderQ();

    Eigen::MatrixXd A(n,n);
    A.setZero();
    A.diagonal() = Eigen::VectorXd::LinSpaced(n, 1, n);
    A = Q*A*Q.transpose();
    return A;
}


int main(int argc, char **argv) {
    int row = 2;
    int col = 2;
//    CSVReader reader;
//    auto m = reader.read("/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/src/matrix.csv");
    //std::cout << m << std::endl;
    int n = 3;
    auto m = createDoubleMatrix(n);
    std::cout << "nb_rows: " << m.rows() << std::endl;
    std::cout << "nb_cols: " << m.cols() << std::endl;
    std::cout << "size: " << m.size() << std::endl;
    std::cout << "m = " << m << std::endl;
    std::cout << "m.T = " << m.transpose() << std::endl;
}

//#include <Eigen/Core>
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//
//int main()
//{
//    // Open file
//    std::ifstream file("/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/src/matrix.csv");
//    if (!file.is_open())
//    {
//        std::cerr << "Error: Could not open file!" << std::endl;
//        return 1;
//    }
//
////    // Read data into matrix
//    Eigen::MatrixXd matrix;
//    std::string line;
//    while (std::getline(file, line))
//    {
//        // Parse line
//        std::stringstream lineStream(line);
//        std::string cell;
//        std::vector<double> values;
//        while (std::getline(lineStream, cell, ','))
//        {
//            values.push_back(std::stod(cell));
//        }
//
//        // Add row to matrix
//        if (matrix.rows() == 0)
//        {
//            matrix.resize(1, values.size());
//        }
//        else
//        {
//            matrix.conservativeResize(matrix.rows() + 1, Eigen::NoChange);
//        }
//        matrix.row(matrix.rows() - 1) = Eigen::Map<Eigen::RowVectorXd>(values.data(), values.size());
//    }
//
//    // Close file
//    file.close();
//
//    // Print matrix
//    std::cout << matrix << std::endl;
//
//    return 0;
//}


