//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_UNILS_H
#define PCSC_PROJECT_UNILS_H

#endif //PCSC_PROJECT_UNILS_H

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <cmath>

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

Eigen::MatrixXcd createDoubleMatrix2(int n) {
    Eigen::MatrixXcd Q(n,n);
    Q.setRandom();
    Q = Eigen::HouseholderQR<Eigen::MatrixXcd>(Q).householderQ();

    Eigen::MatrixXcd A(n,n);
    A.setZero();
    A.diagonal() = Eigen::VectorXcd::LinSpaced(n, 1, n);
    A = Q*A*Q.transpose();
    return A;
}
