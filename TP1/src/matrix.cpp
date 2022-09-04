#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "matrix.h"
#include<cmath>

Matrix<double> file_to_W_matrix(string path, float p){
        // Read file as stream
        ifstream stream(path);
        // Use line as buffer
        string line;

        // First line is n,
        // number of pages.
        getline(stream, line);
        int n = stoi(line);

        // Second line is m, number
        // of links.
        getline(stream, line);
        int m = stoi(line);

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
Matrix<double> Matrix_mul_diag(Matrix<double> A, Matrix<double> diagonal){
    Matrix<double> result(A.N, A.M);
    for(auto it_row = A.values.begin(); it_row != A.values.end(); ++it_row){
        int index_row = it_row->first;
        for(auto it_column = it_row->second.begin(); it_column != it_row->second.end(); ++it_column){
            int index_column = it_column->first;
            double to_set = A[index_row][index_column]*diagonal.values[index_column][index_column];
            result.set(index_row,
                       index_column,
                       to_set);
        }
    }
    return result;
}

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
Matrix<double> gauss_test(){
    Matrix<double> A(3, 6);
    vector<vector<int>> matrix = {{2, 1, 3, 0, 0}, {1, 2, 0, 2, 0}, {0, 2, 1, 1, 0}, {3, 1, 0, 0, 0}};
    // vector<vector<int>> matrix = {{1, 3, 1}, {1, 1, -1}, {3, 11, 5}};
    // vector<vector<int>> matrix = {{1, 1, 1}, {1, 0, 0}, {0, 0, 1}};
    for(int i = 0; i < matrix.size(); i++){
        auto row = matrix[i];
        for(int j = 0; j < row.size(); j++){
            A.set(i, j, matrix[i][j]);
        }
    }
    // A.print();
    // A.gaussian_form();
    // A.print();
    return A;
}
Matrix<double> identity(int N){
    Matrix<double> Id(N, N);
    for(int i = 0; i < N; i++)
        Id.set(i, i, double(1));
    return Id;
}
template<typename Num>
Matrix<Num> sub(Matrix<Num> &A, Matrix<Num> &B){
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

#include <chrono>
typedef std::chrono::high_resolution_clock::time_point TimeVar;
#define duration(a) std::chrono::duration_cast<std::chrono::milliseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

TimeVar start_1;
vector<double> get_solution(Matrix<double> &A){
    int n = A.N-1;
    vector<double> result(n, 0);
    for(int i = n - 1; i >= 0; i--){
        double numerator = A[i][n];
        // for(int j = n-2; j>=i; j--){
        //     if(abs(A[i][j+1]) > 1e-4){
        //         numerator -= A[i][j+1]*result[j+1];
        //     }
        // }
        // cout << "Time spent result with i = " <<  i << " - "<< duration(timeNow()-start_1) << endl;
        // start_1 = timeNow();
        result[i] = numerator / A[i][i];
        // result[i] = A[i][i];
    }
    return result;
}

double vector_norm(vector<double> &V) {
    double value = 0;
    for(double v: V) {
        value += pow(v, 2);
    }
    return sqrt(value);
}

vector<double> normalize(vector<double> solution) {

    double norm = vector_norm(solution);
    for(int i = 0; i<solution.size(); i++){
        solution[i] = pow((solution[i]/norm), 2);
    }
    return solution;
}
