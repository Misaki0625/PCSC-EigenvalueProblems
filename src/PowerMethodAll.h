//
// Created by suo on 08.12.22.
//

#ifndef MAIN_CPP_POWERMETHODALL_H
#define MAIN_CPP_POWERMETHODALL_H

#include <Eigen/Dense>
#include <iostream>
#include "AllEigenMethod.h"
using namespace std;
using namespace Eigen;

/**
 * PowerMethodAll is the implementation of power method to compute all eigenvalues of a square matrix at once.
 * This class inherits from AllEigenMethod and overwrites the calculateEigenvalues function. However, this algorithm
 * is not applicable for complex matrix.
 */
template <typename ScalarType>
class PowerMethodAll : public AllEigenMethod<ScalarType> {
public:

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;

    /**
     * Constructor and destructor.
     */
    PowerMethodAll(int MaxIter, double tol) : MaxIter_(MaxIter), tol_(tol) {}
    ~PowerMethodAll() override = default;

    /**
     * calculateEigenvalue function is not implemented.
     */
    ScalarType calculateEigenvalue(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }

    /**
     * calculateEigenvalues function is implemented to compute all eigenvalues.
     * Normally, it starts with any linearly independent set of vectors stored as columns of a matrix,
     * and use the Gram-Schmidt process to orthonormalize this set and compute the new eigenvalue and eigenvector
     * in every iteration until the maximum iteration. Tolerance is used to make sure convergence is achieved at the last iteration.
     */
    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        // Declare some variables
        VectorType eigenvalues;
        MatrixType A = matrix;
        MatrixType rq;

        // Define the row of matrix
        int n = A.rows();

        // Determine whether the matrix is of full rank
        if (abs(A.determinant()) < 1e-5) {
            throw std::invalid_argument("Input matrix for this algorithm must be linearly independent");
        }

        // Use randInit function to create an random invertible matrix
        MatrixType m = randInit(n);

        // Use Gram-Schmidt process to orthonormalize this set m and generate a matrix v
        MatrixType v = gramSchmidt(m);

        // Iterate until convergence or max iterations reached
        for (int i = 0; i < MaxIter_; i++)
        {
            // Compute the matrix-vector product Ax
            MatrixType Ax = A * v;

            // Update v using the Gram-Schmidt process
            v = gramSchmidt(Ax);

            // Compute the Rayleigh quotient of iterate as rq
            rq = v.transpose() * A * v;
        }

        // Update the eigenvalues
        eigenvalues = rq.diagonal();

        // Sort eigenvalues in descending order
        std::sort(eigenvalues.data(), eigenvalues.data() + eigenvalues.size(),
                  [](ScalarType a, ScalarType b) { return std::abs(a) > std::abs(b); });

        return eigenvalues;
    }

private:
    double MaxIter_;
    double tol_;

    /**
     * randInit is a function to return a randomized invertible matrix
     */
    MatrixType randInit(int n){
        // create a randomly initialized matrix
        MatrixType A = MatrixType::Random(n, n);

        // Determine whether the matrix is of full rank, and return it when it is invertible
        for (int i = 0; true; i++)
            if (abs(A.determinant()) > 1e-5) //
            {
                return A;
            }
    }

    /**
     * gramSchmidt is a function to orthonormalize a matrix using the Gram-Schmidt process
     */
    MatrixType gramSchmidt(const MatrixType& mat) {
        // Row and column of the input orthonormalized matrix
        int m = mat.rows();
        int n = mat.cols();

        // Result matrix of orthogonal vectors
        MatrixType orth = MatrixType::Zero(m, n);

        // Use loops to orthonormalize the matrix
        orth.col(0) = mat.col(0);
        for (int i = 0; i < n; i++)
        {
            VectorType v = mat.col(i);
            for (int j = 0; j < i; j++)
            {
                v -= orth.col(j).dot(mat.col(i)) * orth.col(j);
            }
            orth.col(i) = v.normalized();
        }
        return orth;
    }
};

#endif //MAIN_CPP_POWERMETHODALL_H
