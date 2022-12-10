//
// Created by suo on 06.12.22.
//

#ifndef PCSC_PROJECT_GENERALMETHOD_H
#define PCSC_PROJECT_GENERALMETHOD_H

#include <Eigen/Dense>
#include <iostream>
using namespace std;
using namespace Eigen;

template <typename ScalarType>
class GeneralEigenMethod {
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:
    // Calculate the eigenvalues of a given matrix
    GeneralEigenMethod() = default;
    virtual ~GeneralEigenMethod() = default;

    virtual VectorType calculateEigenvalues(const MatrixType& matrix) = 0;
    virtual ScalarType calculateEigenvalue(const MatrixType& matrix) = 0;
};

#endif //PCSC_PROJECT_GENERALMETHOD_H