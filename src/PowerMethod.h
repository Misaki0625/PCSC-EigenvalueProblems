//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_POWERMETHOD_H
#define PCSC_PROJECT_POWERMETHOD_H

#include <Eigen/Dense>
#include <iostream>
#include <complex>
#include <stdexcept>
#include "SingleEigenMethod.h"
using namespace std;
using namespace Eigen;

/**
 * PowerMethod is the implementation of power method, which is an iterative algorithm for finding
 * the dominant eigenvalue and eigenvector of a square matrix.
 * This class inherits from SingleEigenMethod and overwrites the calculateEigenvalue function.
 */
template <typename ScalarType>
class PowerMethod : public SingleEigenMethod<ScalarType> {

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:

    /**
     * Constructor and destructor.
     */
    PowerMethod(int MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~PowerMethod() {}


    /**
     * calculateEigenvalues function is not implemented.
     */
    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }

    /**
     * calculateEigenvalue function is implemented to compute the dominant eigenvalue.
     * Normally, it starts with a random initial eigenvector and iteratively compute the new eigenvalue and eigenvector
     * until the maximum iteration. Tolerance is used to make sure convergence is achieved at the last iteration.
     */
    ScalarType calculateEigenvalue(const MatrixType& matrix) override {
        // Read matrix and its row
        MatrixType A = matrix;
        int n = A.rows();

        // Initialize the eigenvector with random values and normalize
        VectorType x = VectorType::Random(n);
        x.normalize();

        // Initialize the eigenvalue to zero
        ScalarType lambda = 0;

        // Declare the iteration
        int i;

        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
        {
            // Compute the matrix-vector product Ax
            VectorType Ax = A * x;

            // Compute the next estimate of the eigenvalue
            ScalarType newLambda = Ax.dot(x) / x.dot(x);

            // Check for convergence
            if (abs(newLambda - lambda) < tol_)
            {
                break;
            }

            // Update the eigenvalue and normalize the eigenvector
            lambda = newLambda;
            x = Ax / lambda;
            x.normalize();
    }

        // No convergence condition
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