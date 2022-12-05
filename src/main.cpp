
// Created by suo on 05.12.22.

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <Eigen/Dense>
//#include <cmath>
//#include <exception>
//
//#include "ReadFiles.h"
//#define MAXBUFSIZE  ((int) 1e6)
//
//using namespace std;
//
//Eigen::MatrixXd createDoubleMatrix(int n) {
//    Eigen::MatrixXd Q(n,n);
//    Q.setRandom();
//    Q = Eigen::HouseholderQR<Eigen::MatrixXd>(Q).householderQ();
//
//    Eigen::MatrixXd A(n,n);
//    A.setZero();
//    A.diagonal() = Eigen::VectorXd::LinSpaced(n, 1, n);
//    A = Q*A*Q.transpose();
//    return A;
//}
//
//
//int main(int argc, char **argv) {
//    int row = 2;
//    int col = 2;
//    CSVReader reader;
//   auto m = reader.read("/Users/suo/Desktop/proj_math458/PCSC-EigenvalueProblems/src/matrix.csv");
//    //std::cout << m << std::endl;
//    int n = 3;
//    auto m = createDoubleMatrix(n);
//    std::cout << "nb_rows: " << m.rows() << std::endl;
//    std::cout << "nb_cols: " << m.cols() << std::endl;
//    std::cout << "size: " << m.size() << std::endl;
//    std::cout << "m = " << m << std::endl;
//    std::cout << "m.T = " << m.transpose() << std::endl;
//}
#include "ReadFiles.h"
#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;
using namespace Eigen;

//int main()
//{
//    // Read csv data from file
//    CSVReader csv;
//    csv.read("matrix.csv");
//    // Read binary data from file
//
//    BinaryReader binary;
//    binary.read("data.bin");
//
//    // Read data into Eigen matrix
//    return 0;
//}

#include <iostream>
#include <algorithm>
//#include <argparse/argparse.hpp>

class InputParser{
public:
    InputParser (int &argc, char **argv){
        for (int i=1; i < argc; ++i)
            this->tokens.emplace_back(argv[i]);
    }
    /// @author iain
    [[nodiscard]] const std::string& getCmdOption(const std::string &option) const{
        std::vector<std::string>::const_iterator itr;
        itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()){
            return *itr;
        }
        static const std::string empty_string;
        return empty_string;
    }
    /// @author iain
    [[nodiscard]] bool cmdOptionExists(const std::string &option) const{
        return std::find(this->tokens.begin(), this->tokens.end(), option)
               != this->tokens.end();
    }
private:
    std::vector <std::string> tokens;
};

int main(int argc, char **argv){
    InputParser input(argc, argv);
    if(input.cmdOptionExists("-h")){
        // Do stuff
        cout << &input << endl;
    }
    const std::string &filename = input.getCmdOption("-f");
    if (!filename.empty()){
        // Do interesting things ...
    }
    int i;
    for (i=0; i<argc;i++){
        cout << argv[i] << endl;
    }
    return 0;
}

