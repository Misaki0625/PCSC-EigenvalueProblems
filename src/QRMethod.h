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
template <typename ScalarType>
class QRMethod : public AllEigenMethod<ScalarType> {
public:
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
    QRMethod(int MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~QRMethod() override = default;

    ScalarType calculateEigenvalue(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }
    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        // Initialize variables
        VectorType eigenvalues;
        MatrixType A = matrix;
        // int n = matrix.rows();

        // Perform QR algorithm
        for (int i = 0; i < MaxIter_; i++)
        {
            // Perform QR decomposition
            Eigen::HouseholderQR<MatrixType> qr(A);
            MatrixType Q = qr.householderQ();
            MatrixType R = qr.matrixQR().template triangularView<Eigen::Upper>();
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
                  [](ScalarType a, ScalarType b) { return std::abs(a) > std::abs(b); });

        return eigenvalues;
    }
private:
    double MaxIter_;
    double tol_;
};

#endif //PCSC_PROJECT_QRMETHOD_H





