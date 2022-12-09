//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_POWERMETHODSHIFTED_H
#define PCSC_PROJECT_POWERMETHODSHIFTED_H

#include <Eigen/Dense>
#include <iostream>
#include "SingleEigenMethod.h"
using namespace std;
using namespace Eigen;

class PowerMethodWithShift : public SingleEigenMethod {
public:
    PowerMethodWithShift(double MaxIter, double tol, const std::string& shift) : MaxIter_(MaxIter), tol_(tol), shift_(shift) {}
    ~PowerMethodWithShift() override = default;

    Eigen::VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        throw std::logic_error("Method not implemented");
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

        // Initialize the eigenvalue to zero
        double lambda = 0;
        int i;

        Eigen::MatrixXd B = A - shift * Eigen::MatrixXd::Identity(A.rows(), A.cols());

        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
        {
            // Compute the next approximation of the eigenvector
            x = B.lu().solve(x);
            // x = B * x;
            x.normalize();

            // Compute the matrix-vector product Ax
            VectorXd Ax = A * x;

            // Compute the eigenvalue as the maximum value of the vector
            double newLambda = x.transpose() * Ax;
            // double newLambda = (A * x).norm() / x.norm();

            // Check for convergence
            if (abs(newLambda - lambda) < tol_)
            {
                break;
            }

            lambda = newLambda;
        }

        if (i == MaxIter_){
            throw std::runtime_error("Convergence not achieved");
        }
        return lambda;
    }
private:
    double MaxIter_;
    double tol_;
    const std::string& shift_;
    static double computeShift(const MatrixXd& matrix)
    {
        // Compute the average of the diagonal elements of A
        // as an initial estimate of the shift
        double shift = matrix.diagonal().mean();
        return shift;
    }
};

#endif //PCSC_PROJECT_POWERMETHODSHIFTED_H