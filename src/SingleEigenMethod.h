//
// Created by suo on 08.12.22.
//

#ifndef MAIN_CPP_SINGLEEIGENMETHOD_H
#define MAIN_CPP_SINGLEEIGENMETHOD_H

#include <Eigen/Dense>
#include <iostream>
#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

// Inverse power method for calculating eigenvalues
template <typename ScalarType>
class SingleEigenMethod : public GeneralEigenMethod<ScalarType>{
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:
    SingleEigenMethod() = default;

    virtual ~SingleEigenMethod() = default;

    virtual ScalarType calculateEigenvalue(const MatrixType &matrix) = 0;
};

#endif //MAIN_CPP_SINGLEEIGENMETHOD_H
