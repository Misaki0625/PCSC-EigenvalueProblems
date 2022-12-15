/**
 * \mainpage EigenValueProblem
 *
 * \tableofcontents
 *
 *
 * \section introduction Introduction
 * This programme is concerned with several methods to compute eigenvalues and eigenvectors for a matrix.
 * Basically, For a matrix A, it aims at finding all scalars λ such that \f$Ax=\lambda x\f$.
 * All methods for computing eigenvalues and eigenvectors are iterative in nature, except for very small matrices.
 *
 * ---
 *
 * \section methods Methods
 * Five methods are implemented to solve the eigenvalue problem.
 * - Power method
 * - Inverse power method
 * - Power method with shift
 * - Inverse power method with shift
 * - QR method
 *
 * ---
 *
 * \subsection power_method Power method
 * The power method tries to determine the largest magnitude eigenvalue, and the corresponding eigenvector,
 * of a matrix, by computing (scaled) vectors in the sequence.
 * This algorithm is applicable for double and complex matrices, and it can be modified to compute all eigenvalues at once.
 * But it has the limitation to compute for the complex matrices in this programme.
 *
 * \subsection inverse_power_method Inverse power method
 * The inverse power method reverses the iteration step of the power method.
 * It is similar to a power method iteration for the matrix \f$A^{-1}\f$.
 * So this process will often converge to the eigenvector associated with the largest eigenvalue of \f$A^{-1}\f$,
 * which is the smallest eigenvalue of A in magnitude. In order to ensure the invertibility of the matrix,
 * its determinant cannot be 0.
 *
 * \subsection power_method_with_shift Power method with shift
 * A major limitation of the power method was that it can only find the eigenvalue of largest magnitude.
 * However, using shifting allows us to focus the attention of the power method on
 * seeking the eigenvalue closest to any particular value we care to name. Besides, it can accelerate the convergence
 * process by providing a good shift.
 *
 * \subsection inverse_power_method_with_shift Inverse power method with shift
 * Similar to power method, to release the limitation of the inverse power method, the shifting is used to
 * find a closet eigenvalue we care.
 *
 * \subsection qr_method QR method
 * QR method is the most efficient method for computing all the eigenvalues at once. it constructs its QR factorization
 *  and update the matrix as the multiplication of R and Q.
 *
 * ---
 *
 * \section convergence Convergence
 * Generally, convergence is a difficult subject and fought with special cases and exceptions to rules.
 * Throughout this programme a very simple convergence criterion is used to stop the iteration steps, that is to compare
 * the difference of the newly computed eigenvalue and the old one. If the difference is smaller than the tolerance, then
 *  the convergence is achieved at the current iteration.
 *
 * ---
 *
 * \section read_write_files Read and write files
 * This programme supports reading Eigen matrix from csv and binary files.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <any>
#include <memory>
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

/**
 * Using namespace std and Eigen to make them referred by name.
 */
using namespace std;
using namespace Eigen;

/**
 * InputParser is a module to recognize, pass and assign the command arguments into corresponding variables.
 * It has three function, getCmdOption, cmdOptionExists and assignCmdOption.
 * The first two functions are referred from stack overflow answers: https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c
 */
