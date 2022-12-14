//
// Created by suo on 08.12.22.
//

#ifndef MAIN_CPP_SINGLEEIGENMETHOD_H
#define MAIN_CPP_SINGLEEIGENMETHOD_H

#include <Eigen/Dense>
#include <iostream>
#include "GeneralMethod.h"
using namespace std;
using namespace Eigen;

/**
 * SingleEigenMethod is a virtual class inheriting from GeneralEigenMethod, from which all classes inherited are used
 * to compute one eigenvalue of a given matrix.
 * It has two functions, calculateEigenvalues and calculateEigenvalue, in which only the latter one is implemented.
 */
template <typename ScalarType>
class SingleEigenMethod : public GeneralEigenMethod<ScalarType>{

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:

    /**
    * Constructor and destructor.
    */
    SingleEigenMethod() = default;
    virtual ~SingleEigenMethod() = default;

    /**
     * virtual inherited function.
     */
    virtual ScalarType calculateEigenvalue(const MatrixType &matrix) = 0;
};

#endif //MAIN_CPP_SINGLEEIGENMETHOD_H
