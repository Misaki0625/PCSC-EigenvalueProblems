//
// Created by suo on 08.12.22.
//

#ifndef MAIN_CPP_POWERMETHODALL_H
#define MAIN_CPP_POWERMETHODALL_H

#include <Eigen/Dense>
#include <iostream>
#include "AllEigenMethod.h"
using namespace std;
using namespace Eigen;

template <typename ScalarType>
class PowerMethodAll : public AllEigenMethod<ScalarType> {
public:
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
    PowerMethodAll(int MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~PowerMethodAll() override = default;

    ScalarType calculateEigenvalue(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }
    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        VectorType eigenvalues;
        MatrixType A = matrix;
        MatrixType rq;

        int n = A.rows();
        // Initialize the eigenvector with random values
        // VectorXd x = VectorXd::Random(n);
        if (abs(A.determinant()) < 1e-5) {
            // cout << "Input matrix is not linearly independent" << endl;
            // return lambda;
            throw std::invalid_argument("Input matrix for this algorithm must be linearly independent");
        }
        MatrixType m = randInit(n);

        // Gram-Schmidt process to orthonormalize this set m and generate a matrix v
        MatrixType v = gramSchmidt(m);
        // cout << v << endl;

        // Iterate until convergence or max iterations reached
        for (int i = 0; i < MaxIter_; i++)
        {
            // Compute the matrix-vector product Ax
            MatrixType Ax = A * v;

//            // Compute the eigenvalue as the maximum value of the vector
//            eigenvalues = Ax.colwise().maxCoeff();

            // Update v using the Gram-Schmidt process
            v = gramSchmidt(Ax);
//            HouseholderQR<MatrixXd> qr(Ax);
//            v = qr.householderQ();

            rq = v.transpose() * A * v;

            // cout << v << endl;
        }

        //cout << eigenvalues << endl;
        eigenvalues = rq.diagonal();
        // in descending order using a lambda function
        std::sort(eigenvalues.data(), eigenvalues.data() + eigenvalues.size(),
                  [](ScalarType a, ScalarType b) { return std::abs(a) > std::abs(b); });

        return eigenvalues;
    }

private:
    double MaxIter_;
    double tol_;
    MatrixType randInit(int n){
        // create a randomly initialized matrix
        MatrixType A = MatrixType::Random(n, n);

//        // Make the matrix invertible by adding a multiple of one row to another
//        A.row(1) += 2 * A.row(0);

        // Check if the matrix is invertible; normally it should be invertible
        for (int i = 0; true; i++)
            if (abs(A.determinant()) > 1e-5) //
            {
                // cout << "The matrix is invertible" << endl;
                return A;
            }
    }
    MatrixType gramSchmidt(const MatrixType& mat) {
        // Number of vectors in the input matrix
        int m = mat.rows();
        int n = mat.cols();

        // Result matrix of orthogonal vectors
        MatrixType orth = MatrixType::Zero(m, n);

        // First vector is the same as the first input vector
        orth.col(0) = mat.col(0);
        for (int i = 0; i < n; i++)
        {
            VectorType v = mat.col(i);
            for (int j = 0; j < i; j++)
            {
                v -= orth.col(j).dot(mat.col(i)) * orth.col(j);
            }
            orth.col(i) = v.normalized();
        }
        return orth;
    }
};

#endif //MAIN_CPP_POWERMETHODALL_H
