#include "pcsc.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <any>
#include <Eigen/Dense>
#include <typeinfo>
#include <cmath>
#include <exception>
#include <algorithm>
#include <utility>
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

// Class to print the configuration of the method.
struct Config
{
    std::string file;
    std::string scalar;
    std::string algo;
    std::string outfile;
    std::string shift;
    int MaxIter;
    double tol;
};

// Function to print the values of a Config object
class Configs{
public:
    static std::map<std::string, std::string> getAlgorithmMap(){
        std::map<std::string, std::string> dictAlgo;
        dictAlgo["p"] = "power method";
        dictAlgo["ip"] = "inverse power method";
        dictAlgo["ps"] = "power method with shift";
        dictAlgo["ips"] = "inverse power method with shift";
        dictAlgo["qr"] = "QR Method";
        dictAlgo["pa"] = "power method to compute all eigenvalues";
        return dictAlgo;
    }
    static std::map<std::string, std::string> mapAlgorithm;
    static void printConfig(const Config& config)
    {
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "Configuration: " << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;

        std::cout << "Input file is " << config.file << std::endl;
        std::cout << "Scalar type is " << config.scalar << std::endl;
        std::cout << "Algorithm is " << mapAlgorithm[config.algo] << std::endl;
        std::cout << "Maximum iteration is " << config.MaxIter << std::endl;
        std::cout << "Tolerance is " << config.tol << std::endl;
        std::cout << "Shift is " << config.shift << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }
    template <typename ScalarType>
    static void printMatrix(const Eigen::Matrix<ScalarType, -1, -1>& matrix) {
        std::cout << "Input matrix:" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << matrix << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        if (abs(matrix.determinant()) < 1e-5) {
            std::cout << "Input matrix is not linearly independent." << std::endl;
            std::cout << "------------------------------------------------------------" << std::endl;
        } else {
            std::cout << "Input matrix is linearly independent." << std::endl;
            std::cout << "------------------------------------------------------------" << std::endl;
        }
    }
    template <typename ScalarType>
    static void printOutputScalar(ScalarType output) {
        std::cout << "The computed eigenvalue is" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << output << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }
    template <typename ScalarType>
    static void printOutputVector(const Eigen::Vector<ScalarType, -1>& output) {
        std::cout << "The computed eigenvalues are" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << output << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }
    static void printWriteFile(const string& outfile) {
        cout << "Results written to " << outfile << endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }
//private:
};

std::map<std::string, std::string> Configs::mapAlgorithm=Configs::getAlgorithmMap();

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
template <typename ScalarType>
std::unique_ptr<FileReader<ScalarType>> createReader(const std::string& file)
{
    auto type = identifyFileType(file);
    if (type == "csv"){
        return std::make_unique<CSVReader<ScalarType>> ();
    } else if (type == "bin"){
        return std::make_unique<BinaryReader<ScalarType>> ();
    }
    return nullptr;
}

//solver function by algorithm and max iteration
template <typename ScalarType>
std::unique_ptr<GeneralEigenMethod<ScalarType>> createMethod(const std::string& method, int MaxIter, double tol, ScalarType shift)
{
    if (method == "p") {
        return std::make_unique<PowerMethod<ScalarType>>(MaxIter, tol);
    } else if (method == "ip") {
        return std::make_unique<InversePowerMethod<ScalarType>> (MaxIter, tol);
    } else if (method == "ps") {
        return std::make_unique<PowerMethodWithShift<ScalarType>> (MaxIter, tol, shift);
    } else if (method == "ips") {
        return std::make_unique<InversePowerMethodWithShift<ScalarType>> (MaxIter, tol, shift);
    } else if (method == "qr") {
        return std::make_unique<QRMethod<ScalarType>> (MaxIter, tol);
    } else if (method == "pa") {
        return std::make_unique<PowerMethodAll<ScalarType>> (MaxIter, tol);
    }
    return nullptr;
}

template <typename ScalarType>
void vec2csv(const Eigen::Vector<ScalarType, -1>& vec, const std::string& filename)
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
template <typename ScalarType>
void value2csv(ScalarType value, const std::string& filename)
{
    // Open the CSV file for writing
    std::ofstream file(filename, std::ios::out | std::ios::app);

    if (!file.is_open())
    {
        std::cerr << "Error: could not open file '" << filename << "' for writing." << std::endl;
        return;
    }

    // Write the double value to the file
    file << value << std::endl;

    // Close the file
    file.close();
}

bool in_array(const std::string &value, const std::vector<std::string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}

