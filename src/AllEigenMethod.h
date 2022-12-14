//
// Created by suo on 08.12.22.
//

#ifndef MAIN_CPP_ALLEIGENMETHOD_H
#define MAIN_CPP_ALLEIGENMETHOD_H

#include <Eigen/Dense>
#include <iostream>
#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

/**
 * AllEigenMethod is a virtual class inheriting from GeneralEigenMethod, from which all classes inherited are used
 * to compute all eigenvalues of a given matrix at once.
 * It has two functions, calculateEigenvalues and calculateEigenvalue, in which only the former one is implemented.
 */
template <typename ScalarType>
class AllEigenMethod : public GeneralEigenMethod<ScalarType> {

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:

    /**
     * Constructor and destructor.
     */
    AllEigenMethod() = default;
    virtual ~AllEigenMethod() = default;

    /**
     * virtual inherited function.
     */
    virtual VectorType calculateEigenvalues(const MatrixType& matrix) = 0;
};

#endif //MAIN_CPP_ALLEIGENMETHOD_H