class InputParser{
public:
    InputParser (int &argc, char **argv){
        for (int i=1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }

    /**
     * getCmdOption is a function that obtains the value for a specific option.
     */
    const std::string& getCmdOption(const std::string &option) const{
        std::vector<std::string>::const_iterator itr;
        itr =  std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()){
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
    }

    /**
     * cmdOptionExists is a function that determines whether the input option exists or not.
     */
    bool cmdOptionExists(const std::string &option) const{
        return std::find(this->tokens.begin(), this->tokens.end(), option)
               != this->tokens.end();
    }

    /**
     * assignCmdOption is a function that assigns the value into an option. It also includes an optional argument that
     * allows assigning a default value when no value is given from the command line.
     */
    const std::string& assignCmdOption(const std::string &option, bool optional, const std::string &default_value) const{
        if(this->cmdOptionExists(option)){
            const std::string &value = this->getCmdOption(option);
            if (!value.empty()) {
                return value;
            } else{
                throw std::invalid_argument( "no value is given for " + option );
            }
        } else if(optional){
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

/**
 * Config is a struct class that contains the variables for configuration.
 */
struct Config{
    std::string file;
    std::string scalar;
    std::string algo;
    std::string outfile;
    std::string shift;
    int MaxIter;
    double tol;
};

/**
 * Configs is a set of configuration printer functions.
 */
class Configs{
public:

    /**
     * getAlgorithmMap is a function to create a map for algorithms.
     */
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

    /**
     * mapAlgorithm is a map for algorithms.
     */
    static std::map<std::string, std::string> mapAlgorithm;

    /**
     * printConfig is a function to print the configuration.
     */
    static void printConfig(const Config& config) {
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

    /**
     * printMatrix is a function to print the input matrix.
     */
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

    /**
     * printOutputScalar is a function to print the single output eigenvalue.
     */
    template <typename ScalarType>
    static void printOutputScalar(ScalarType output) {
        std::cout << "The computed eigenvalue is" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << output << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }

    /**
     * printOutputVector is a function to print the output eigenvalues.
     */
    template <typename ScalarType>
    static void printOutputVector(const Eigen::Vector<ScalarType, -1>& output) {
        std::cout << "The computed eigenvalues are" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << output << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }

    /**
     * printWriteFile is a function to print the message that the output is written to file successfully.
     */
    static void printWriteFile(const string& outfile) {
        cout << "Results written to " << outfile << endl;
        std::cout << "------------------------------------------------------------" << std::endl;
    }
};

std::map<std::string, std::string> Configs::mapAlgorithm=Configs::getAlgorithmMap();

/**
 * identifyFileType is a function to identify the type of input file
 *
 * param: filename (string)
 * return: file type (string)
 */
std::string identifyFileType(std::string filename) {
    // Convert the filename to lowercase
    std::transform(filename.begin(), filename.end(), filename.begin(), ::tolower);

    // Get the position of the last '.' in the filename
    std::size_t dotPos = filename.find_last_of('.');

    // If a '.' is not found, return an empty string
    if (dotPos == std::string::npos)
        return "";

    // Get the file type by extracting the substring after the last '.'
    std::string fileType = filename.substr(dotPos + 1);

    // Return the file type (extension name) in lowercase
    return fileType;
}

/**
 * createReader is a function to create the file reader according to input file.
 *
 * param: filename (string)
 * return: file reader (pointer)
 */
template <typename ScalarType>
std::unique_ptr<FileReader<ScalarType>> createReader(const std::string& file) {
    auto type = identifyFileType(file);
    if (type == "csv"){
        return std::make_unique<CSVReader<ScalarType>> ();
    } else if (type == "bin"){
        return std::make_unique<BinaryReader<ScalarType>> ();
    }
    return nullptr;
}

/**
 * createMethod is a function to create the eigen method according to input configuration.
 *
 * param: method/algorithm (string)
 * param: maximum iteration (int)
 * param: tolerance (double)
 * param: shift (double/complex)
 * return: eigen solver (pointer)
 */
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

/**
 * vec2csv is a function to write the eigenvalue vector to a csv file.
 */
template <typename ScalarType>
void vec2csv(const Eigen::Vector<ScalarType, -1>& vec, const std::string& filename)
{
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file '" << filename << "' for writing." << std::endl;
        return;
    }
    for (int i = 0; i < vec.size(); ++i) {
        file << vec(i);
        if (i < vec.size() - 1) {
            file << ",";
        }
    }
    file << std::endl;

    file.close();
}

/**
 * value2csv is a function to write the eigenvalue to a csv file.
 */
template <typename ScalarType>
void value2csv(ScalarType value, const std::string& filename) {
    std::ofstream file(filename, std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file '" << filename << "' for writing." << std::endl;
        return;
    }
    file << value << std::endl;

    file.close();
}

/**
 * in_array is a function to check if a string exists in a string vector.
 */
bool in_array(const std::string &value, const std::vector<std::string> &array)
{
    return std::find(array.begin(), array.end(), value) != array.end();
}

/**
 * computeEigenValues is a function to compute the eigenvalue of a matrix
 *
 * param: shift identifier (double/complex)
 * param: input file name (string)
 * param: algorithm (string)
 * param: maximum iteration (int)
 * param: tolerance (double)
 * param: shift (string)
 * param: output file (string)
 */
template <typename ScalarType>
void computeEigenValues(ScalarType initShift,
                        const std::string &file,
                        const std::string &algo,
                        int MaxIter,
                        double tol,
                        const std::string &shift,
                        const std::string &outfile) {

    // Create the reader
    auto reader = createReader<ScalarType>(file);
    if (reader == nullptr) {
        std::cerr << "Invalid file type" << std::endl;
        throw std::invalid_argument("Please provide a csv or binary file");
    }

    // Read the matrix
    auto matrix = reader->read(file);
    Configs::printMatrix(matrix);

    // Determine the shift
    ScalarType shift_;
    if (shift == "default") {
        shift_ = matrix.diagonal().mean();
    } else {
        shift_ = initShift;
    }

    // Create the solver
    auto solver = createMethod<ScalarType>(algo, MaxIter, tol, shift_);
    if (solver == nullptr) {
        throw std::invalid_argument("Invalid algorithm type");
    }

    // Solve the problem and save the output
    std::vector<std::string> sAlgo {"p", "ip", "ps", "ips"};
    std::vector<std::string> aAlgo {"qr", "pa"};

    if (in_array(algo, sAlgo)) {
        cout << "** This algorithm is to compute a single eigenvalue **"<< endl;
        auto output = solver->calculateEigenvalue(matrix);
        Configs::printOutputScalar(output);
        if (identifyFileType(outfile)!="csv") {
            throw std::invalid_argument( "Output file must be CSV file! ");
        } else {
            value2csv(output, outfile);
        }
    } else if (in_array(algo, aAlgo)) {
        cout << "** This algorithm is to compute all eigenvalues **"<< endl;
        auto output = solver->calculateEigenvalues(matrix);
        Configs::printOutputVector(output);
        if (identifyFileType(outfile)!="csv") {
            throw std::invalid_argument( "Output file must be CSV file! ");
        } else {
            vec2csv(output, outfile);
        }
    } else {
        throw std::invalid_argument("Invalid algorithm! ");
    }
}

/**
 * an central executable main
 */
int main(int argc, char **argv){
    // Declare the input variables
    std::string file;
    std::string scalar;
    std::string algo;
    std::string outfile;
    std::string shift;
    int MaxIter;
    double tol;

    // Assign the variables from the command line
    InputParser input(argc, argv);
    file = input.assignCmdOption("-f", false, "");
    scalar = input.assignCmdOption("-scalar", false, "double");
    algo = input.assignCmdOption("-algo", true, "qr");
    outfile = input.assignCmdOption("-o", true, "output.csv");
    MaxIter = stoi(input.assignCmdOption("-MaxIter", true, "10000"));
    tol = stod(input.assignCmdOption("-tol", true, "1e-8"));
    shift = input.assignCmdOption("-shift", true, "default");

    // Print the configuration
    Config a = {file, scalar, algo, outfile, shift, MaxIter, tol};
    Configs::printConfig(a);

    // Exclude some algorithms
    std::vector<std::string> noComplexAlgo {"ps", "ips", "pa"};
    if ((scalar == "complex") && (in_array(algo, noComplexAlgo))) {
        throw std::invalid_argument("Complex scalar type not supported by this algorithm");
    }

    // Determine the scalar type and solve the problem
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

    return 0;
}
