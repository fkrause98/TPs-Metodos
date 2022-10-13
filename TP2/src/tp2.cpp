#include "matrix.cpp"
#include <fstream>
using namespace std;
using std::ofstream;

int main(int argc, char *argv[]) {

    if(argc != 4){
        cout << "Numero incorrecto de argumentos" << endl;
        return -1;
    }
    string file_path = argv[1];
    int iteraciones = stod(argv[2]);
    double tolerancia = atof(argv[3]);
    //Toma el input y lo devuelve como matriz A.
    auto A = file_to_matrix(file_path);
    A.print();
    cout << A.N << " " << A.M << endl;
    cout << iteraciones << " " << tolerancia << endl;

    pair<vector<double>, vector<vector<double>>> result = get_eigen(A, iteraciones, tolerancia);
    vector<double> autovalores = result.first;
    vector<vector<double> > autovectores = result.second;


    for(int i = 0; i < autovalores.size(); i++){
        cout << autovalores[i] << " ";
    }
    cout << "<-- autovalores de A" << endl;

    for(int i = 0; i < autovectores.size(); i++){
        for(int j = 0; j < autovectores[i].size(); j++){
            cout << autovectores[i][j] << " ";
        }
        cout << "<-- autovectores[" << i << "] de A" << endl;
    }

    write_solution(result, file_path);
    /*
    vector<double> prueba = {-3280,3280,0};

    for(int i = 0; i < prueba.size(); i++){
        cout << prueba[i] << " ";
    }
    cout << "<-- prueba normalizar" << endl;

    prueba = norm_2(prueba);

    for(int i = 0; i < prueba.size(); i++){
        cout << prueba[i] << " ";
    }
    cout << "<-- prueba normalizar" << endl; */

    /*
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
    */

    return 0;
}
