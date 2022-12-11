//
// Created by suo on 07.12.22.
//

#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <cstdio>
#include <exception>
#include <algorithm>
#include <type_traits>
#include "PowerMethod.h"

using namespace std;
using namespace Eigen;
template <typename MatrixType>
typename MatrixType::Scalar PowerMethod1(const MatrixType& matrix) {
    // Define a vector to store the current approximation of the eigenvector
    Eigen::VectorXd x = Eigen::VectorXd::Random(matrix.cols());

    // Define a variable to store the current approximation of the eigenvalue
    typename MatrixType::Scalar lambda = 0;
    // Iterate until convergence
    while (true) {
        // Compute the next approximation of the eigenvector
        Eigen::VectorXd xNext = matrix * x;

        // Compute the next approximation of the eigenvalue
        lambda = xNext.dot(x) / x.dot(x);

        // Check for convergence
        if (xNext.isApprox(lambda * x)) {
            // Return the largest eigenvalue
            return lambda;
        }

        // Update the current approximation of the eigenvector
        x = xNext;
    }
}

#include <Eigen/Dense>
#include <iostream>

// Define a template function that uses the QR method iteratively to compute the eigenvalues of a matrix
template <typename MatrixType>
Eigen::VectorXcd QRMethod(const MatrixType& matrix)
{
    // Define a variable to store the current approximation of the matrix
    MatrixType A = matrix;

    // Iterate until convergence
    for (int i=0; i<1000;i++)
    {
        // Compute the QR decomposition of the current approximation of the matrix
//        Eigen::HouseholderQR<MatrixType> qr(A);
//        MatrixType Q = qr.householderQ();
//        MatrixType R = qr.matrixQR().template triangularView<Eigen::Upper>();
//
//        // Compute the next approximation of the matrix
//        A = R * Q;
        MatrixType Q = Eigen::HouseholderQR<MatrixType>(A).householderQ();
        A = Q.transpose() * A * Q;

    }
    auto eigenvalues = A.diagonal();
    return eigenvalues;
}


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

template <typename T>
T from_string(const std::string& str)
{
    T result;
    try
    {
        result = std::stod(str);
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    return result;
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


    // Print the largest eigenvalue to the console
    // std::cout << "Largest eigenvalue: " << maxEigenvalue << std::endl;

// Define a 3x3 matrix
    // Define a 3x3 matrix
    Eigen::MatrixXd m(5,5);
    m << 1.87,0.19,-1.22,2.03,-1.11,
    1.17,-10.71,2.23,32.1,-9.23,
    5.23,2.32,1.09,-8.35,2.90,
    0.87,2.34,-10.82,-3.45,0,
    9.12,-3.53,-2.34,6.34,1.57;

    cout << m << endl;

    //complex eigenpower = PowerMethod1(m);
    //cout << "power: " << eigenpower << endl;

    // Compute the eigenvalues of the matrix using the QR method
    Eigen::VectorXcd eigenvalues = QRMethod(m);

    // Print the eigenvalues to the console
    std::cout << "Eigenvalues: " << eigenvalues << std::endl;

    Eigen::EigenSolver<MatrixXd> solver(m);
    cout << solver.eigenvalues() << endl;

    cout << "real" << m.eigenvalues() << endl;

    std::string str = "3.14";
    auto d = from_string<double>(str);
    std::cout << d << std::endl;

    str = "3.14+4.13i";

    std::complex<double> aa(1.0, 2.0);
    std::complex<double> bb(3.0, 4.0);

// Use the * operator to perform multiplication
    std::complex<double> cc = aa - bb;
    std::complex<double> ee = 1;

// Use std::abs to compute the absolute value
    auto dd = std::abs(cc - aa);
    double tol_ = 0;

    if (abs(ee - aa) > tol_)
    {
        cout << "no" << endl;
    }

    cout << dd << endl;

    // Define a string representing a complex number
    std::string str1 = "(2.5, 1)";

    // Parse the real and imaginary parts of the number
    double real, imag;
    std::sscanf(str1.c_str(), "(%lf, %lf)", &real, &imag);

    // Create a std::complex<double> value from the parsed parts
    std::complex<double> z(real, imag);

    // Print the complex number to the console
    std::cout << "z = " << z << std::endl;


    return 0;
}