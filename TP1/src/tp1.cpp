#include "matrix.cpp"
#include <fstream>
using namespace std;
using std::ofstream;

int main(int argc, char *argv[]) {
    if(argc != 3){
        cout << "Numero incorrecto de argumentos" << endl;
        return -1;
    }
    string file_path = argv[1];
    float p_value = atof(argv[2]);
    auto W = file_to_W_matrix(file_path);
    auto D = W_to_D_matrix(W);
    auto product = Matrix_mul_diag(W, D);
    product.times_scalar(p_value);
    int n = product.N;
    Matrix<double> id = identity(n);
    Matrix<double> result = sub(id, product);
    result.extend_with_ones();
    result.gaussian_form();
    result.gaussian_upper_form();
    vector<double> solution = get_solution(result);
    vector<double> normalized_solution = normalize(solution);
    // =========
    //  OUTPUT
    // =========
   ofstream outdata;
   outdata.open(file_path + ".out");
   if (!outdata) {
       cerr << "No pude abrir el archivo de salida" << endl;
       exit(1);
   }
    outdata << p_value << endl; 
    for (double d: normalized_solution) 
        outdata << d << endl;
    
    outdata.close();

    return 0;
}
