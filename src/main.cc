#include "pcsc.hh"
#include "ReadFiles.h"
#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <cmath>
#include <exception>
#include <argparse.hpp>

using namespace std;
using namespace Eigen;

int main(int argc, char **argv){
    int i;
    for (i=0; i<argc;i++){
        cout << argv[i] << endl;
    }
    return 0;
}
