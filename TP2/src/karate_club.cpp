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

    Matrix<double> L = A_to_Laplacian(A);

    L.print();

    auto res = get_eigen(L, iteraciones, tolerancia);
    write_solution(res, file_path);
    /*
    auto result = karate_centrality(A, iteraciones, tolerancia);

    auto sorted = sort_by_centrality(result);
    for(int i = 0; i < sorted.size(); i++){
        cout << sorted[i].first << " " << sorted[i].second << endl;
    }
    // double autovalor = result.first;
    // vector<double> autovector = result.second;


    // cout << "Autovalor dominante: " << autovalor << endl;
    for(int i = 0; i < result.size(); i++){
        cout << result[i] << " ";
    }
    // write_solution_karate(result, file_path);
    */
    
    return 0;
}
