#  Eigenvalue problems
This is a C++ project for the *Programming concepts in scientific computing* (MATH-458) of EPFL.
It is an implementation of numerical methods for eigenvalue computation, including power and inverse power method, power 
and inverse power method with shift, and QR method.

## Compilation
To clone the git repository into the local folder:
```
git clone https://github.com/Misaki0625/PCSC-EigenvalueProblems.git
```
Then redirect to the repository:
```
cd PCSC-EigenvalueProblems
```
Use submodule to install *googletest* and *eigen*:
```
git submodule update --init 
```
Then, building is done as usual, e.g. with CLion or in the terminal:
```
mkdir build
cd build
cmake ..
make
```
## Test
To run all the tests at once:
```
./test_pcsc
```
Normally, it should display that 32 tests passed. 

Note that two test suites are created for testing file reader
class, ReadFileTestCSV and ReadFileTestBinary. And they are tested to read the matrix from two files, *matrix.csv* and 
*data.bin* under the *src* folder, which save the pre-defined data. If the user modifies the data in the files and run
tests, probably some tests will fail.

To make sure the tests run successfully, please do not change anything before testing. If the user already changes the data and want to run tests again, please try to recover
the data in the following ways:
### matrix.csv
This file is under *src* folder. Please directly open it in any available application or Clion, and enter the data:
```
1,2,3
4,5,6
7,8,10
```

### data.bin
This file is under *src* folder. You can use the following codes to recover the data:
```
// write a matrix into a binary file
Eigen::MatrixXd a(3, 3);
a << 1, 2, 4,
     4, 5, 6,
     7, 8, 10;

// Write matrix to binary file
ofstream out("data.bin", ios::binary);
out.write((char*)a.data(), a.size()*sizeof(double));
out.close();
```

Note that data in two files are different (the third element).

## Usage
The idea of this programme is to through command line to control the inputs of algorithms.
There are 7 options available from arguments.
### option
| Column 1 | Column 2 | Column 3 | Column 3 |
|----------|----------|----------|----------|
| Cell 1   | Cell 2   | Cell 3   | Cell 3   |
| Cell 4   | Cell 5   | Cell 6   | Cell 6   |


