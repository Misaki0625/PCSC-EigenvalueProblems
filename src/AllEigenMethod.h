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
class AllEigenMethod : public GeneralEigenMethod {
public:
    AllEigenMethod() = default;
    virtual ~AllEigenMethod() = default;

    virtual VectorXd calculateEigenvalues(const MatrixXd &matrix) = 0;
};

#endif //MAIN_CPP_ALLEIGENMETHOD_H
