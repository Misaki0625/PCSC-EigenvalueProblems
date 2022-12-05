//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_QRMETHOD_H
#define PCSC_PROJECT_QRMETHOD_H

#endif //PCSC_PROJECT_QRMETHOD_H

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Base class for eigenvalue solvers
class EigenvalueSolver
{
public:
    virtual VectorXcd computeEigenvalues(const MatrixXcd& A) = 0;
};

// QR method eigenvalue solver
class QRSolver : public EigenvalueSolver
{
public:
    VectorXcd computeEigenvalues(const MatrixXcd& A)
    {
        // Initialize variables
        MatrixXcd Q = MatrixXcd::Identity(A.rows(), A.cols());
        MatrixXcd R = A;
        int n = A.rows();

        // QR decomposition
        for (int i = 0; i < n-1; i++)
        {
            // Compute Householder reflection
            VectorXcd x = R.col(i).tail(n-i);
            VectorXcd e = VectorXcd::Unit(n-i, 0);
            VectorXcd v = x + x.norm() * e;
            MatrixXcd H = MatrixXcd::Identity(n-i, n-i) - (2.0 / v.dot(v)) * v * v.conjugate().transpose();

            // Apply Householder reflection to R
            R.block(i, i, n-i, n-i) = H * R.block(i, i, n-i, n-i);

            // Apply Householder reflection to Q
            Q.block(i, i, n-i, n-i) = Q.block(i, i, n-i, n-i) * H.conjugate().transpose();
        }

        // Return eigenvalues of R
        return R.diagonal();
    }
};

//// Power method eigenvalue solver
//class PowerSolver : public EigenvalueSolver
//{
//public:
//    VectorXcd computeEigenvalues(const MatrixXcd& A)
//    {
//        // Initialize variables
//        int n = A.rows();
//        VectorXcd x = VectorXcd::Random(n);
//        VectorXcd y;
//
//        // Iterate until convergence
//        while (true)
//        {
//            y = A * x;
//            x = y / y.norm();
//
//            // Check for convergence
//            if ((x - y).norm() < 1e-6)
//                break;
//        }
//
//        // Return dominant eigenvalue
//        return x.dot(A * x) / x.dot(x);
//    }
//};
//
//// Inverse power method eigenvalue solver
//class InversePowerSolver : public EigenvalueSolver
//{
//public:
//    VectorXcd computeEigenvalues(const MatrixXcd& A)
//    {
//        // Initialize variables
//        int n = A.rows();
//        MatrixXcd B = A.inverse();
//        VectorXcd x = VectorXcd::Random(n);
//
//        VectorXcd y;
//        // Iterate until convergence
//        while (true)
//        {
//            y = B * x;
//            x = y / y.norm();
//
//            // Check for convergence
//            if ((x - y).norm() < 1e-6)
//                break;
//        }
//
//// Return dominant eigenvalue of A^-1
//        return x.dot(B * x) / x.dot(x);
//    }
//};
//
//// Power method with shift eigenvalue solver
//class PowerShiftSolver : public EigenvalueSolver
//{
//public:
//    PowerShiftSolver(complex<double> shift) : mShift(shift) {}
//
//    VectorXcd computeEigenvalues(const MatrixXcd& A)
//    {
//// Initialize variables
//        int n = A.rows();
//        MatrixXcd B = A - mShift * MatrixXcd::Identity(n, n);
//        VectorXcd x = VectorXcd::Random(n);
//        VectorXcd y;
//        // Iterate until convergence
//        while (true)
//        {
//            y = B * x;
//            x = y / y.norm();
//
//            // Check for convergence
//            if ((x - y).norm() < 1e-6)
//                break;
//        }
//
//// Return dominant eigenvalue of A - shift*I
//        return x.dot(B * x) / x.dot(x) + mShift;
//    }
//
//private:
//    complex<double> mShift;
//};
//
//// Inverse power method using inheritance
//class InversePowerInheritanceSolver : public PowerShiftSolver
//{
//public:
//    InversePowerInheritanceSolver() : PowerShiftSolver(0.0) {}
//
//    VectorXcd computeEigenvalues(const MatrixXcd& A)
//    {
//// Compute eigenvalues of A^-1 using power method with shift
//        MatrixXcd B = A.inverse();
//        return PowerShiftSolver::computeEigenvalues(B);
//    }
//};





