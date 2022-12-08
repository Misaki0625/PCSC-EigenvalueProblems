#include "pcsc.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <Eigen/Dense>
#include <cmath>
#include <exception>
#include <algorithm>
#include "ReadFiles.h"
#include "PowerMethod.h"
#include "InversePowerMethod.h"
#include "PowerMethodShifted.h"
#include "InversePowerMethodShifted.h"
#include "QRMethod.h"
#include "PowerMethodAll.h"


using namespace std;
using namespace Eigen;

class InputParser{
public:
    InputParser (int &argc, char **argv){
        for (int i=1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    /// @author iain
    const std::string& getCmdOption(const std::string &option) const{
        std::vector<std::string>::const_iterator itr;
        itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()){
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }
    /// @author iain
    bool cmdOptionExists(const std::string &option) const{
        return std::find(this->tokens.begin(), this->tokens.end(), option)
               != this->tokens.end();
    }
    const std::string& assignCmdOption(const std::string &option, bool optional, const std::string &default_value) const{
        if(this->cmdOptionExists(option)){
            // assign the option
            const std::string &value = this->getCmdOption(option);
            if (!value.empty()){
                return value;
                //cout << "filename:" << file << endl;
            } else{
                //cout << "file is empty!" << endl;
                throw std::invalid_argument( "no value is given for " + option );
            }
        } else if(optional){
            // if the option does not exist, output a message
            cout << "Option " << option << " does not exist" << endl;
            cout << "Falling back to the default value: " << default_value << endl;
            return default_value;
        } else{
            cout << "Option" << option << "must be given" << endl;
            throw std::invalid_argument( "Option " + option + " must be given");
        }
    }
private:
    std::vector <std::string> tokens;
};

// Function to identify the file type by its name
std::string identifyFileType(std::string filename)
{
    // Convert the filename to lowercase
    std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

    // Get the position of the last '.' in the filename
    std::size_t dotPos = filename.find_last_of('.');

    // If a '.' is not found, return an empty string
    if (dotPos == std::string::npos)
        return "";

    // Get the file type by extracting the substring after the last '.'
    std::string fileType = filename.substr(dotPos + 1);

    // Return the file type in lowercase
    return fileType;
}

//reader function by extension name of file
FileReader* createReader(const std::string& file)
{
    auto type = identifyFileType(file);
    if (type == "csv"){
        return new CSVReader();
    } else if (type == "bin"){
        return new BinaryReader();
    }
    return nullptr;
}

//solver function by algorithm and max iteration
GeneralEigenMethod* createMethod(const std::string& method, double MaxIter, double tol, const std::string& shift)
{
    if (method == "p") {
        return new PowerMethod(MaxIter, tol);
    } else if (method == "ip") {
        return new InversePowerMethod(MaxIter, tol);
    } else if (method == "ps") {
        return new PowerMethodWithShift(MaxIter, tol, shift);
    } else if (method == "ips") {
        return new InversePowerMethodWithShift(MaxIter, tol, shift);
    } else if (method == "qr") {
        return new QRMethod(MaxIter, tol);
    } else if (method == "pa") {
        return new PowerMethodAll(MaxIter, tol);
    }
    return nullptr;
}

void write2csv(const VectorXd& vec, const std::string& filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file '" << filename << "' for writing." << std::endl;
        return;
    }
    // not sure if should add statement to detect the filename type, if it is not csv, put an error??
// Save the vector to the file, with each element separated by a comma
    for (int i = 0; i < vec.size(); ++i)
    {
        file << vec(i);
        if (i < vec.size() - 1)
        {
            file << ",";
        }
    }
    file << std::endl;

    file.close();
}

bool in_array(const std::string &value, const std::vector<std::string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}



