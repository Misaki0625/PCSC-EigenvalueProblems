//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H
#define PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H

#include <Eigen/Dense>
#include <iostream>
#include <cstdio>
#include <type_traits>
#include "SingleEigenMethod.h"
using namespace std;
using namespace Eigen;

/**
 * InversePowerMethodWithShift is the implementation of inverse power method with shift.
 * It uses shift as an initial guess of one eigenvalue, and finds the closest eigenvalue.
 * Unfortunately, this algorithm has issues to compute the correct value for complex matrices.
 * This class inherits from SingleEigenMethod and overwrites the calculateEigenvalue function.
 */
template <typename ScalarType>
class InversePowerMethodWithShift : public SingleEigenMethod<ScalarType> {
public:

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;

    /**
     * Constructor and destructor.
     */
    InversePowerMethodWithShift(int MaxIter, double tol, ScalarType shift) : MaxIter_(MaxIter), tol_(tol), shift_(shift) {}
    ~InversePowerMethodWithShift() override = default;

    /**
     * calculateEigenvalues function is not implemented.
     */
    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }

    /**
     * calculateEigenvalue function is implemented to compute one eigenvalue closest to shift.
     * If the matrix is not linearly independent that is not invertible, it will throw an invalid argument.
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

        // Determine whether the matrix is of full rank.
        if (abs(A.determinant()) < 1e-5) {
            throw std::invalid_argument("Input matrix for this algorithm must be linearly independent");
        }

        // Compute the inverse of the shifted matrix
        MatrixType inv = (A - shift_ * MatrixType::Identity(n, n)).inverse();

        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
        {
            // Compute the next approximation of eigenvector
            x = inv * x;

            // Normalize the eigenvector
            x.normalize();

            // Compute the next estimate of the eigenvalue
            ScalarType newLambda = x.transpose() * A * x;

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
    int MaxIter_;
    double tol_;
    ScalarType shift_;
};

#endif //PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H