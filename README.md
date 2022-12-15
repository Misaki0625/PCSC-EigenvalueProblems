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

## Documentation
The documentation html page is generated by Doxygen, providing a formatted documentation in line with codes.

To get the html page, redirect to the directory and run:

```
doxygen
```
Users can open the newly created folder `doxygen_doc`, `html` and `index.html` to get a full look at the
organization of this programme. 

Note that the documentation is only for the `src` folder. If the user is interested in how the test modules are organized, try to open
the `Doxyfile` file and modify `INPUT` option as `src` and `test`.

## Test
To run all the tests at once, direct to build folder and in the terminal:
```
./test_pcsc
```
Normally, it should display that 32 tests passed. 

### Test Design

There are 11 test suites containing 32 tests designed for every algorithm module and the file reader module. The tests include different
cases computation and error assertion, covering a lot of possible situations.

### Data Recovery
Note that two test suites are created for testing file reader
class, ReadFileTestCSV and ReadFileTestBinary. And they are tested to read the matrix from two files, *matrix.csv* and 
*data.bin* under the *src* folder, which save the pre-defined data. If the user modifies the data in the files and run
tests, probably some tests will fail.

To make sure the tests run successfully, please do not change anything before testing. If the user already changes the data and want to run tests again, please try to recover
the data in the following ways:
#### matrix.csv
This file is under *src* folder. Please directly open it in any available application or Clion, and enter the data:
```
1,2,3
4,5,6
7,8,10
```

#### data.bin
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
The idea of this programme is to control the inputs of algorithms through command line.
There are 7 options available from arguments.
### -f
`-f` option is the filename that tells the programme which input file to read data from. It is a mandatory option. If no 
file name is given, the programme will output an error.

The input file must be csv or binary format. This programme will automatically identify the file type by its extension name and read the
data into an Eigen matrix as input.

### -scalar
`-scalar` is another mandatory option where the users specify the scalar type and pass it to the template algorithms.
Two scalars are supported in this programme, `double` and `complex`. If none of them is explicitly given, it will throw an error.

### -algo
`-algo` is the entry of the specified algorithm.

- single eigenvalue computation: `p`, `ip`, `ps`, `ips` respectively for power method, inverse power method, 
power method with shift, and inverse power method with shift.
- all eigenvalue computation: `qr`, `pa` which represent QR method and power method to compute all eigenvalues at once.

This is an optional argument. When no value is given, it will use `qr` by default.
### -o
`-o` passes the output file name to the programme. It is an optional choice, when no file is given, the programme will create an output.csv in the build folder to save the results.

### -MaxIter
`-MaxIter` gives an integer number for the maximum iteration of eigenvalue computation. It is optional, and default value is 10000.

### -tol
`-tol` gives a double number as the criterion of convergence and stopping and iterative process. It is optional and default value is 1e-8.

### -shift
`-shift` is not necessary for methods without shifting mechanism. It has `default` as the default value. When using shifting methods, the
`default` will take the mean value of the diagnoal of input matrix. 

If users want to pass a customized shift, please enter a double
number, as shifting methods are only applicable for double matrices.

## Example
Direct to the build folder, and try the following arguments: 

```
./main -algo qr -f matrix.csv -scalar double
```

And the results are printed out:

```
The computed eigenvalues are
------------------------------------------------------------
16.7075
-0.90574
0.198247
------------------------------------------------------------
```
Except the results, the configuration, matrix and output message will be printed as well.

For more examples, try:

```
./main -algo p -f matrix.csv -scalar double
```
```
./main -algo ips -f matrix.csv -scalar double -shift -10
```
```
./main -algo qr -f data.bin -scalar complex
```

Follow the instruction in Usage and get more insights on how the programme works.


## Features

This programme enables the configuration as an input flow from command line, which increases its flexibility and efficiency without recompilation.

Besides, it supports double and complex matrix computation using all methods in template, though, some of them are not applicable for now.
The summary of all methods are listed in the table:

|     | double | complex | tolerance | full rank | shift |
|-----|--------|---------|-----------|-----------|-------|
| p   | 1      | 1       | 1         | 0         | 0     |
| ip  | 1      | 1       | 1         | 1         | 0     |
| ps  | 1      | 0       | 1         | 0         | 1     |
| ips | 1      | 0       | 1         | 1         | 1     |
| qr  | 1      | 1       | 0         | 0         | 0     |
| pa  | 1      | 0       | 0         | 1         | 0     |

1 in double and complex columns represents the method support this scalar type, 0 otherwise.
1 in tolerance means the method requires the tolerance as the convergence condition, 0 otherwise.
1 in full rank means that the method requires the matrix has full rank, 0 otherwise. 
1 in shift column means the method requires the shift as a parameter.

The summary of file reader is as below:

|         | double | complex without imaginary parts | complex with imaginary parts | 
|---------|--------|---------------------------------|------------------------------|
| csv     | 1      | 1                               | 0                            |
| binary  | 1      | 1                               | 1                            |

Csv file has the advantage of easy modification, but if the user want to input complex matrix, it is more recommended to
use binary file.

For more features regarding the programming part, please kindly check the detailed doxygen documentation.

## Issues
The issues of this programme are but not limited to:

- Some methods are not supporting both scalar types. The algorithms should be improved to incorporate various matrix types.
- File readers can be improved to support more file types, e.g. txt, webpage etc.
- Assertion and error logic is not perfectly fitted in the programme, as it should give more clues of how the users can fix the errors.
- Time and space efficiency are not strictly analyzed yet.
