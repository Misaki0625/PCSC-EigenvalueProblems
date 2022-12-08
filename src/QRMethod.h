//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_QRMETHOD_H
#define PCSC_PROJECT_QRMETHOD_H

#include <iostream>
#include <Eigen/Dense>
#include "AllEigenMethod.h"
using namespace std;
using namespace Eigen;

// QR method for calculating eigenvalues
class QRMethod : public AllEigenMethod {
public:
    QRMethod(double MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~QRMethod() override = default;

    double calculateEigenvalue(const MatrixXd& matrix) override {
        return {};
    }
    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        // Initialize variables
        VectorXd eigenvalues;
        MatrixXd A = matrix;
        // int n = matrix.rows();

        // Perform QR algorithm
        for (int i = 0; i < MaxIter_; i++)
        {
            // Perform QR decomposition
            HouseholderQR<MatrixXd> qr(A);
            MatrixXd Q = qr.householderQ();
            MatrixXd R = qr.matrixQR().triangularView<Upper>();
            // Update matrix
            A = R * Q;

            // check for convergence
            //if ((A - MatrixXd(A.diagonal().asDiagonal())).norm() < tol_)
            // actually this is never converged for some cases. even with 10000 iterations
            if(A.cwiseAbs().maxCoeff() < tol_)
            {
                // print the result
                cout << "converged at iteration " << i << endl;
                cout << "eigenvalues =" << endl << A.diagonal().transpose() << endl;
                break;
            }
        }


        // Extract eigenvalues from diagonal of A
        eigenvalues = A.diagonal();

        // in descending order using a lambda function
        std::sort(eigenvalues.data(), eigenvalues.data() + eigenvalues.size(),
                  [](double a, double b) { return std::abs(a) > std::abs(b); });

        return eigenvalues;
    }
private:
    double MaxIter_;
    double tol_;
};

#endif //PCSC_PROJECT_QRMETHOD_H





