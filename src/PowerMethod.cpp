//
// Created by suo on 05.12.22.
//

//#include "PowerMethod.h"
//#include <iostream>
//#include <Eigen/Dense>
//
//using namespace Eigen;
//
//int main()
//{
//    // Define a 3x3 matrix
//    Matrix3d A;
//    A << 1, 2, 3,
//            4, 5, 6,
//            7, 8, 9;
//
//    // Print the matrix
//    std::cout << "A =\n" << A << std::endl;
//
//    // Define a vector to store the eigenvalues
//    Vector3d eigenvalues;
//
//    // Define a variable to store the maximum number of iterations
//    int maxIterations = 1000;
//
//    // Define a variable to store the error tolerance
//    double tolerance = 1e-6;
//
//    // Define a variable to store the error
//    double error = 1;
//
//    // Define a variable to store the number of iterations
//    int iterations = 0;
//
//    // Define a vector to store the eigenvector
//    Vector3d eigenvector = Vector3d::Ones();
//
//    // Iteratively calculate the eigenvalues using the power method
//    while (error > tolerance && iterations < maxIterations)
//    {
//        // Calculate the eigenvector
//        eigenvector = A * eigenvector;
//
//        // Normalize the eigenvector
//        eigenvector /= eigenvector.norm();
//
//        // Calculate the eigenvalue
//        auto eigenvalues = eigenvector.transpose() * A * eigenvector;
//
//        // Calculate the error
//        error = (A * eigenvector - eigenvalues(0, 0) * eigenvector).norm();
//
//        // Increment the number of iterations
//        iterations++;
//    }
//
//    // Print the eigenvalues
//    std::cout << "Eigenvalues =\n" << eigenvalues << std::endl;
//
//    return 0;
//}

//#include <iostream>
//#include <Eigen/Dense>
//
//using namespace Eigen;
//
//int main()
//{
//    // define a random 3x3 matrix
//    Matrix3d A;
//    A << 1, 2, 3,
//            4, 5, 6,
//            7, 8, 9;
//
//    std::cout << "Matrix A:\n" << A << std::endl;
//
//    // define a list of initial guesses for the eigenvectors
//    std::vector<Vector3d> x0 = {
//            Vector3d(1, 0, 0),
//            Vector3d(0, 1, 0),
//            Vector3d(0, 0, 1)
//    };
//
//    // set the tolerance for the convergence criterion
//    double tolerance = 1e-6;
//
//    // initialize the list of eigenvalues and eigenvectors
//    std::vector<double> lambda(3);
//    std::vector<Vector3d> x(3);
//
//    // iterate until convergence
//    for (int i = 0; i < 3; ++i)
//    {
//        // initialize the eigenvector with the initial guess
//        x[i] = x0[i];
//
//        // iterate until convergence
//        while (true)
//        {
//            // compute the next approximation of the eigenvector
//            Vector3d x_next = A * x[i];
//
//            // compute the norm of the current approximation of the eigenvector
//            double norm = x_next.norm();
//
//            // normalize the current approximation of the eigenvector
//            x_next /= norm;
//
//            // check for convergence
//            if ((x[i] - x_next).norm() < tolerance)
//            {
//                // update the eigenvector and eigenvalue
//                x[i] = x_next;
//                lambda[i] = norm;
//                break;
//            }
//
//            // update the eigenvector
//            x[i] = x_next;
//        }
//    }
//
//    // print the eigenvalues and eigenvectors
//    for (int i = 0; i < 3; ++i)
//    {
//        std::cout << "Eigenvalue " << i << ": " << lambda[i] << std::endl;
//        std::cout << "Eigenvector " << i << ":\n" << x[i] << std::endl;
//    }
//
//    return 0;
//}

#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main()
{
    // Define a 3x3 matrix
    Matrix3f A;
    A << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    VectorXcf eigenvaluestrue = A.eigenvalues();

    // Define a 3x1 vector
    Vector3f v;

    // Set the tolerance for the power method
    float tol = 1e-8;

    // Set the maximum number of iterations
    int max_iter = 10000;

    // Compute all eigenvalues of A using the power method
    for (int i = 0; i < 3; i++)
    {
        // Set the initial vector v
        v << 0, 1, 1;

        for (int j = 0; j < max_iter; j++)
        {
            // Compute the product Av
            Vector3f Av = A * v;

            // Compute the eigenvalue as the maximum component of Av
            float lambda = Av.maxCoeff();

            // Normalize v by dividing it by the maximum component
            v = Av / lambda;

            // Check for convergence
            if (Av.isApprox(lambda * v, tol))
            {
                std::cout << "Eigenvalue: " << lambda << std::endl;
                break;
            }
        }
    }
    cout << "Real eigenvalues: " << endl << eigenvaluestrue << endl;

    return 0;
}



