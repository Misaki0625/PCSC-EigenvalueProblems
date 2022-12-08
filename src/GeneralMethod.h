//
// Created by suo on 06.12.22.
//

#ifndef PCSC_PROJECT_GENERALMETHOD_H
#define PCSC_PROJECT_GENERALMETHOD_H

#include <Eigen/Dense>
#include <iostream>
using namespace std;
using namespace Eigen;

class GeneralEigenMethod {
public:
    // Calculate the eigenvalues of a given matrix
    GeneralEigenMethod() = default;
    virtual ~GeneralEigenMethod() = default;

    virtual VectorXd calculateEigenvalues(const MatrixXd& matrix) = 0;
    virtual double calculateEigenvalue(const MatrixXd& matrix) = 0;
};

#endif //PCSC_PROJECT_GENERALMETHOD_H