//
// Created by suo on 05.12.22.
//
#include <iostream>
#include <Eigen/Dense>
#include "QRMethod.h"
#include "unils.h"
using namespace std;
using namespace Eigen;

//int main()
//{
//    // Create an arbitrary-sized matrix
//    //MatrixXd A = MatrixXd::Random(10, 10);
//    MatrixXd A = createDoubleMatrix(10);
//
//    // Compute the QR decomposition of A
//    HouseholderQR<MatrixXd> qr(A);
//
//    // Get the Q and R matrices from the QR decomposition
//    MatrixXd Q = qr.householderQ();
//    MatrixXd R = qr.matrixQR().triangularView<Upper>();
//
//    // Compute the eigenvalues of R * Q
//    SelfAdjointEigenSolver<MatrixXd> eigensolver(R * Q);
//
//    // Print the eigenvalues to the console
//    cout << "The eigenvalues of A are:" << endl << eigensolver.eigenvalues() << endl;
//
//    EigenvalueSolver solver(A);
//    VectorXd eigenvalues = solver.computeEigenvalues();
//
//// Print the eigenvalues
//    std::cout << "Eigenvalues: " << eigenvalues << std::endl;
//
//    return 0;
//}

int main()
{
// Test the different eigenvalue solvers on a simple matrix
    MatrixXcd A = MatrixXcd(3,3);
    A << 1, 2, 3,
            4, 5, 6,
            7, 8, 10;
    MatrixXd B = createDoubleMatrix(2);
    cout << B << endl;

    QRSolver qrSolver;
//    PowerSolver powerSolver;
//    InversePowerSolver inversePowerSolver;
//    PowerShiftSolver powerShiftSolver(1.0);
//    InversePowerInheritanceSolver inversePowerInheritanceSolver;
    cout << "Eigenvalues of A (QR method):" << endl << qrSolver.computeEigenvalues(A) << endl;
//    cout << "Eigenvalues of A (power method):" << endl << powerSolver.computeEigenvalues(A) << endl;
//    cout << "Eigenvalues of A (inverse power method):" << endl << inversePowerSolver.computeEigenvalues(A) << endl;
//    cout << "Eigenvalues of A (power method with shift):" << endl << powerShiftSolver.computeEigenvalues(A) << endl;
//    cout << "Eigenvalues of A (inverse power method using inheritance):" << endl << inversePowerInheritanceSolver.computeEigenvalues(A) << endl;

    return 0;
}