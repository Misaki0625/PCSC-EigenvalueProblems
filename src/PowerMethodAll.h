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

MatrixXd randInit(int n){
    // create a randomly initialized matrix
    MatrixXd A = MatrixXd::Random(n, n);

    // Make the matrix invertible by adding a multiple of one row to another
    A.row(1) += 2 * A.row(0);

    // Check if the matrix is invertible; normally it should be invertible
    if (abs(A.determinant()) > 1e-5) //
    {
        // cout << "The matrix is invertible" << endl;
        return A;
    } else{
        cout << "The matrix is not invertible" << endl;
        cout << "please try again!" << endl;
        return {}; // to modify or to terminate the program; loop to return valid matrix
    }
}

MatrixXd gramSchmidt(const MatrixXd& mat) {
    // Number of vectors in the input matrix
    int m = mat.rows();
    int n = mat.cols();

    // Result matrix of orthogonal vectors
    MatrixXd orth = MatrixXd::Zero(m, n);

    // First vector is the same as the first input vector
    orth.col(0) = mat.col(0);
    for (int i = 0; i < n; i++)
    {
        VectorXd v = mat.col(i);
        for (int j = 0; j < i; j++)
        {
            v -= orth.col(j).dot(mat.col(i)) * orth.col(j);
        }
        orth.col(i) = v.normalized();
    }
    return orth;
}

class PowerMethodAll : public AllEigenMethod {
public:
    PowerMethodAll(double MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~PowerMethodAll() override {}

    double calculateEigenvalue(const MatrixXd& matrix) override {
        return {};
    }
    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        VectorXd eigenvalues;
        MatrixXd A = matrix;
        MatrixXd rq;

        int n = A.rows();
        // Initialize the eigenvector with random values
        // VectorXd x = VectorXd::Random(n);
        MatrixXd m = randInit(n);

        // Gram-Schmidt process to orthonormalize this set m and generate a matrix v
        MatrixXd v = gramSchmidt(m);
        cout << v << endl;

        // Iterate until convergence or max iterations reached
        for (int i = 0; i < MaxIter_; i++)
        {
            // Compute the matrix-vector product Ax
            MatrixXd Ax = A * v;

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
                  [](double a, double b) { return std::abs(a) > std::abs(b); });

        return eigenvalues;
    }

private:
    double MaxIter_;
    double tol_;
};

#endif //MAIN_CPP_POWERMETHODALL_H
