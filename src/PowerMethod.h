//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_POWERMETHOD_H
#define PCSC_PROJECT_POWERMETHOD_H

#endif //PCSC_PROJECT_POWERMETHOD_H

#include <Eigen/Dense>
#include <iostream>
#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

class PowerMethod : public GeneralEigenMethod {
public:
    PowerMethod(double MaxIter, double height) : MaxIter_(MaxIter), height_(height) {}
    ~PowerMethod() override {}

    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        VectorXd v(3);
        v << 1, 2, 3;
        return v;
    }

private:
    double MaxIter_;
    double height_;
};
