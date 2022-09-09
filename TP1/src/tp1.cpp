#include "matrix.cpp"
#include <assert.h>
#include <chrono>
#include <utility>
#include <fstream>
using namespace std;
using std::ofstream;

typedef std::chrono::high_resolution_clock::time_point TimeVar;
#define duration(a) std::chrono::duration_cast<std::chrono::milliseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()
TimeVar start;
// void reset_timer(){
//     start = timeNow();
//     cout << "Time reset" << endl;
// }
int main(int argc, char *argv[]) {
    if(argc != 3){
        cout << "Numero incorrecto de argumentos" << endl;
        return -1;
    }
    string file_path = argv[1];
    float p_value = atof(argv[2]);
    // cout << "Leyendo: " << (file_path) << endl << "P: " << p_value << endl;
    auto start = timeNow();
    auto W = file_to_W_matrix(file_path, p_value);
    // cout << "Time spent creating W: " << duration(timeNow()-start)*(1e-9) << endl;
    // reset_timer();
    auto D = W_to_D_matrix(W);
    // cout << "Time spent creating D: " << duration(timeNow()-start) << endl;
    // reset_timer();
//    W.print();
//    D.print();
    auto product = Matrix_mul_diag(W, D);
    // cout << "Time spent multiplying W by D: " << duration(timeNow()-start) << endl;
    // reset_timer();
//    product.print();
    product.times_scalar(p_value);
    // cout << "Time spent multiplying WD by p: " << duration(timeNow()-start) << endl;
    // reset_timer();
//    product.print();
    int n = product.N;
    Matrix<double> id = identity(n);
    // cout << "Time spent creating identity: " << duration(timeNow()-start) << endl;
    // reset_timer();
    Matrix<double> result = sub(id, product);
    // cout << "Time spent doing Id-(pWD): " << duration(timeNow()-start) << endl;
    // reset_timer();
//    result.print();
    result.extend_with_ones();
    // cout << "Time spent extending with ones: " << duration(timeNow()-start) << endl;
    // reset_timer();
//    result.print();
    result.gaussian_form();
    // cout << "Time spent doing Gauss: " << duration(timeNow()-start) << endl;
    // reset_timer();
    result.gaussian_upper_form();
    // cout << "Time spent doing Upper Gauss: " << duration(timeNow()-start) << endl;
    // reset_timer();
    // result.print();
    vector<double> solution = get_solution(result);
    // cout << "Time spent getting solution: " << duration(timeNow()-start) << endl;
    // reset_timer();
    // for(auto num : solution)
    //     cout << num << endl;

    vector<double> normalized_solution = normalize(solution);

    // for(auto num : normalized_solution)
    //     cout << num << endl;
    // C.print();
    // W.gaussian_form();
    //W.print();

    // =========
    //  OUTPUT
    // =========
   ofstream outdata;
   outdata.open("archive.out");
   if (!outdata) {
       cerr << "Error: file couldn't be opened" << endl;
       exit(1);
   }
    outdata << p_value << endl; 
    for (double d: normalized_solution) 
        outdata << d << endl;
    
    outdata.close();

    return 0;
}
