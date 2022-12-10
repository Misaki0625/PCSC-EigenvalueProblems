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

template <typename ScalarType>
class PowerMethod : public SingleEigenMethod<ScalarType> {
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:
    PowerMethod(int MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~PowerMethod() {}

    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }
    ScalarType calculateEigenvalue(const MatrixType& matrix) override {
        // VectorXd eigenvalues;
        MatrixType A = matrix;

        int n = A.rows();
        // Initialize the eigenvector with random values
        VectorXd x = VectorXd::Random(n);

        // Initialize the eigenvalue to zero
        ScalarType lambda = 0;
        int i;
        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
        {
            // Compute the matrix-vector product Ax
            VectorXd Ax = A * x;

            // Compute the eigenvalue as the maximum value of the vector
            ScalarType newLambda = Ax.maxCoeff();

            // Check for convergence
            if (abs(newLambda - lambda) < tol_)
            {
                break;
            }

            // Update the eigenvalue and normalize the vector
            lambda = newLambda;
            x = Ax / lambda;
    }
//        if (i == MaxIter_){
//            throw std::runtime_error("Convergence not achieved");
//        }

        return lambda;
    }
private:
    double MaxIter_;
    double tol_;
};

#endif //PCSC_PROJECT_POWERMETHOD_H