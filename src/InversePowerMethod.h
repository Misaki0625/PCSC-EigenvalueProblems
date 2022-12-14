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

/**
 * InversePowerMethod is the implementation of inverse power method, which reverses the iteration step of the power method
 * to compute the smallest eigenvalue of a given matrix in magnitude.
 * This class inherits from SingleEigenMethod and overwrites the calculateEigenvalue function.
 */
template <typename ScalarType>
class InversePowerMethod : public SingleEigenMethod<ScalarType> {

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:

    /**
     * Constructor and destructor.
     */
    InversePowerMethod(int MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~InversePowerMethod() override = default;

    /**
     * calculateEigenvalues function is not implemented.
     */
    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }

    /**
     * calculateEigenvalue function is implemented to compute the smallest eigenvalue in magnitude.
     * If the matrix is not linearly independent that is not invertible, this method is not possible to compute
     * the correct eigenvalue. E.g. a real double matrix has zero eigenvalue as its smallest eigenvalue when it has
     * zero determinant, then this algorithm will throw an invalid argument.
     * Normally, it starts with a random initial eigenvector and iteratively compute the new eigenvalue and eigenvector
     * until the maximum iteration. Tolerance is used to make sure convergence is achieved at the last iteration.
     */
    ScalarType calculateEigenvalue(const MatrixType& matrix) override {
        // Read the matrix and its row
        MatrixType A = matrix;
        int n = A.rows();

        // Initialize the eigenvector with random values
        VectorType x = VectorType::Random(n);

        // Initialize the eigenvalue to zero
        ScalarType lambda = 0;

        // Declare the iteration
        int i;

        // Determine whether the matrix is of full rank
        if (abs(A.determinant()) < 1e-5) {
            throw std::invalid_argument("Input matrix for this algorithm must be linearly independent");
        }

        // Compute the inverse matrix
        MatrixType A_inverse = A.inverse();

        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
        {
            // Compute the next estimate of the eigenvector
            x = (A - lambda * MatrixType::Identity(n, n)).inverse() * x;

            // Normalize the eigenvector
            x.normalize();

            // Compute the next estimate of the eigenvalue
            ScalarType newLambda = x.dot(A * x) / x.dot(x);

            // Check for convergence
            if (abs(newLambda - lambda) < tol_)
            {
                break;
            }

            // Assign the new eigenvalue
            lambda = newLambda;
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

#endif //PCSC_PROJECT_INVERSEPOWERMETHOD_H