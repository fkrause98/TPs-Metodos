#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include "matrix.h"
#include <cmath>
#include <time.h>

Matrix<double> file_to_matrix(string path){
        
        // Leer el archivo como un stream
        ifstream stream1(path);
        // Usar line de buffer
        string line1;

        // Obtener cantidad de filas
        int N = 0;
        while(getline(stream1, line1))
            N++;
        int M = 0;

        // Inicializar matriz vacia.
        Matrix<double> A(N, M);

        ifstream stream2(path);
        string line2;
        //Metemos los valores no nulos en values.
        
        for(int i = 0; i < N; i++){
            getline(stream2, line2);
            string fila = line2;
            int j;
            for(j = 0; j < N-1; j++){
                int split = fila.find(" ");
                string fst = fila.substr(0, split);
                fila = fila.substr(split+1);
                if(fst != "0"){
                    A.set(i, j, stod(fst));
                    M++;
                }
            }
            if(fila != "0"){
                A.set(i, j, stod(fila));
                M++;
            }
        }
        A.M = M;  
        return A;
}


// Esto toma la matriz W del enunciado
// y la transforma en la matriz D.
Matrix<double> W_to_D_matrix(Matrix <double> W){
    Matrix<double> D(W.N, W.N);
    for(int i = 0; i < W.N; i++){
        auto cj = W.get_cj(i);
        if(!is_zero(cj)){
            D.set(i, i, 1/cj);
        }
    }
    return D;
}
// Toma una  matriz A y la multiplica por una 
// matriz llamada diagonal, que como su nombre indica,
// asumimos que es como tal.
Matrix<double> Matrix_mul_diag(Matrix<double> A, Matrix<double> diagonal){
    // Result va a ser el resultado del producto.
    Matrix<double> result(A.N, A.M);
   // it_row == iterador a files
    for(auto it_row = A.values.begin(); it_row != A.values.end(); ++it_row){
        int index_row = it_row->first;
        //it_row == iterador a columnas.
        for(auto it_column = it_row->second.begin(); it_column != it_row->second.end(); ++it_column){
            int index_column = it_column->first;
            //
            double to_set = A[index_row][index_column]*diagonal.values[index_column][index_column];
            result.set(index_row,
                       index_column,
                       to_set);
        }
    }
    return result;
}

// Multiplicar A por un escalar p.
Matrix<double> p_times_Matrix(Matrix<double> A, double p){
    Matrix<double> result(A.N, A.M);
    for(auto it_row = A.values.begin(); it_row != A.values.end(); ++it_row){
        int index_row = it_row->first;
        for(auto it_column = it_row->second.begin(); it_column != it_row->second.end(); ++it_column){
            int index_column = it_column->first;
            double to_set = A[index_row][index_column]*p;
            result.set(index_row,
                       index_column,
                       to_set);
        }
    }
    return result;
}
// Generar una identidad de tamaño NxN.
Matrix<double> identity(int N){
    Matrix<double> Id(N, N);
    for(int i = 0; i < N; i++)
        Id.set(i, i, double(1));
    return Id;
}
// Restar 2 matrices.
template<typename Num>
Matrix<Num> sub(Matrix<Num> A, Matrix<Num> B){
      int n = A.N;
      Matrix<Num> result(n, A.M);
      for(int i = 0; i < n; i++){
          for(int j = 0; j < n; j++){
              Num res = A.values[i][j] - B[i][j];
              if(!is_zero(res)){
                  result.set(i, j, res);
              }
          }
       }
      return result;
}

// Hace el despeje de una matriz tras
// haberle aplicado Gauss.
vector<double> get_solution(Matrix<double> A){
    int n = A.N-1;
    vector<double> result(n, 0);
    for(int i = n - 1; i >= 0; i--){
        double numerator = A[i][n];
        result[i] = numerator / A[i][i];
    }
    return result;
}
// Normalizar el vector dado por parámetro.
vector<double> normalize(vector<double> solution) {

    double sum = 0;
    for(int i = 0; i<solution.size(); i++){
        sum += solution[i];
    }
    for(int i = 0; i<solution.size(); i++){
        solution[i] = solution[i]/sum;
    }
    return solution;
}

vector<double> norm_2(vector<double> solution) {

    double sum = 0;
    for(int i = 0; i<solution.size(); i++){
        sum += pow((solution[i]),2);
    }
    for(int i = 0; i<solution.size(); i++){
        solution[i] = solution[i]/(sqrt(sum));
    }
    return solution;
}

vector<double> mul_matrix_vector(Matrix<double> M, vector<double> V) {
    vector<double> result;
    for(int i= 0; i < M.N ; i++) {
        double sum = 0;
        for(int j=0; j <M.N; j++) {
            sum += (M[i][j] * V[j]);
        }
        result.push_back(sum);
    }
    return result;
}

vector<double> select_column(Matrix<double> &M) {
    vector<double> res;
    for (int i = 0; i < M.N ; i++) {
        res.push_back(M[i][0]);
    }
    return res;
}


vector<double> power_method(Matrix<double> M, int k) {
    //vector<double> x = select_column(M);
    srand (time(NULL));
    vector<double> x = {};
    for (int i=0; i < M.N; i++){
        x.push_back(rand());
    }
    for (int i=0; i < k ; i++) {
        x = norm_2(mul_matrix_vector(M, x));
    }
    return x;
}

double eigen_value(Matrix<double> M, vector<double> x) {
    vector<double> res = mul_matrix_vector(M, x);
    int i = 0;
    while(x[i] < 1e-4)
        i++;
    return (res[i] / x[i]);
}

vector<double> sqrt_vector(vector<double> V) {
    for(int i = 0; i < V.size(); i++){
        V[i] = sqrt(V[i]);
    }
    return V;
}

Matrix<double> create_v_vt(vector<double> V) {
    Matrix<double> v_vt(V.size(),V.size()*V.size());
    for(int i = 0; i < v_vt.N; i++){
        for(int j = 0; j < v_vt.N; j++){
            v_vt.set(i,j,V[i]*V[j]);
        }
    }
    return v_vt;
}

Matrix<double> next_matrix(Matrix<double> A, vector<double> V, double lambda) {
    Matrix<double> B = create_v_vt(V);
    B = p_times_Matrix(B, lambda);
    B = sub(A, B);
    return B;
}

vector<double> clear_vec(vector<double> V) {
    for(int i = 0; i < V.size(); i++){
        if(abs(V[i]) < 1e-4){
            V[i] = 0;
        }
    }
    return V;
}

pair<vector<double>, vector<vector<double>>> get_eigen(Matrix<double> A, int iteraciones, double tolerancia){
    vector<vector<double> > eigenvectors = {};
    vector<double> eigenvalues = {};
    for(int i = 0; i < A.N; i++){
        vector<double> eigenvec = power_method(A, iteraciones);
        eigenvec = clear_vec(eigenvec);
        eigenvectors.push_back(eigenvec);
        double eigenval = eigen_value(A, eigenvec);
        eigenvalues.push_back(eigenval);
        A = next_matrix(A, eigenvec, eigenval);
    }
    pair<vector<double>, vector<vector<double>>> par = make_pair(eigenvalues,eigenvectors);
    return par;
}
