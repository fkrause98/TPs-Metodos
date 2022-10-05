#include "matrix.cpp"
#include <fstream>
using namespace std;
using std::ofstream;

int main(int argc, char *argv[]) {

    Matrix<double> M(4, 10);
    // M.set(0,0, 1);
    // M.set(0,2, 1);
    // M.set(1,0,1);
    // M.set(1,1,1);
    // M.set(1,2,1);
    // M.set(1,3,1);
    // M.set(2,2,1);
    // M.set(2,3,1);
    // M.set(3,0,1);
    // M.set(3,1,1);

    M.set(0, 0, 2);
    M.set(0, 1, 1);
    M.set(1, 0, 1);
    M.set(1, 1, 2);

    vector<double> res = power_method(M, 1000);

    double eigen_val = eigen_value(M,  res);

    cout << eigen_val << endl;
    return 0;
}
