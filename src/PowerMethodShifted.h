//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_POWERMETHODSHIFTED_H
#define PCSC_PROJECT_POWERMETHODSHIFTED_H

#include <Eigen/Dense>
#include <iostream>
#include <type_traits>
#include "SingleEigenMethod.h"
using namespace std;
using namespace Eigen;


template <typename ScalarType>
class PowerMethodWithShift : public SingleEigenMethod<ScalarType> {
public:
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
    PowerMethodWithShift(int MaxIter, double tol, const std::string& shift) : MaxIter_(MaxIter), tol_(tol), shift_(shift) {}
    ~PowerMethodWithShift() override = default;

    VectorType calculateEigenvalues(const MatrixType& matrix) override {
        throw std::logic_error("Method not implemented");
    }
    ScalarType calculateEigenvalue(const MatrixType& matrix) override {
        // VectorXd eigenvalues;
        MatrixType A = matrix;
        ScalarType shift;

        if (shift_ == "default"){
            shift = computeShift(A);
        } else{
            shift = convertShift(shift_);
        }

        int n = A.rows();
        // Initialize the eigenvector with random values
        VectorType x = VectorType::Random(n);

        // Initialize the eigenvalue to zero
        ScalarType lambda = 0;
        int i;

        MatrixType B = A - shift * MatrixType::Identity(A.rows(), A.cols());

        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
        {
            // Compute the next approximation of the eigenvector
            x = B.lu().solve(x);
            // x = B * x;
            x.normalize();

            // Compute the matrix-vector product Ax
            VectorType Ax = A * x;

            // Compute the eigenvalue as the maximum value of the vector
            ScalarType newLambda = x.transpose() * Ax;
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
    int MaxIter_;
    double tol_;
    const std::string& shift_;
    static ScalarType computeShift(const MatrixType& matrix)
    {
        // Compute the average of the diagonal elements of A
        // as an initial estimate of the shift
        ScalarType shift = matrix.diagonal().mean();
        return shift;
    };
    static ScalarType convertShift(const std::string& str)
    {
        ScalarType shift;
        if (std::is_same<ScalarType, double>::value) {
            shift = stod(str);
        } else if (std::is_same<ScalarType, std::complex<double>>::value) {
            std::complex<double>::from_string(str);
        }
        return shift;
    }
};

#endif //PCSC_PROJECT_POWERMETHODSHIFTED_H