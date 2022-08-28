#include "matrix.cpp"
#include <assert.h>
using namespace std;

int main(int argc, char *argv[]) {
    if(argc != 3){
        cout << "Numero incorrecto de argumentos" << endl;
        return -1;
    }
    string file_path = argv[1];
    float p_value = atof(argv[2]);
    cout << "Leyendo: " << (file_path) << endl << "P: " << p_value << endl;
    auto W = file_to_W_matrix(file_path, p_value);
    auto D = W_to_D_matrix(W);
    W.print();
    D.print();
    auto product = Matrix_mul_diag(W, D);
    product.print();
    product.times_scalar(p_value);
    product.print();
    int n = product.N;
    Matrix<double> id = identity(n);
    Matrix<double> result = sub(id, product);
    result.print();
    result.extend_with_ones();
    result.print();
    result.gaussian_form();
    result.print();
    vector<double> solution = get_solution(result);
    for(auto num : solution)
        cout << num << endl;
    // C.print();
    // W.gaussian_form();
    // W.print();
    return 0;
}
