//
// Created by suo on 05.12.22.
//
#include <iostream>
#include <Eigen/Dense>
#include "QRMethod.h"
#include "unils.h"
using namespace std;
using namespace Eigen;

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// Base class for calculating eigenvalues
class EigenvalueCalculator
{
public:
    // Virtual function for calculating eigenvalues
    virtual VectorXd calcEigenvalues(const MatrixXd& matrix) = 0;
};

// Derived class for calculating eigenvalues using the power and inverse power method
class PowerInverseMethodCalculator : public EigenvalueCalculator
{
public:
    VectorXd calcEigenvalues(const MatrixXd& matrix)
    {
        // Code for calculating eigenvalues using the power and inverse power method
        // Initialize variables
        VectorXd eigenvalues;
        VectorXd x0 = VectorXd::Random(matrix.rows());
        double lambda = 0.0;

        // Perform power method
        for (int i = 0; i < 100; i++)
        {
            VectorXd x1 = matrix * x0;
            lambda = x1.maxCoeff() / x0.maxCoeff();
            x0 = x1 / x1.maxCoeff();
        }

        // Perform inverse power method
        MatrixXd I = MatrixXd::Identity(matrix.rows(), matrix.cols());
        MatrixXd A = matrix - lambda * I;
        FullPivLU<MatrixXd> lu(A);
        eigenvalues = lu.kernel();

        return eigenvalues;
    }
};

// Derived class for calculating eigenvalues using the power and inverse power method with shift
class PowerInverseMethodShiftCalculator : public EigenvalueCalculator
{
public:
    VectorXd calcEigenvalues(const MatrixXd& matrix)
    {
        // Code for calculating eigenvalues using the power and inverse power method with shift
        // Initialize variables
        VectorXd eigenvalues;
        VectorXd x0 = VectorXd::Random(matrix.rows());
        double lambda = 0.0;

        // Perform power method
        for (int i = 0; i < 100; i++)
        {
            VectorXd x1 = (matrix - x0.maxCoeff() * MatrixXd::Identity(matrix.rows(), matrix.cols())) * x0;
            lambda = x1.maxCoeff() / x0.maxCoeff();
            x0 = x1 / x1.maxCoeff();
        }// Perform inverse power method
        MatrixXd I = MatrixXd::Identity(matrix.rows(), matrix.cols());
        MatrixXd A = matrix - lambda * I;
        FullPivLU<MatrixXd> lu(A);
        eigenvalues = lu.kernel();

        return eigenvalues;
    }
};

// Derived class for calculating eigenvalues using the QR method
class QRMethodCalculator : public EigenvalueCalculator
{
public:
    VectorXd calcEigenvalues(const MatrixXd& matrix)
    {
        // Code for calculating eigenvalues using the QR method
        // Initialize variables
        VectorXd eigenvalues;
        MatrixXd A = matrix;
        int n = matrix.rows();

        // Perform QR algorithm
        for (int i = 0; i < 100; i++)
        {
            // Perform QR decomposition
            HouseholderQR<MatrixXd> qr(A);
            MatrixXd Q = qr.householderQ();
            MatrixXd R = qr.matrixQR().triangularView<Upper>();
            // Update matrix
            A = R * Q;
        }

// Extract eigenvalues from diagonal of A
        eigenvalues = A.diagonal();

        return eigenvalues;

    }
};

class PowerMethodCalculator : public EigenvalueCalculator
{
public:
    VectorXd calcEigenvalues(const MatrixXd& matrix)
    {
        // Code for calculating eigenvalues using the power and inverse power method
        // Initialize variables
        VectorXd eigenvalues;
        VectorXd x0 = VectorXd::Random(matrix.rows());
        double lambda = 0.0;

        // Perform power method
        for (int i = 0; i < 100; i++)
        {
            VectorXd x1 = matrix * x0;
            lambda = x1.maxCoeff() / x0.maxCoeff();
            x0 = x1 / x1.maxCoeff();
        }

        eigenvalues << lambda, x0;

        return eigenvalues;
    }
};

class PowerMethodShiftCalculator : public EigenvalueCalculator
{
public:
    VectorXd calcEigenvalues(const MatrixXd& matrix)
    {
        // Code for calculating eigenvalues using the power and inverse power method
        // Initialize variables
        VectorXd eigenvalues;
        VectorXd x0 = VectorXd::Random(matrix.rows());
        double lambda = 0.0;

        // Perform power method with shift
        for (int i = 0; i < 100; i++)
        {
            VectorXd x1 = (matrix - x0.maxCoeff() * MatrixXd::Identity(matrix.rows(), matrix.cols())) * x0;
            lambda = x1.maxCoeff() / x0.maxCoeff();
            x0 = x1 / x1.maxCoeff();
        }

        eigenvalues << lambda, x0;

        return eigenvalues;
    }
};

int main()
{
    // Create a matrix
    MatrixXd matrix(3,3);
    matrix << 1, 2, 3,
            4,5,6,
            7,8,9;
    VectorXcd eigenvaluestrue = matrix.eigenvalues();

    // Create an instance of each derived class
    PowerInverseMethodCalculator powerInverseMethodCalculator;
    PowerInverseMethodShiftCalculator powerInverseMethodShiftCalculator;
    QRMethodCalculator qrMethodCalculator;
//    PowerMethodCalculator powerMethodCalculator;
//    PowerMethodShiftCalculator powerMethodShiftCalculator;

    // Calculate eigenvalues using each method
    VectorXd eigenvalues1 = powerInverseMethodCalculator.calcEigenvalues(matrix);
    VectorXd eigenvalues2 = powerInverseMethodShiftCalculator.calcEigenvalues(matrix);
    VectorXd eigenvalues3 = qrMethodCalculator.calcEigenvalues(matrix);
//    VectorXd eigenvalues4 = powerMethodCalculator.calcEigenvalues(matrix);
//    VectorXd eigenvalues5 = powerMethodShiftCalculator.calcEigenvalues(matrix);

    // Print the results
    cout << "Real eigenvalues: " << endl << eigenvaluestrue << endl;
    cout << "Eigenvalues using the power and inverse power method: " << endl << eigenvalues1 << endl;
    cout << "Eigenvalues using the power and inverse power method with shift: " << endl << eigenvalues2 << endl;
    cout << "Eigenvalues using the QR method: " << endl << eigenvalues3 << endl;
//    cout << "Eigenvalues using the power method: " << endl << eigenvalues4 << endl;
//    cout << "Eigenvalues using the power method with shift: " << endl << eigenvalues5 << endl;

    return 0;
}