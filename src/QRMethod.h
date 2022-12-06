//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_QRMETHOD_H
#define PCSC_PROJECT_QRMETHOD_H

#endif //PCSC_PROJECT_QRMETHOD_H

#include <iostream>
#include <Eigen/Dense>
//#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

// QR method for calculating eigenvalues
class QRMethod : public GeneralEigenMethod {
public:
    QRMethod(double MaxIter, double height) : MaxIter_(MaxIter), height_(height) {}
    ~QRMethod() override = default;

    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        return {};
    }
private:
    double MaxIter_;
    double height_;
};





