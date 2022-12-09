//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_POWERMETHOD_H
#define PCSC_PROJECT_POWERMETHOD_H

#include <Eigen/Dense>
#include <iostream>
#include <stdexcept>
#include "SingleEigenMethod.h"
using namespace std;
using namespace Eigen;

class PowerMethod : public SingleEigenMethod {
public:
    PowerMethod(double MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~PowerMethod() {}

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
        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
        {
            // Compute the matrix-vector product Ax
            VectorXd Ax = A * x;

            // Compute the eigenvalue as the maximum value of the vector
            double newLambda = Ax.maxCoeff();

            // Check for convergence
            if (abs(newLambda - lambda) < tol_)
            {
                break;
            }

            // Update the eigenvalue and normalize the vector
            lambda = newLambda;
            x = Ax / lambda;
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

#endif //PCSC_PROJECT_POWERMETHOD_H