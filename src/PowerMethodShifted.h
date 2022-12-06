//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_POWERMETHODSHIFTED_H
#define PCSC_PROJECT_POWERMETHODSHIFTED_H

#endif //PCSC_PROJECT_POWERMETHODSHIFTED_H

#include <Eigen/Dense>
#include <iostream>
//#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

class PowerMethodWithShift : public GeneralEigenMethod {
public:
    PowerMethodWithShift(double MaxIter, double height) : MaxIter_(MaxIter), height_(height) {}
    ~PowerMethodWithShift() override = default;

    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        return {};
    }
private:
    double MaxIter_;
    double height_;
};