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
    //Toma el input y lo devuelve como matriz W.
    auto W = file_to_W_matrix(file_path);
    //Crea D a partir de W.
    auto D = W_to_D_matrix(W);
    //product <- W*D.
    auto product = Matrix_mul_diag(W, D);
    //product <- p*WD.
    product.times_scalar(p_value);
    int n = product.N;
    Matrix<double> id = identity(n);
    //result <- (I-pWD)
    Matrix<double> result = sub(id, product);
    //Extendemos con unos, simulando
    //una matriz extendida, resolviendo
    //el sistema (I-pWD)*x = (1, ..., 1)
    result.extend_with_ones();
    //Triangular result de manera inferior.
    result.gaussian_form();
    //Triangular result de manera superior.
    result.gaussian_upper_form();
    //Obtener solución (o sea, hacer el despeje)
    //al tener solution triangulada.
    vector<double> solution = get_solution(result);
    //Mismo vector de antes, ahora
    //normalizado.
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
