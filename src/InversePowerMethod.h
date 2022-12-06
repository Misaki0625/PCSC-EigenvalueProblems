//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_INVERSEPOWERMETHOD_H
#define PCSC_PROJECT_INVERSEPOWERMETHOD_H

#endif //PCSC_PROJECT_INVERSEPOWERMETHOD_H
#include <Eigen/Dense>
#include <iostream>
//#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

// Inverse power method for calculating eigenvalues
class InversePowerMethod : public GeneralEigenMethod {
public:
    InversePowerMethod(double MaxIter, double height) : MaxIter_(MaxIter), height_(height) {}
    ~InversePowerMethod() override = default;

    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        return {};
    }
private:
    double MaxIter_;
    double height_;
};