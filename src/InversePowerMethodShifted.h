//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H
#define PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H

#include <Eigen/Dense>
#include <iostream>
#include "SingleEigenMethod.h"
using namespace std;
using namespace Eigen;

// Inverse power method with shift for calculating eigenvalues
class InversePowerMethodWithShift : public SingleEigenMethod {
public:
    InversePowerMethodWithShift(double MaxIter, double tol, const std::string& shift) : MaxIter_(MaxIter), tol_(tol), shift_(shift) {}
    ~InversePowerMethodWithShift() override = default;

    Eigen::VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        return {};
    }
    double calculateEigenvalue(const MatrixXd& matrix) override {
        // VectorXd eigenvalues;
        MatrixXd A = matrix;
        double shift;

        if (shift_ == "default"){
            shift = computeShift(A);
        } else{
            shift = stod(shift_);
        }

        int n = A.rows();
        // Initialize the eigenvector with random values
        VectorXd x = VectorXd::Random(n);

        Eigen::MatrixXd inv = (A - shift * Eigen::MatrixXd::Identity(A.rows(), A.cols())).inverse();

        // Initialize the eigenvalue to zero
        double lambda = 0;

        // Iterate until convergence or max iterations reached
        for (int i = 0; i < MaxIter_; i++)
        {
            // Compute the shifted matrix and the next approximation
            // of the eigenvector
//            Eigen::MatrixXd inv = (A - shift * Eigen::MatrixXd::Identity(A.rows(), A.cols())).inverse();
            x = inv * x;

            // x = (B - lambda * Eigen::MatrixXd::Identity(B.rows(), B.cols())).inverse() * x;

//            x = B.lu().solve(x);

            // Compute the matrix-vector product Ax
            // VectorXd Ax = A * x;
            //VectorXd Ax = A * x - shift * x;

            x.normalize();

            // Compute the eigenvalue as the maximum value of the vector
            // double newLambda = x.transpose() * Ax;
            // double newLambda = x.dot(A * x) / x.dot(x);
            double newLambda = x.transpose() * A * x;

            // Check for convergence
            if (abs(newLambda - lambda) < tol_)
            {
                break;
            }
            // x = Ax / Ax.norm();
            lambda = newLambda;
        }

        cout << lambda << endl;
        return lambda;
    }
private:
    double MaxIter_;
    double tol_;
    const std::string shift_;
    static double computeShift(const MatrixXd& matrix)
    {
        // Compute the average of the diagonal elements of A
        // as an initial estimate of the shift
        double shift = matrix.diagonal().mean();
        return shift;
    }
};

#endif //PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H