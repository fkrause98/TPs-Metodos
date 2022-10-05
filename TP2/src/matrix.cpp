#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "matrix.h"
#include<cmath>

Matrix<double> file_to_W_matrix(string path){
        // Leer el archivo como un stream
        ifstream stream(path);
       // Usar line de buffer
        string line;

        // La primera línea es n,
        // el nro. de páginas.
        getline(stream, line);
        int n = stoi(line);

        // La segunda línea es m, el número
        // de links.
        getline(stream, line);
        int m = stoi(line);

        //Metemos los i,j en la matriz
        //Si recibimos un i,j, termina
        //siendo un 1 en la posición j-1,i-1 de 
        //la matriz W.
        Matrix<double> W(n, m);
        for(int k = 1; k <= m; k++){
            getline(stream, line);
            int split = line.find(" ");
            string fst = line.substr(0, split);
            string snd = line.substr(split);
            int i = stod(fst)-1;
            int j = stod(snd)-1;
            W.set(j, i, 1);
        }
        return W;
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
        res.push_back(M[i][1]);
    }
    return res;
}


vector<double> power_method(Matrix<double> M, int k) {
    vector<double> x = select_column(M);
    for (int i=0; i < k ; i++) {
        x = normalize(mul_matrix_vector(M, x));
    }
    return x;
}

double eigen_value(Matrix<double> M, vector<double> x) {
    vector<double> res = mul_matrix_vector(M, x);
    return (res[0] / x[0]);
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

Matrix<double> create_householder(vector<double> V) {
    Matrix<double> H = create_v_vt(V);
    H = p_times_Matrix(H, 2);
    Matrix<double> id = identity(V.size());
    H = sub(id, H);
    return H;
}