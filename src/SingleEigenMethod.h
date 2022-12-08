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
class SingleEigenMethod : public GeneralEigenMethod {
public:
    SingleEigenMethod() = default;

    virtual ~SingleEigenMethod() = default;

    virtual double calculateEigenvalue(const MatrixXd &matrix) = 0;
};

#endif //MAIN_CPP_SINGLEEIGENMETHOD_H