    int main(int argc, char **argv){
    std::string file;
    std::string algo;
    std::string outfile;
    std::string shift;
    int MaxIter;
    double tol;

    InputParser input(argc, argv);

    file = input.assignCmdOption("-f", false, "");
    algo = input.assignCmdOption("-algo", true, "qr");
    outfile = input.assignCmdOption("-o", true, "output.csv");
    MaxIter = stoi(input.assignCmdOption("-MaxIter", true, "10000"));
    tol = stod(input.assignCmdOption("-tol", true, "1e-8"));
    shift = input.assignCmdOption("-shift", true, "default");


//    // command option: file
//    if(input.cmdOptionExists("-f")){
//        // assign the option
//        const std::string &filename = input.getCmdOption("-f");
//        if (!filename.empty()){
//            file = filename;
//            cout << "filename:" << file << endl;
//        } else{
//            cout << "file is empty!" << endl;
//        }
//    } else{
//        // if the option does not exist, output a message
//        cout << "Option -f does not exist" << endl;
//        return 1;
//    }
//    // command option: algorithm
//    if(input.cmdOptionExists("-algo")){
//        // assign the option
//        const std::string &algorithm = input.getCmdOption("-algo");
//        if (!algorithm.empty()){
//            algo = algorithm;
//            cout << "algorithm:" << algo << endl;
//        } else{
//            cerr << "Option -algo is empty" << endl;
//            return 1;
//        }
//    } else{
//        // if the option does not exist, output a message
//        cout << "Option -algo does not exist" << endl;
//        cout << "Falling back to the default value: qr" << endl;
//        algo = "qr";
//    }
//
//    if(input.cmdOptionExists("-MaxIter")){
//        // assign the option
//        const std::string &iteration = input.getCmdOption("-MaxIter");
//        if (!iteration.empty()){
//            MaxIter = stoi(iteration);
//            cout << "max iteration:" << MaxIter << endl;
//        } else{
//            cerr << "Option -MaxIter is empty" << endl;
//            return 1;
//        }
//    } else{
//        // if the option does not exist, output a message
//        cout << "Option -MaxIter does not exist" << endl;
//        cout << "Falling back to the default value: 10000" << endl;
//        MaxIter = 10000;
//    }
//
//    if(input.cmdOptionExists("-o")){
//        // assign the option
//        const std::string &output = input.getCmdOption("-o");
//        if (!output.empty()) {
//            out = output;
//            cout << "output file:" << out << endl;
//        }
//    } else{
//        // if the option does not exist, output a message
//        cout << "No file not provided" << endl;
//        cout << "Print the results to the screen" << endl;
//    }

    FileReader* reader = createReader(file);
    if (reader == nullptr) {
        std::cout << "Invalid file type" << std::endl;
        return 1;
    }
    auto matrix = reader->read(file);
    // test if matrix is read successfully
    delete reader;
    reader = nullptr;
    cout << matrix << endl;

    GeneralEigenMethod* solver = createMethod(algo, MaxIter, tol, shift);
    if (solver == nullptr) {
        std::cout << "Invalid algorithm type" << std::endl;
        return 1;
    }

    // a configuration print need to be written as a function/class

    std::vector<std::string> sAlgo {"p", "ip", "ps", "ips"};
    std::vector<std::string> aAlgo {"qr", "pa"};

    if (in_array(algo, sAlgo))
    {
        cout << "Use " << algo << " algorithm to compute a single eigenvalue"<< endl;
        auto output = solver->calculateEigenvalue(matrix);
        cout << "computed" << output << endl;
    } else if (in_array(algo, aAlgo)){
        cout << "Use " << algo << " to compute all eigenvalues"<< endl;
        auto output = solver->calculateEigenvalues(matrix);
        cout << "computed" << output << endl;
    }
    // use template? guess not
    // test if eigenvalues can be returned successfully
    // cout << "computed" << output << endl;

    // real eigenvalues computed by Eigen library
    VectorXcd eigenvaluestrue = matrix.eigenvalues();
    cout << "real" << eigenvaluestrue << endl;

    Eigen::EigenSolver<MatrixXd> es(matrix);
    VectorXcd emo = es.eigenvalues();

    cout << "The eigenvalues of A are: " << emo << endl;

//    if (!outfile.empty()){
//        write2csv(output, outfile);
//    } else {
//        cout << output << endl;
//    }
    delete solver;
    solver = nullptr;
    return 0;
}
