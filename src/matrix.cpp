//
// Created by suo on 07.12.22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <exception>
#include <algorithm>
#include "PowerMethod.h"

using namespace std;
using namespace Eigen;

MatrixXd randInit(const MatrixXd& mat){
    // Number of vectors in the input matrix
    int n = mat.cols();

    // create a randomly initialized matrix
    MatrixXd A = MatrixXd::Random(n, n);

    // Make the matrix invertible by adding a multiple of one row to another
    A.row(1) += 2 * A.row(0);

    // Check if the matrix is invertible; normally it should be invertible
    if (A.determinant() != 0)
    {
        // cout << "The matrix is invertible" << endl;
        return A;
    }
    else
    {
        cout << "The matrix is not invertible" << endl;
        cout << "please try again!" << endl;
        return {}; // to modify or to terminate the program
    }
}

MatrixXd orthogonalize(const MatrixXd& mat) {
    // Number of vectors in the input matrix
    int n = mat.cols();

    // Result matrix of orthogonal vectors
    MatrixXd orth = MatrixXd::Zero(mat.rows(), n);

    // First vector is the same as the first input vector
    orth.col(0) = mat.col(0);

    // Orthogonalize the remaining vectors
    for (int i = 1; i < n; ++i) {
        orth.col(i) = mat.col(i);
        for (int j = 0; j < i; ++j) {
            // Subtract the projection of the current vector onto the previous vectors
            orth.col(i) -= orth.col(i).dot(orth.col(j)) / orth.col(j).squaredNorm() * orth.col(j);
        }
    }
    return orth;
}

int main(){
    MatrixXd a(3,3);
    MatrixXd A =  randInit(a);

    // Invert the matrix
    MatrixXd Ainv = A.inverse();

    // Print the inverted matrix
    cout << "The inverted matrix is: " << endl << Ainv << endl;

    auto B = orthogonalize(A);
    if (B.determinant() != 0)
    {
        cout << "The matrix is invertible" << endl;
    }
    else
    {
        cout << "The matrix is not invertible" << endl;
    }
    cout << B << endl;

    auto C = orthogonalize(B);
    if (C.determinant() != 0)
    {
        cout << "The matrix is invertible" << endl;
    }
    else
    {
        cout << "The matrix is not invertible" << endl;
    }
    cout << C << endl;

    VectorXd maxVals = C.colwise().maxCoeff();
    cout << maxVals << endl;

    MatrixXd b(3,3);
    b << 1,1,1,
    2,2,2,
    3,3,3;

    if (abs(b.determinant()) > 1e-5)
    {
        cout << "The matrix is invertible" << endl;
    }
    else
    {
        cout << "The matrix is not invertible" << endl;
    }
    //test power method
    HouseholderQR<MatrixXd> qr(b);
    MatrixXd v = qr.householderQ();

    MatrixXd rq = v.transpose() * b * v;
    cout << "v/q" << v << endl;
    cout << "rq" << rq << endl;
    //test qr method
    MatrixXd r = qr.matrixQR().triangularView<Upper>();
    MatrixXd A_ = r * v;
    cout << "r" << r << endl;
    cout << "A" << A_ << endl;

    cout << b.eigenvalues() << endl;

    Eigen::Matrix3d m;
    m << 1, 0, 0,
            0, 1, 0,
            0, 0, 1;

    // Create a SelfAdjointEigenSolver object
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> solver;

    // Compute the eigenvalues and eigenvectors of the matrix
    solver.compute(m);

    // Print the eigenvalues to the console
    std::cout << "Eigenvalues: " << solver.eigenvalues().transpose() << std::endl;

    // Find the largest eigenvalue
    double maxEigenvalue = solver.eigenvalues().maxCoeff();

    // Print the largest eigenvalue to the console
    std::cout << "Largest eigenvalue: " << maxEigenvalue << std::endl;

    return 0;
}