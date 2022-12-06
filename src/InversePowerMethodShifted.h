//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H
#define PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H

#endif //PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H
#include <Eigen/Dense>
#include <iostream>
//#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

// Inverse power method with shift for calculating eigenvalues
class InversePowerMethodWithShift : public GeneralEigenMethod {
public:
    InversePowerMethodWithShift(double MaxIter, double height) : MaxIter_(MaxIter), height_(height) {}
    ~InversePowerMethodWithShift() override = default;

    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        return {};
    }
private:
    double MaxIter_;
    double height_;
};