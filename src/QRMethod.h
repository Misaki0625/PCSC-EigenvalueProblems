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

/**
 * QRMethod is the implementation of QR method to compute all eigenvalues of a square matrix at once.
 * This class inherits from AllEigenMethod and overwrites the calculateEigenvalues function. This algorithm
 * is applicable for both double and complex matrix.
 */
template <typename ScalarType>
class QRMethod : public AllEigenMethod<ScalarType> {
public:

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;

    /**
    * Constructor and destructor.
    */
    QRMethod(int MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~QRMethod() override = default;

    /**
     * calculateEigenvalue function is not implemented.
     */
    ScalarType calculateEigenvalue(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }

    /**
     * calculateEigenvalues function is implemented to compute all eigenvalues.
     * Normally, it uses QR decomposition and reconstruct the matrix as RxQ, then iteratively compute the new eigenvalues.
     */
    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        // Initialize variables
        VectorType eigenvalues;
        MatrixType A = matrix;

        // Perform QR algorithm
        for (int i = 0; i < MaxIter_; i++)
        {
            // Perform QR decomposition
            Eigen::HouseholderQR<MatrixType> qr(A);
            MatrixType Q = qr.householderQ();
            MatrixType R = qr.matrixQR().template triangularView<Eigen::Upper>();
        }

        // Extract eigenvalues from diagonal of A
        eigenvalues = A.diagonal();

        // Sort in descending order
        std::sort(eigenvalues.data(), eigenvalues.data() + eigenvalues.size(),
                  [](ScalarType a, ScalarType b) { return std::abs(a) > std::abs(b); });

        return eigenvalues;
    }
private:
    double MaxIter_;
    double tol_;
};

#endif //PCSC_PROJECT_QRMETHOD_H





