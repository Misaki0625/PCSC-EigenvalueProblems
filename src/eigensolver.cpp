//
// Created by suo on 05.12.22.
//
#include <Eigen/Dense>
#include <iostream>
using namespace std;
using namespace Eigen;

using Eigen::MatrixXd;
using Eigen::VectorXd;

// Abstract base class for eigenvalue calculation methods
class EigenvalueCalculationMethod {
public:
    // Calculate the eigenvalues of a given matrix
    virtual VectorXd calculateEigenvalues(const MatrixXd& matrix) = 0;
};

// Power method for calculating eigenvalues
class PowerMethod : public EigenvalueCalculationMethod {
public:
    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        // Initialize eigenvector to a random vector
//        VectorXd eigenvector = VectorXd::Random(matrix.rows());
//        // Iteratively calculate eigenvector
//        for (int i = 0; i < 100; i++) {
//            eigenvector = matrix * eigenvector;
//            eigenvector.normalize();
//        }
//        // Return eigenvector as eigenvalue
//        return eigenvector;
        const int maxIterations = 100;  // Maximum number of iterations
        const double tolerance = 1e-10; // Tolerance for convergence

        // Initialize the eigenvector to a random vector
        auto eigenvector = Eigen::VectorXd::Random(matrix.rows());
        for (int i = 0; i < maxIterations; i++)
        {
            // Calculate the next approximation of the eigenvector
            Eigen::VectorXd nextEigenvector = matrix * eigenvector;

            // Calculate the dominant eigenvalue as the norm of the eigenvector divided by the norm of the next approximation
            auto eigenvalue = eigenvector.norm() / nextEigenvector.norm();

            // Update the eigenvector to the next approximation
            eigenvector = nextEigenvector;

            // Check for convergence
            if (eigenvector.norm() < tolerance)
            {
                break;
            }
        }
    }
};

// Inverse power method for calculating eigenvalues
class InversePowerMethod : public EigenvalueCalculationMethod {
public:
    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        // Initialize eigenvector to a random vector
        VectorXd eigenvector = VectorXd::Random(matrix.rows());
        // Calculate inverse of matrix
        MatrixXd inverse = matrix.inverse();
        // Iteratively calculate eigenvector
        for (int i = 0; i < 100; i++) {
            eigenvector = inverse * eigenvector;
            eigenvector.normalize();
        }
        // Return eigenvector as eigenvalue
        return eigenvector;
    }
};

// Power method with shift for calculating eigenvalues
class PowerMethodWithShift : public EigenvalueCalculationMethod {
public:
    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        // Initialize eigenvector to a random vector
        VectorXd eigenvector = VectorXd::Random(matrix.rows());
        // Choose a random value for the shift
        double shift = VectorXd::Random(1)(0);
        // Iteratively calculate eigenvector
        for (int i = 0; i < 100; i++) {
            eigenvector = (matrix - shift * MatrixXd::Identity(matrix.rows(), matrix.cols())) * eigenvector;
            eigenvector.normalize();
        }
        // Return eigenvector as eigenvalue
        return eigenvector;
    }
};

// Inverse power method with shift for calculating eigenvalues
class InversePowerMethodWithShift : public EigenvalueCalculationMethod {
public:
    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
        // Initialize eigenvector to a random vector
        VectorXd eigenvector = VectorXd::Random(matrix.rows());
        // Calculate inverse of matrix
        MatrixXd inverse = matrix.inverse();
        // Choose a random value for the shift
        double shift = VectorXd::Random(1)(0);
        // Iteratively calculate eigenvector
        for (int i = 0; i < 100; i++) {
            eigenvector = (inverse - shift * MatrixXd::Identity(matrix.rows(), matrix.cols())) * eigenvector;
            eigenvector.normalize();
        }
        // Return eigenvector as eigenvalue
        return eigenvector;
    }
};

// QR method for calculating eigenvalues
//class QRMethod : public EigenvalueCalculationMethod {
//public:
//    VectorXd calculateEigenvalues(const MatrixXd& matrix) override {
//        // Initialize QR decomposition
//        Eigen::HouseholderQR<MatrixXd> qr(matrix.rows(), matrix.cols());
//        qr.compute(matrix);
//        // Initialize eigenvalues to the diagonal of R
//        VectorXd eigenvalues = qr.matrixQR().diagonal();
//        // Iteratively improve eigenvalues
//        for (int i = 0; i < 100; i++) {
//            // Calculate QR decomposition of matrix A - eigenvalues * I
//            qr.compute((matrix - eigenvalues.asDiagonal()).eval());
//            // Update eigenvalues to the diagonal of R
//            eigenvalues = qr.matrixQR().diagonal();
//        }
//        // Return eigenvalues
//        return eigenvalues;
//    }
//};

// Example usage
int main() {
    // Create a matrix
    MatrixXd matrix(3, 3);
    matrix << 1, 2, 3,
            4, 5, 6,
            7, 8, 10;
    VectorXcd eigenvaluestrue = matrix.eigenvalues();
    // Create an instance of each eigenvalue calculation method
    PowerMethod powerMethod;
    InversePowerMethod inversePowerMethod;
    PowerMethodWithShift powerMethodWithShift;
    InversePowerMethodWithShift inversePowerMethodWithShift;
    //QRMethod qrMethod;
    // Calculate and print the eigenvalues for each method
    std::cout << "Real eigenvalues: " << std::endl << eigenvaluestrue << std::endl;
    std::cout << "Power method: " << powerMethod.calculateEigenvalues(matrix).transpose() << "\n";
    std::cout << "Inverse power method: " << inversePowerMethod.calculateEigenvalues(matrix).transpose() << "\n";
    std::cout << "Power method with shift: " << powerMethodWithShift.calculateEigenvalues(matrix).transpose() << "\n";
    std::cout << "Inverse power method with shift: " << inversePowerMethodWithShift.calculateEigenvalues(matrix).transpose() << "\n";
    //std::cout << "QR method: " << qrMethod.calculateEigenvalues(matrix).transpose() << "\n";
    return 0;
}
