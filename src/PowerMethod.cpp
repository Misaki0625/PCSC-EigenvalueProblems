//
// Created by suo on 05.12.22.
//

#include "PowerMethod.h"
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

int main()
{
    // Define a 3x3 matrix
    Matrix3d A;
    A << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;

    // Print the matrix
    std::cout << "A =\n" << A << std::endl;

    // Define a vector to store the eigenvalues
    Vector3d eigenvalues;

    // Define a variable to store the maximum number of iterations
    int maxIterations = 100;

    // Define a variable to store the error tolerance
    double tolerance = 1e-6;

    // Define a variable to store the error
    double error = 1;

    // Define a variable to store the number of iterations
    int iterations = 0;

    // Define a vector to store the eigenvector
    Vector3d eigenvector = Vector3d::Ones();

    // Iteratively calculate the eigenvalues using the power method
    while (error > tolerance && iterations < maxIterations)
    {
        // Calculate the eigenvector
        eigenvector = A * eigenvector;

        // Normalize the eigenvector
        eigenvector /= eigenvector.norm();

        // Calculate the eigenvalue
        eigenvalues = eigenvector.transpose() * A * eigenvector;

        // Calculate the error
        error = (A * eigenvector - eigenvalues(0, 0) * eigenvector).norm();

        // Increment the number of iterations
        iterations++;
    }

    // Print the eigenvalues
    std::cout << "Eigenvalues =\n" << eigenvalues << std::endl;

    return 0;
}

