//
// Created by suo on 05.12.22.
//

#ifndef PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H
#define PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H

#include <Eigen/Dense>
#include <iostream>
#include <type_traits>
#include "SingleEigenMethod.h"
using namespace std;
using namespace Eigen;

// Inverse power method with shift for calculating eigenvalues
template <typename ScalarType>
class InversePowerMethodWithShift : public SingleEigenMethod<ScalarType> {
public:
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
    InversePowerMethodWithShift(int MaxIter, double tol, const std::string& shift) : MaxIter_(MaxIter), tol_(tol), shift_(shift) {}
    ~InversePowerMethodWithShift() override = default;

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

        if (abs(A.determinant()) < 1e-5) {
            // cout << "Input matrix is not linearly independent" << endl;
            // return lambda;
            throw std::invalid_argument("Input matrix for this algorithm must be linearly independent");
        }

        MatrixType inv = (A - shift * MatrixType::Identity(A.rows(), A.cols())).inverse();

        // Initialize the eigenvalue to zero
        ScalarType lambda = 0;
        int i;

        // Iterate until convergence or max iterations reached
        for (i = 0; i < MaxIter_; i++)
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
            ScalarType newLambda = x.transpose() * A * x;

            // Check for convergence
            if (abs(newLambda - lambda) < tol_)
            {
                break;
            }
            // x = Ax / Ax.norm();
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
    const std::string shift_;
    static ScalarType computeShift(const MatrixType& matrix)
    {
        // Compute the average of the diagonal elements of A
        // as an initial estimate of the shift
        ScalarType shift = matrix.diagonal().mean();
        return shift;
    }
    static ScalarType convertShift(const std::string& str)
    {
        ScalarType shift;
        if (std::is_same<ScalarType, double>::value) {
            shift = stod(str);
        } else if (std::is_same<ScalarType, std::complex<double>>::value) {
            shift = stold(str);
        }
        return shift;
    }
};

#endif //PCSC_PROJECT_INVERSEPOWERMETHODSHIFTED_H