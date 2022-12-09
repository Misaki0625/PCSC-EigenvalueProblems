//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_INVERSEPOWERMETHOD_H
#define PCSC_PROJECT_INVERSEPOWERMETHOD_H

#include <Eigen/Dense>
#include <iostream>
#include "SingleEigenMethod.h"
using namespace std;
using namespace Eigen;

// Inverse power method for calculating eigenvalues
class InversePowerMethod : public SingleEigenMethod {
public:
    InversePowerMethod(double MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~InversePowerMethod() override = default;

    Eigen::VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        throw std::logic_error("Method not implemented");
    }
    double calculateEigenvalue(const MatrixXd& matrix) override {
        // VectorXd eigenvalues;
        MatrixXd A = matrix;

        int n = A.rows();

        // Initialize the eigenvector with random values
        VectorXd x = VectorXd::Random(n);

        // Initialize the eigenvalue to zero
        double lambda = 0;
        int i;

        if (abs(A.determinant()) < 1e-5) {
            // cout << "Input matrix is not linearly independent" << endl;
            // return lambda;
            throw std::invalid_argument("Input matrix for this algorithm must be linearly independent");
        }
        //VectorXd x = VectorXd::Unit(n, 0);

        // not inverse & output an error
        MatrixXd A_inverse = A.inverse();

        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
        {
            // Compute the next estimate of the eigenvector
            // x = (A - lambda * Eigen::MatrixXd::Identity(A.rows(), A.cols())).inverse() * x;
            x = A.inverse() * x;

            // Normalize the eigenvector
            x.normalize();

            // Compute the next estimate of the eigenvalue
            double newLambda = x.transpose() * A * x;

            // Check for convergence
            if (abs(newLambda - lambda) < tol_)
            {
                break;
            }

//            // Check for convergence
//            if (std::abs(lambda - x.transpose() * A * x) < tol_)
//                break;
            // Update the eigenvalue and normalize the vector
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
};

#endif //PCSC_PROJECT_INVERSEPOWERMETHOD_H