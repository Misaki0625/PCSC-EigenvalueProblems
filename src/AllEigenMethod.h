//
// Created by suo on 08.12.22.
//

#ifndef MAIN_CPP_ALLEIGENMETHOD_H
#define MAIN_CPP_ALLEIGENMETHOD_H

#include <Eigen/Dense>
#include <iostream>
#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

// Inverse power method for calculating eigenvalues
template <typename ScalarType>
class AllEigenMethod : public GeneralEigenMethod<ScalarType> {
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:
    AllEigenMethod() = default;
    virtual ~AllEigenMethod() = default;

    virtual VectorType calculateEigenvalues(const MatrixType& matrix) = 0;
};

#endif //MAIN_CPP_ALLEIGENMETHOD_H
