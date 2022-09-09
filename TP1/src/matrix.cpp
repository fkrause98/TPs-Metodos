#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "matrix.h"
#include<cmath>

Matrix<double> file_to_W_matrix(string path){
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

vector<double> get_solution(Matrix<double> &A){
    int n = A.N-1;
    vector<double> result(n, 0);
    for(int i = n - 1; i >= 0; i--){
        double numerator = A[i][n];
        result[i] = numerator / A[i][i];
    }
    return result;
}
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