template <typename ScalarType>
void computeEigenValues(ScalarType initShift,
                        const std::string &file,
                        const std::string &algo,
                        int MaxIter,
                        double tol,
                        const std::string &shift,
                        const std::string &outfile) {
    auto reader = createReader<ScalarType>(file);
    if (reader == nullptr) {
        std::cerr << "Invalid file type" << std::endl;
        throw std::invalid_argument("Please provide a csv or binary file");
    }
    auto matrix = reader->read(file);
    Configs::printMatrix(matrix);

    ScalarType shift_;
    if (shift == "default") {
        shift_ = matrix.diagonal().mean();
    } else {
        shift_ = initShift;
    }

    auto solver = createMethod<ScalarType>(algo, MaxIter, tol, shift_);
    if (solver == nullptr) {
        throw std::invalid_argument("Invalid algorithm type");
    }

    std::vector<std::string> sAlgo {"p", "ip", "ps", "ips"};
    std::vector<std::string> aAlgo {"qr", "pa"};

    if (in_array(algo, sAlgo))
    {
        cout << "** This algorithm is to compute a single eigenvalue **"<< endl;
        auto output = solver->calculateEigenvalue(matrix);
        Configs::printOutputScalar(output);
        if (identifyFileType(outfile)!="csv"){
            throw std::invalid_argument( "Output file must be CSV file! ");
        } else {
            value2csv(output, outfile);
        }
    } else if (in_array(algo, aAlgo)){
        cout << "** This algorithm is to compute all eigenvalues **"<< endl;
        auto output = solver->calculateEigenvalues(matrix);
        Configs::printOutputVector(output);
        if (identifyFileType(outfile)!="csv"){
            throw std::invalid_argument( "Output file must be CSV file! ");
        } else {
            vec2csv(output, outfile);
        }
    } else {
        throw std::invalid_argument("Invalid algorithm! ");
    }
}

int main(int argc, char **argv){
//    using ScalarType = std::complex<double>;
    // using ScalarType = double;
    std::string file;
    std::string scalar;
    std::string algo;
    std::string outfile;
    std::string shift;
    int MaxIter;
    double tol;

    InputParser input(argc, argv);

    file = input.assignCmdOption("-f", false, "");
    scalar = input.assignCmdOption("-scalar", false, "double");
    algo = input.assignCmdOption("-algo", true, "qr");
    outfile = input.assignCmdOption("-o", true, "output.csv");
    MaxIter = stoi(input.assignCmdOption("-MaxIter", true, "10000"));
    tol = stod(input.assignCmdOption("-tol", true, "1e-8"));
    shift = input.assignCmdOption("-shift", true, "default");

    Config a = {file, scalar, algo, outfile, shift, MaxIter, tol};
    Configs::printConfig(a);

    std::vector<std::string> noComplexAlgo {"ps", "ips", "pa"};
    if ((scalar == "complex") && (in_array(algo, noComplexAlgo))){
        throw std::invalid_argument("Complex scalar type not supported by this algorithm");
    }

    // FileReader<double> reader = createReader(file);
    if (scalar == "double") {
        double initShiftDouble;
        if (shift != "default") {
            initShiftDouble = stod(shift);
        } else {
            initShiftDouble = 0.0;
        }
        computeEigenValues(initShiftDouble, file, algo, MaxIter, tol, shift, outfile);
    } else if(scalar == "complex") {
        std::complex<double> initShiftComplex;
        if (shift != "default") {
            initShiftComplex = std::complex<double>(stod(shift), 0.0);
        } else {
            initShiftComplex = std::complex<double>(0.0, 0.0);
        }
        computeEigenValues(initShiftComplex, file, algo, MaxIter, tol, shift, outfile);
    }

    Configs::printWriteFile(outfile);

// Define a 3x3 matrix
    Eigen::Matrix3d m;
    m << 1,2,3,
         2,5,6,
         3,6,4;

    MatrixXcd III(2,2);
    III(0,0) = std::complex<double>(1.0, 1.0);
    III(0,1) = std::complex<double>(1.0, -2.0);
    III(1,0) = std::complex<double>(1.0, -2.0);
    III(1,1) = std::complex<double>(-1.0, -1.0);
    PowerMethodWithShift<double> method(10000, 1e-8, -10);
    // auto real_value = std::complex<double>{-1, 2};
    auto real_value = m.eigenvalues();
    auto compute = method.calculateEigenvalue(m);
    cout << "compute" << compute << endl;
    cout << "read_value" << real_value << endl;

    MatrixXd I = Eigen::MatrixXd::Constant(3, 3, 1);

    PowerMethodAll<double> pm(10000, 1e-8);
    // VectorXcd compute = pm.calculateEigenvalues(m);
    cout << "real" << m.eigenvalues() << endl;
    cout << "compute" << compute << endl;
    // cout << "norm" << (compute-m.eigenvalues()).norm() << endl;

    // Print the result to the console
    cout << m << endl;
    std::cout << m.eigenvalues()(1).real() << std::endl;

    Matrix2d pp;
    pp << 1,2,
    2,1;

    // cout << pp.eigenvalues() << endl;

    VectorXcd rea(2);
    rea << std::complex<double>(3,0), std::complex<double>(-1,2);
    cout << rea << endl;

    auto shift1 = III.diagonal().mean();
    double shift2 = 2;
    cout << m.diagonal().mean() << endl;
    cout << III.diagonal().mean() << endl;

    cout << III - shift2 * MatrixXcd::Identity(III.rows(), III.cols()) << endl;

    return 0;
}
