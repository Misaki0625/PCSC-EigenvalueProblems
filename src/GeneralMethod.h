//
// Created by suo on 06.12.22.
//

#ifndef PCSC_PROJECT_GENERALMETHOD_H
#define PCSC_PROJECT_GENERALMETHOD_H

#include <Eigen/Dense>
#include <iostream>
using namespace std;
using namespace Eigen;
/**
 * GeneralEigenMethod is a virtual class, where all implemented EigenMethods are inherited.
 * It has two unimplemented functions, calculateEigenvalues and calculateEigenvalue.
 */
template <typename ScalarType>
class GeneralEigenMethod {

    /**
     * declare MatrixType and VectorType using template ScalarType for internal use.
     */
    using MatrixType = Eigen::Matrix<ScalarType, -1, -1>;
    using VectorType = Eigen::Vector<ScalarType, -1>;
public:

    /**
     * Constructor and destructor.
     */
    GeneralEigenMethod() = default;
    virtual ~GeneralEigenMethod() = default;

    /**
     * two unimplemented function.
     */
    virtual VectorType calculateEigenvalues(const MatrixType& matrix) = 0;
    virtual ScalarType calculateEigenvalue(const MatrixType& matrix) = 0;
};

#endif //PCSC_PROJECT_GENERALMETHOD_H