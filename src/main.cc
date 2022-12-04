#include "pcsc.hh"
#include "ReadFiles.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <exception>

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

Eigen::MatrixXd abc(std::string file, int rows, int cols) {

    std::ifstream in(file);

    std::string line;

    int row = 0;
    int col = 0;

    Eigen::MatrixXd res = Eigen::MatrixXd(rows, cols);

    if (in.is_open()) {

        while (std::getline(in, line)) {

            char *ptr = (char *) line.c_str();
            int len = line.length();

            col = 0;

            char *start = ptr;
            for (int i = 0; i < len; i++) {

                if (ptr[i] == ',') {
                    res(row, col++) = atof(start);
                    start = ptr + i + 1;
                }
            }
            res(row, col) = atof(start);

            row++;
        }

        in.close();
    }
    return res;
}

int main(int argc, char **argv) {
    //Eigen::Matrix<float, 4, 4> m;
    int row = 2;
    int col = 2;
    ReadFiles::CSVReader read(matrix2.csv);
    int n = 2;
    //auto m = createDoubleMatrix(n);
    std::cout << "nb_rows: " << m.rows() << std::endl;
    std::cout << "nb_cols: " << m.cols() << std::endl;
    std::cout << "size: " << m.size() << std::endl;
    std::cout << "m = " << m << std::endl;
    std::cout << "m.T = " << m.transpose() << std::endl;


}
